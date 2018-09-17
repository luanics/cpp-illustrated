#pragma once

namespace luanics::utility {

/// @returns the last element of the pathName, e.g., "File.ext" in /path/File.ext"
char const * fileNameFrom(char const * const pathName, char const delimiter = '/');

} // namespace luanics::utility
