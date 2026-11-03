// SPDX-License-Identifier: GPL-3.0-or-later
//
// engine/src/defs/type.hpp
// Copyright (C) 2025-2026 ss
//

#pragma once

#include <cstdint>
#include <entt/fwd.hpp>
#include <glm/glm.hpp>
#include <memory>

namespace ss
{
// --------------------------------------- 数字类型
using u32 = uint32_t;
using u64 = uint64_t;
using u8 = uint8_t;
using u16 = uint16_t;

using i32 = int32_t;
using i64 = int64_t;
using i8 = int8_t;
using i16 = int16_t;

using f32 = float;
using f64 = double;

using byte = u8;

// --------------------------------------- 线性代数类型
using vec4 = glm::vec4;
using vec3 = glm::vec3;
using vec2 = glm::vec2;
using ivec3 = glm::ivec3;
using ivec2 = glm::ivec2;

using dvec3 = glm::dvec3;
using dvec2 = glm::dvec2;
using u32vec3 = glm::u32vec3;
using u32vec2 = glm::u32vec2;

using mat4 = glm::mat4;
using mat3 = glm::mat3;

// --------------------------------------- 注册表 最重要常用至高无上
// 所以给一个很短的缩写
using rg = entt::registry;

// ----------------------------------指针等
template <typename T>
using ptr = T*;
template <typename T>
using ref = T&;
template <typename T>
using uptr = std::unique_ptr<T>;
template <typename T>
using sptr = std::shared_ptr<T>;
template <typename T>
using wptr = std::weak_ptr<T>;

template <typename T>
using csvi = ref<const T>; // const view 只读视图 非常常用

using cstr = ptr<const char>;

} // namespace ss