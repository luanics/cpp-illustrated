#include "luanics/testing/Unit.hpp"
#include "luanics/utility/Paths.hpp"

#include <cstring>

namespace luanics::utility {

BEGIN_TEST_SET(Paths)

TEST(FileNameFrom) {
	auto const * path = "/this/is/a/path/to/a/file.ext";
	auto const * file = fileNameFrom(path);
	EXPECT_EQ(std::strcmp(file, "file.ext"), 0);
}

END_TEST_SET(Paths)

} // namespace luanics::utility
