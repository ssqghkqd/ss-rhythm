// SPDX-License-Identifier: GPL-3.0-or-later
//
// engine/src/utils/file_utils.hpp
// Copyright (C) 2025-2026 ss
//

#pragma once
#include <filesystem>
#include <string>

#include "defs/error.hpp"
#include "defs/type.hpp"

namespace ss::utils::file_utils
{
eperr<std::filesystem::path>
get_resource_path(csvi<std::filesystem::path> relative_path);

eperr<std::string> read_file_to_string(csvi<std::filesystem::path> path);

eperr<std::vector<byte>> read_file_to_bytes(csvi<std::filesystem::path> path);

} // namespace ss::utils::file_utils