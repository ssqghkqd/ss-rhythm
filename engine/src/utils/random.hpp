// SPDX-License-Identifier: GPL-3.0-or-later
//
// engine/src/utils/random.hpp
// Copyright (C) 2025-2026 ss
//

#pragma once
#include <random>

#include "defs/type.hpp"
namespace ss::utils::random
{
static std::mt19937 generator{};

inline void init(u32 seed)
{
    generator.seed(seed);
}

inline f32 range(f32 min, f32 max)
{
    std::uniform_real_distribution distribution(min, max);
    return distribution(generator);
}
} // namespace ss::utils::random