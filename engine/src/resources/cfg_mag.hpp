// SPDX-License-Identifier: GPL-3.0-or-later
//
// engine/src/resources/cfg_mag.hpp
// Copyright (C) 2025-2026 ss
//

#pragma once

#include <filesystem>

#include "defs/cfg/basic.hpp"
#include "defs/error.hpp"

namespace ss::res
{
class CfgMag
{
  private:
    defs::cfg::Basic basic_{};

  public:
    CfgMag() = default;
    ~CfgMag() = default;
    CfgMag(const CfgMag&) = delete;
    CfgMag& operator=(const CfgMag&) = delete;
    CfgMag(CfgMag&&) = delete;
    CfgMag& operator=(CfgMag&&) = delete;

    eperr<void> load_basic(const std::filesystem::path& file_path);
    auto get_basic() -> defs::cfg::Basic const;

  private:
};

} // namespace ss::res