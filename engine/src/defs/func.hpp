// SPDX-License-Identifier: GPL-3.0-or-later
//
// engine/src/defs/func.hpp
// Copyright (C) 2025-2026 ss
//

#pragma once

#include <cassert>
namespace ss
{

// cpp转换太丑了 包装一下 c风格又不太安全
// 只用这两个 动态转换因为关了rtti不能用 const转换就不应该使用
template <typename To, typename From>
constexpr auto sc(From value) noexcept -> To
{
    return static_cast<To>(value);
}

/*
 * 一开始我还在这里写了完美转发，但后来又删掉了，我也不知道要不要用？应该不需要吧
 */

template <typename To, typename From>
    requires(std::is_pointer_v<To> || std::is_integral_v<To>)
            && (std::is_pointer_v<From> || std::is_integral_v<From>)
constexpr auto rc(From value) noexcept -> To
{
    return reinterpret_cast<To>(value);
}
} // namespace ss
namespace ss::debug
{
inline void break_point(cstr msg = nullptr)
{
    assert(!"debug_break_point!" && msg);
}
} // namespace ss::debug