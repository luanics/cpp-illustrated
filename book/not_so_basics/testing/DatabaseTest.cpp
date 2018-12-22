#include "Database.hpp"

#include <luanics/testing/Unit.hpp>

namespace luanics {

BEGIN_TEST_SET(Database)           // test set: "Database"

TEST(Connect) {                    // test: "Connect"
	Database d("path_to_database");
	d.open();
	EXPECT_TRUE(d.isOpen());        // test statement
	EXPECT_FALSE(d.isErrored());    // test statement
}

TEST(Disconnect) {                 // test: "Disconnect"
	Database d("path_to_database");
	d.open();
	d.close();
	EXPECT_FALSE(d.isOpen());       // test statement
	EXPECT_FALSE(d.isErrored());    // test statement
}

END_TEST_SET(Database)

} // namespace luanics
