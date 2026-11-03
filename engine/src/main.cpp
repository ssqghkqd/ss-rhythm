// SPDX-License-Identifier: GPL-3.0-or-later
//
// engine/src/main.cpp
// Copyright (C) 2025-2026 ss
//

#include "core/app.hpp"

int main()
{
    ss::core::App app;
    app.init();
    return app.run();
}