#include "luanics/testing/Unit.hpp"
#include "luanics/testing/tutorial/ReporterAdapter.hpp"
#include "luanics/testing/core/SimpleReporter.hpp"

using namespace luanics::testing;
using namespace luanics::testing::core;
using namespace luanics::testing::tutorial;

// Comment this out to begin
//#define IS_INACTIVE

BEGIN_TEST_SET(TutorialReporterAdapter)

#ifndef IS_INACTIVE

TEST(All) {
	Composite tutorial{"Tutorial"};
	Composite level1{"1"};
	Installer level1Installer(&tutorial, &level1);

	Composite level1Topics{"Topics"};
	Installer level1TopicsInstaller{&level1, &level1Topics};
	Composite level1TopicA{"A"};
	Installer level1TopicAInstaller{&level1Topics, &level1TopicA};
	Composite level1TopicASubtopicI{"I"};
	Installer level1TopicASubtopicIInstaller{&level1TopicA, &level1TopicASubtopicI};

	Composite level1Projects{"Projects"};
	Installer level1ProjectsInstaller{&level1, &level1Projects};
	Composite level1ProjectA{"A"};
	Installer level1ProjectAInstaller{&level1Projects, &level1ProjectA};
	Composite level1ProjectASubprojectI{"I"};
	Installer level1ProjectASubprojectIInstaller{&level1ProjectA, &level1ProjectASubprojectI};

}

#endif
#undef IS_INACTIVE

END_TEST_SET(TutorialReporter)
