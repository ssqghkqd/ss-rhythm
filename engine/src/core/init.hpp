// SPDX-License-Identifier: GPL-3.0-or-later
//
// engine/src/core/init.hpp
// Copyright (C) 2025-2026 ss
//

#pragma once

#include "defs/error.hpp"
#include "defs/type.hpp"
namespace ss::core::init
{
eperr<void> init(rg& r);

void fill_reg(rg& r);

void init_basic(rg& r);
eperr<void> load_config(rg& r);
eperr<void> init_window(rg& r);

eperr<void> init_renderer(rg& r);
} // namespace ss::core::init