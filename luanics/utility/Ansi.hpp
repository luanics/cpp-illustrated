#pragma once

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///
/// @file Ansi
///
/// @brief Ansi escape sequences for colors.
///
/// https://en.wikipedia.org/wiki/ANSI_escape_code
///
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

namespace luanics::utility::ansi {

static constexpr char const * RESET = "\033[0m";
static constexpr char const * BLACK = "\033[30m";
static constexpr char const * RED = "\033[31m";
static constexpr char const * GREEN = "\033[32m";
static constexpr char const * BROWN = "\033[33m";
static constexpr char const * BLUE = "\033[34m";
static constexpr char const * MAGENTA = "\033[35m";
static constexpr char const * CYAN = "\033[36m";
static constexpr char const * LIGHT_GRAY = "\033[37m";
static constexpr char const * DARK_GRAY  = "\033[1m\033[30m";
static constexpr char const * BOLD_RED = "\033[1m\033[31m";
static constexpr char const * BOLD_GREEN = "\033[1m\033[32m";
static constexpr char const * BOLD_YELLOW = "\033[1m\033[33m";
static constexpr char const * BOLD_BLUE = "\033[1m\033[34m";
static constexpr char const * BOLD_MAGENTA = "\033[1m\033[35m";
static constexpr char const * BOLD_CYAN = "\033[1m\033[36m";
static constexpr char const * WHITE = "\033[1m\033[37m";

} // namespace luanics::utility::ansi
