// SPDX-License-Identifier: GPL-3.0-or-later
//
// engine/src/core/window.cpp
// Copyright (C) 2025-2026 ss
//

#include "core/window.hpp"

#include <algorithm>
#include <string_view>

#include <SDL3/SDL.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_video.h>
#include <entt/fwd.hpp>

#include "defs/error.hpp"
#include "defs/event/input_state.hpp"
#include "defs/event/window.hpp"
#include "defs/func.hpp"
#include "defs/input/key_code.hpp"
#include "defs/render/platform_data.hpp"

#include "utils/log/log_marco.hpp"

namespace ss::core
{
using ss::defs::ButtonCode;

using ss::defs::render::PlatformData;
using ss::defs::render::WindowType;

Window::Window(rg& r) : r_(r)
{
    auto& dp = r_.ctx().get<entt::dispatcher>();
    // 注册我的事件系统事件
    dp.sink<defs::events::WindowClose>().connect<&Window::close_window>(this);
}

Window::~Window()
{
    if (window_)
    {
        SDL_DestroyWindow(window_);
        window_ = nullptr;
    }
    SDL_Quit();
}

eperr<void> Window::init()
{
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        RET_ERR("SDL初始化失败");
    }

    return {};
}

eperr<void> Window::create_window(u32 width, u32 height, cstr title)
{
    if (window_ != nullptr)
    {
        LG_WARN("窗口已经创建");
        return {};
    }

    // 由bgfx创建上下文 sdl默认不创建
    auto window_flags = SDL_WINDOW_RESIZABLE; // 可添加
    window_ = SDL_CreateWindow(title, sc<i32>(width), sc<i32>(height), window_flags);

    if (!window_)
    {
        RET_ERR("窗口创建失败");
    }

    // 把窗口放在中间
    SDL_SetWindowPosition(window_, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    LG_DEBUG("窗口创建成功");

    return {};
}

void Window::broadcast_input() const
{
    defs::events::InputStateEvent current_state{};

    // key
    i32 numkeys{};
    const auto key_state = SDL_GetKeyboardState(&numkeys);
    static_assert(defs::KeyCount <= SDL_SCANCODE_COUNT, "KeyCount exceeds SDL scancode range");
    for (u32 i = 0; i < defs::KeyCount; i++)
    {
        current_state.key_state.set(i, key_state[i]);
        // 都遵循usb hid标准 可以这么搞
    }

    auto& bs = current_state.button_state;
    u32 buttons = SDL_GetMouseState(nullptr, nullptr); // 鼠标xy 空指针表示不关心
    bs[sc<size_t>(ButtonCode::LEFT)] = buttons & SDL_BUTTON_LMASK;
    bs[sc<size_t>(ButtonCode::RIGHT)] = buttons & SDL_BUTTON_RMASK;
    bs[sc<size_t>(ButtonCode::MIDDLE)] = buttons & SDL_BUTTON_MMASK;
    bs[sc<size_t>(ButtonCode::X1)] = buttons & SDL_BUTTON_X1MASK;
    bs[sc<size_t>(ButtonCode::X2)] = buttons & SDL_BUTTON_X2MASK;
    // 用的位掩码 反正就5个手动一下也行

    auto& dp = r_.ctx().get<entt::dispatcher>();
    dp.trigger(current_state);
}

[[nodiscard]] bool Window::is_should_close() const
{
    return should_close_;
}

void Window::close_window()
{
    should_close_ = true;
}

void Window::poll_events()
{
    SDL_Event event{};
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_EVENT_QUIT:
            should_close_ = true;
            break;

        case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
            // 只处理属于我们这个 window 的事件
            if (event.window.windowID == SDL_GetWindowID(window_))
            {
                should_close_ = true;
            }
            break;
        default:
            break;
        }
    }

    broadcast_input();
}

[[nodiscard]] eperr<PlatformData> Window::get_platform_window_data() const
{
    PlatformData pd{};

    SDL_PropertiesID props = SDL_GetWindowProperties(window_);

#if defined(_WIN32) || defined(_WIN64)
    pd.type = WindowType::WIN32;
    pd.native_display_type = nullptr;
    pd.native_window_handle
        = SDL_GetPointerProperty(props, SDL_PROP_WINDOW_WIN32_HWND_POINTER, nullptr);

#elifdef __APPLE__
    pd.type = WindowType::COCOA;
    pd.native_display_type = nullptr;
    pd.native_window_handle
        = SDL_GetPointerProperty(props, SDL_PROP_WINDOW_COCOA_WINDOW_POINTER, nullptr);

#elifdef __linux__
    // Linux 同时包含 X11 和 Wayland，运行时才能判断用哪个
    const char* driver = SDL_GetCurrentVideoDriver();

    if (std::string_view(driver) == "wayland")
    {
        pd.type = WindowType::WAYLAND;
        pd.native_display_type
            = SDL_GetPointerProperty(props, SDL_PROP_WINDOW_WAYLAND_DISPLAY_POINTER, nullptr);
        pd.native_window_handle
            = SDL_GetPointerProperty(props, SDL_PROP_WINDOW_WAYLAND_SURFACE_POINTER, nullptr);
    }
    else if (std::string_view(driver) == "x11")
    {
        pd.type = WindowType::X11;
        pd.native_display_type = nullptr;
        // X11 的 window 是 XID（数字），不是指针
        pd.native_window_handle
            = rc<void*>(SDL_GetNumberProperty(props, SDL_PROP_WINDOW_X11_WINDOW_NUMBER, 0));
    }
    else
    {
        RET_ERR("Unsupported window platform on linux");
    }

#else
#error "Unsupported platform: only Windows, macOS, and Linux are supported"
#endif

    return pd;
}
} // namespace ss::core