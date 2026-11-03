// SPDX-License-Identifier: GPL-3.0-or-later
//
// engine/src/utils/maths.hpp
// Copyright (C) 2025-2026 ss
//

#pragma once
#include "defs/type.hpp"

namespace ss::utils::maths
{
template <typename T>
[[nodiscard]] inline f32 length(const T& vec)
{
    return glm::length(vec);
}

template <typename T>
[[nodiscard]] inline T normalize(const T& vec)
{
    return glm::normalize(vec);
}

} // namespace ss::utils::maths