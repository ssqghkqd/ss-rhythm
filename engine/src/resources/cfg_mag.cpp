// SPDX-License-Identifier: GPL-3.0-or-later
//
// engine/src/resources/cfg_mag.cpp
// Copyright (C) 2025-2026 ss
//

#include "resources/cfg_mag.hpp"

#include <string>
#include <yaml-cpp/yaml.h>

#include "defs/cfg/basic.hpp"
#include "defs/func.hpp"

#include "utils/file_utils.hpp"

namespace ss::res
{
eperr<void> CfgMag::load_basic(const std::filesystem::path& file_path)
{
    const auto content = TRY(utils::file_utils::read_file_to_string(file_path));

    try
    {
        auto basic = YAML::Load(content);
        basic_.game_name = basic["game_name"].as<std::string>();
        basic_.engine_name = basic["engine_name"].as<std::string>();
        basic_.window_width = basic["window_width"].as<u32>();
        basic_.window_height = basic["window_height"].as<u32>();
    }
    catch (...)
    {
        RET_ERR("读取yaml错误"); // TODO
    }

    return {};
}

auto CfgMag::get_basic() -> defs::cfg::Basic const
{
    return basic_;
}

} // namespace ss::res