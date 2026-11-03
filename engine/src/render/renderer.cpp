// SPDX-License-Identifier: GPL-3.0-or-later
//
// engine/src/render/renderer.cpp
// Copyright (C) 2025-2026 ss
//

#include "render/renderer.hpp"
#include "defs/error.hpp"
#include "defs/render/platform_data.hpp"

#include <bgfx/bgfx.h>

namespace ss::render
{
struct PosColorVertex
{
    // 顶点坐标
    f32 x_{};
    f32 y_{};
    f32 z_{};
    // 纹理坐标
    i16 u_{};
    i16 v_{};
    // 顶点描述对象
    static bgfx::VertexLayout vert_layout_;

    static void init()
    {
        // 这句话的意思是位置数据里面，前三个 Float 类型是作为顶点坐标，后两个 Int16
        // 类的值作为纹理的坐标
        vert_layout_.begin()
            .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
            .add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Int16, true)
            .end();
    };
};
using defs::render::PlatformData;
using defs::render::WindowType;

eperr<void> Renderer::init(u32 width, u32 height, const PlatformData& pd)
{
    width_ = width;
    height_ = height;

    bgfx::PlatformData bpd{};
    switch (pd.type)
    {
    case WindowType::OTHER:
        RET_ERR("不支持的平台");
    case WindowType::WAYLAND:
        bpd.type = bgfx::NativeWindowHandleType::Enum::Wayland;
        break;
    default:
        bpd.type = bgfx::NativeWindowHandleType::Enum::Default;
        break;
    }

    bpd.nwh = pd.native_window_handle;
    bpd.ndt = pd.native_display_type;

    bgfx::Init init{};

    // 选择一个渲染后端，当设置为 RendererType::Enum::Count
    // 的时候，系统将默认选择一个平台，可以设置Metal，OpenGL ES，Direct 等
    init.type = bgfx::RendererType::Enum::Count;
    // 设置供应商接口Vendor PCI ID，默认设置为0将选择第一个设备来显示。
    init.vendorId = 0;
    // 设置分辨率大小
    init.resolution.width = width_;
    init.resolution.height = height_;
    // BGFX_RESET_VSYNC
    // 其作用主要是让显卡的运算和显示器刷新率一致以稳定输出的画面质量。
    init.resolution.reset = BGFX_RESET_VSYNC;
    init.platformData = bpd;
    bgfx::init(init);

    return {};
}

void Renderer::render()
{
    bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x78A7FFFF, 1.0f, 0);
    bgfx::setViewRect(0, 0, 0, width_, height_);
    bgfx::touch(0);
}

void Renderer::frame()
{
    bgfx::frame();
}
} // namespace ss::render