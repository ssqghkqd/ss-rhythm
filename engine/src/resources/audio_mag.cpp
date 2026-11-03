// SPDX-License-Identifier: GPL-3.0-or-later
//
// engine/src/resources/audio_mag.cpp
// Copyright (C) 2025-2026 ss
//

#include "audio_mag.hpp"

#include "defs/func.hpp"
#include "utils/log/log_marco.hpp"

namespace ss::res
{

AudioMag::~AudioMag()
{
    ma_sound_uninit(&music_);
    for (auto& [name, sound] : sounds_)
    {
        ma_sound_uninit(sound);
    }
    ma_engine_uninit(&engine_);
}

operr AudioMag::init()
{
    const ma_result result = ma_engine_init(nullptr, &engine_);
    if (result != MA_SUCCESS)
    {
        const auto e = "音频引擎加载失败";
        SSLOG_CRI(e);
        MAKE_OPERR(e);
    }
    return OKERR;
}

operr AudioMag::load_music(csvi<defs::resource::Resource> res)
{
    auto& name = res.name;
    auto& path = res.path;
    if (music_paths_.contains(name))
    {
        SSLOG_WARN("音乐已经加载: {}", name);
        return OKERR;
    }

    music_paths_[name] = path;
    SSLOG_INFO("存储音乐{}->{}", name, path.string());
    return OKERR;
}

// 播放音乐（单实例）
void AudioMag::play_music(
    const std::string& name, float volume, bool loop
) noexcept // 但会造成崩溃
{
    assert(music_paths_.contains(name) && "音乐未加载！");

    ma_sound_uninit(&music_);
    const auto path = music_paths_[name];

    const auto result = ma_sound_init_from_file(
        &engine_,
        path.c_str(),
        MA_SOUND_FLAG_STREAM | MA_SOUND_FLAG_ASYNC,
        nullptr,
        nullptr,
        &music_
    );

    if (result != MA_SUCCESS)
    {
        {
            const auto e = std::format(
                "音乐播放失败 名称{}，原因:{}",
                name,
                ma_result_description(result)
            );
            SSLOG_ERROR(e);
            assert(0);
            return;
        }
    }

    ma_sound_set_volume(&music_, volume * music_volume_ * master_volume_);
    ma_sound_set_looping(&music_, loop);
    ma_sound_start(&music_);
}

/*
 * sounds哈希表里存储的是模板masound对象，几乎静态
 * 播放时将会分配一块内存通过ma提供的复制播放来播放，存入activesound链表
 * 所有权归他所有并且由cleansound定时检查清理
 * 一些踩坑实录：ma没有提供什么一次加载直接播放什么的
 * 搞了半天最后看到了原来是这样实现的
 */
operr AudioMag::load_sound(csvi<defs::resource::Resource> res)
{
    auto& name = res.name;
    auto& path = res.path;
    if (sounds_.contains(name))
    {
        SSLOG_WARN("音频已经加载，名：{}", name);
        return OKERR;
    }

    const auto template_sound = rc<ma_sound*>(malloc(sizeof(ma_sound)));
    if (template_sound == nullptr)
    {
        MAKE_OPERR("内存不足");
    }
    const ma_result result = ma_sound_init_from_file(
        &engine_,
        path.c_str(),
        MA_SOUND_FLAG_DECODE,
        nullptr,
        nullptr,
        template_sound
    );

    if (result != MA_SUCCESS)
    {
        free(template_sound);
        MAKE_OPERR(
            std::format(
                "加载{} ,失败: {}", path.string(), ma_result_description(result)
            )
        );
    }

    sounds_[name] = template_sound; // 存储模板
    return OKERR;
}

void AudioMag::play_sound(const std::string& name, const float volume) noexcept
{
    assert(sounds_.contains(name) && "未加载！");

    /*
     * 【内存管理经验】（亲身经历都是）
     * 1.第一反应当然是智能指针，但实测是不行的：首先
     * 如果你直接使用智能指针，会编译报错 指出无法删除这个masound对象
     *      如果你手动加上删除器 这里有一个问题
     * 智能指针的析构如果再不正确的时间调用，有可能会导致段错误，因为音频驱动还在用这个堆内存
     * 2.那智能指针不能用 只有两个了 new malloc 为什么是malloc？
     * 因为 new会尝试调用构造函数 而masound没有 虽然这其实不会有什么效果
     * 但感觉是是很奇怪的 并且new还会抛出异常 不符合我的理念 最终使用malloc
     * 首先ma就是一个c库他的示例就是这样做的 并且malloc的开销是最小的
     * 另外提一句activesounds是一个链表 由清理函数定期清理管理
     */
    // 可以用对象池 这里malloc可能内存碎片 但目前性能好不用
    const auto sound = rc<ma_sound*>(malloc(sizeof(ma_sound)));

    assert(sound != nullptr && "内存不足");

    const ma_result result = ma_sound_init_copy(
        &engine_, sounds_[name], MA_SOUND_FLAG_DECODE, nullptr, sound
    );

    if (result != MA_SUCCESS)
    {
        {
            free(sound);
            const std::string e = std::format(
                "播放失败 {}: {}", name, ma_result_description(result)
            );
            SSLOG_ERROR(e);
            debug::break_point();
            return;
        }
    }

    ma_sound_set_volume(sound, volume * sfx_volume_ * master_volume_);
    ma_sound_set_looping(sound, false);
    ma_sound_start(sound);
    active_sounds_.push_back(sound);
}

void AudioMag::clean_sound()
{
    /*
     * 将会被每秒调用 注意这里播放完的音频将被清理！不要手动管理
     * 频率不要太高（目前1hz） 一开始我用是vector 现在是链表 但仍然保持低频清理
     */
    for (auto it = active_sounds_.begin(); it != active_sounds_.end();)
    {
        if (!ma_sound_is_playing(*it))
        {
            ma_sound_uninit(*it);
            free(*it);
            it = active_sounds_.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

operr AudioMag::load_all_audio(
    csvi<std::vector<defs::resource::Resource>> sounds,
    csvi<std::vector<defs::resource::Resource>> musics
)
{
    for (const auto& sound : sounds)
    {
        TRY_OPOP(load_sound(sound), assert(0));
    }
    for (const auto& music : musics)
    {
        TRY_OPOP(load_sound(music), assert(0));
    }
    return OKERR;
}

} // namespace ss::res