// SPDX-License-Identifier: GPL-3.0-or-later
//
// engine/src/resources/audio_mag.hpp
// Copyright (C) 2025-2026 ss
//

#pragma once

#include <miniaudio/miniaudio.h>

#include <list>
#include <string>
#include <unordered_map>

#include "defs/error.hpp"
#include "defs/type.hpp"
#include "wrapper/filesystem.hpp"

namespace ss::res
{
class AudioMag
{
  private:
    ma_engine engine_{};
    ma_sound music_{};                                        // 音乐专用通道
    std::unordered_map<std::string, fs::path> music_paths_{}; // 音乐路径表
    std::unordered_map<std::string, ma_sound*> sounds_{};     // 音效
    std::list<ma_sound*> active_sounds_{};

    f32 master_volume_ = 0.05f;
    f32 music_volume_ = 1.0f;
    f32 sfx_volume_ = 1.0f;

  public:
    AudioMag() = default;
    ~AudioMag();
    AudioMag(const AudioMag&) = delete;
    AudioMag& operator=(const AudioMag&) = delete;
    AudioMag(AudioMag&&) = delete;
    AudioMag& operator=(AudioMag&&) = delete;

    [[nodiscard]] operr load_all_audio(
        csvi<std::vector<defs::resource::Resource>> sounds,
        csvi<std::vector<defs::resource::Resource>> musics
    );

    [[nodiscard]] operr init();
    operr load_music(csvi<defs::resource::Resource> res);
    void play_music(const std::string& name, float volume, bool loop) noexcept;
    operr load_sound(csvi<defs::resource::Resource> res);
    void play_sound(const std::string& name, float volume) noexcept;
    void clean_sound();

  private:
};
} // namespace ss::resources