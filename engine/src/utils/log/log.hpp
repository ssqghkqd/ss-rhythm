// SPDX-License-Identifier: GPL-3.0-or-later
//
// engine/src/utils/log/log.hpp
// Copyright (C) 2025-2026 ss
//

#pragma once
#include "defs/type.hpp"
#include <spdlog/spdlog.h>

namespace ss::log
{
sptr<spdlog::logger> get_logger();
} // namespace ss::log