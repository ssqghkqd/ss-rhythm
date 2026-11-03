// SPDX-License-Identifier: GPL-3.0-or-later
//
// engine/src/defs/error.hpp
// Copyright (C) 2025-2026 ss
//

#pragma once
#include <expected>
#include <source_location>
#include <string>
#include <string_view>

namespace ss::defs::error
{
class Error
{
  private:
    std::string error_message_{};

  public:
    explicit Error(
        std::string msg, const std::source_location& loc = std::source_location::current()
    ) :
        error_message_(
            std::format(
                "{}:{} {}:\n{}", loc.file_name(), loc.line(), loc.function_name(), std::move(msg)
            )
        )
    {
    }
    ~Error() = default;

    [[nodiscard]]
    std::string_view what() const noexcept
    {
        return error_message_;
    }

    Error(Error&& other) noexcept : error_message_(std::move(other.error_message_))
    {
    }
    Error& operator=(Error&& other) noexcept
    {
        if (this != &other)
        {
            error_message_ = std::move(other.error_message_);
        }
        return *this;
    }
    Error(const Error&) = default;
    Error& operator=(const Error& other)
    {
        if (this != &other)
        {
            error_message_ = other.error_message_;
        }
        return *this;
    }
};
} // namespace ss::defs::error

// ------------------------------------------------------------------

namespace ss
{
using err = ss::defs::error::Error;

template <typename T> using eperr = std::expected<T, err>;

} // namespace ss

// ------------------------------------------------------------------
namespace ss::defs::error::macro // 并不是为了命名空间 纯粹分隔一下
                                 // 实际上宏并不会受命名空间限制
{
#define _MAKE_EP(e) (std::unexpected(e))

#define TRY(operate)                                                                               \
    ({                                                                                             \
        auto e = (operate);      /* 这是个eperr*/                                                  \
        if (!e.has_value())                                                                        \
        {                                                                                          \
            return _MAKE_EP(e.error());                                                            \
        }                                                                                          \
        e.value();                                                                                 \
    })

#define RET_ERR(text)                                                                              \
    do                                                                                             \
    {                                                                                              \
        ss::debug::break_point();                                                                  \
        return _MAKE_EP(err{ (text) });                                                            \
    } while (0)
} // namespace ss::defs::error::macro