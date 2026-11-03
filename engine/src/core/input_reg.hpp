// SPDX-License-Identifier: GPL-3.0-or-later
//
// engine/src/core/input_reg.hpp
// Copyright (C) 2025-2026 ss
//

#pragma once
#include "defs/event/input_state.hpp"
#include "defs/type.hpp"
namespace ss::core::input
{
class InputRegister
{
  private:
    rg& r_;
    defs::events::InputStateEvent last_state_{};

  public:
    InputRegister(rg& r);
    ~InputRegister() = default;

    InputRegister(const InputRegister&) = delete;
    InputRegister& operator=(const InputRegister&) = delete;
    InputRegister(InputRegister&&) = delete;
    InputRegister& operator=(InputRegister&&) = delete;

  private:
    void handle_input(const defs::events::InputStateEvent& event);
};
} // namespace ss::core::input