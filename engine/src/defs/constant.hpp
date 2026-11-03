// SPDX-License-Identifier: GPL-3.0-or-later
//
// engine/src/defs/constant.hpp
// Copyright (C) 2025-2026 ss
//

#pragma once

#include "defs/type.hpp"
namespace ss::defs
{
namespace state
{
#ifdef NDEBUG
constexpr bool IS_DEBUG = false;
#else
constexpr bool IS_DEBUG = true;
#endif

} // namespace state

namespace unit
{
constexpr u32 BYTES = 1;
constexpr u32 KiB = 1024 * BYTES;
constexpr u32 MiB = 1024 * KiB;
constexpr u32 GiB = 1024 * MiB;
} // namespace unit

namespace reference
{
constexpr cstr cfg_basic_path = "config/basic.yaml";
}
} // namespace ss::defs