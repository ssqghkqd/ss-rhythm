// SPDX-License-Identifier: GPL-3.0-or-later
//
// engine/src/utils/file_utils.cpp
// Copyright (C) 2025-2026 ss
//

#include "utils/file_utils.hpp"

#include <fstream>
#include <sstream>

#include "defs/error.hpp"
#include "defs/func.hpp"
#include "utils/log/log_marco.hpp"

namespace ss::utils::file_utils
{
using Path = std::filesystem::path;
eperr<std::string> read_file_to_string(const Path& path)
{
    const auto safe_path = TRY(get_resource_path(path));

    std::ifstream file{ safe_path };
    if (!file.is_open())
    {
        RET_ERR(std::format("无法打开文件:{}", safe_path.string()));
    }

    std::stringstream buffer{};
    buffer << file.rdbuf();
    return buffer.str();
}

eperr<std::vector<byte>> read_file_to_bytes(const Path& path)
{
    const auto safe_path = TRY(get_resource_path(path));

    std::ifstream file{ safe_path, std::ios::ate | std::ios::binary };
    if (!file.is_open())
    {
        RET_ERR(std::format("无法打开文件:{}", path.string()));
    }

    const auto file_size{ file.tellg() };
    if (file_size < 0)
    {
        RET_ERR(std::format("文件大小无效:{}", path.string()));
    }

    std::vector<byte> buffer(file_size);
    file.seekg(0); // 回到开头
    file.read(rc<char*>(buffer.data()), file_size);

    file.close();
    return buffer;
}

eperr<Path> get_resource_path(const Path& relative_path)
{
    static const std::array<Path, 3> POSSIBLE_PATHS
        = { "../assets/", "../../assets/", "./assets/" };
    LG_DEBUG("相对路径: {}", relative_path.string());
    for (const auto& path : POSSIBLE_PATHS)
    {
        auto final_path = path / relative_path;
        LG_DEBUG("尝试完整路径: {}", final_path.string());
        if (std::filesystem::exists(final_path))
        {
            LG_DEBUG("找到完整路径: {}", final_path.string());
            return final_path;
        }
    }

    RET_ERR(std::format("{}不存在", relative_path.string()));
}
} // namespace ss::utils::file_utils