#pragma once

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///
/// @file tutorial/StructuralMacros.hpp
///
/// @brief Macros for setting up tutorial hierarchy.
///
/// Note that all names are decorated (minimally) with "LUANICS_" prefix to avoid name clashes.
///
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "luanics/testing/core/Composite.hpp"
#include "luanics/testing/core/Installer.hpp"
#include "luanics/testing/core/Leaf.hpp"
#include "luanics/testing/core/Reporter.hpp"
#include "luanics/testing/tutorial/ComponentInstaller.hpp"
#include "luanics/testing/tutorial/CompositeReference.hpp"

#define LUANICS_ADD_TUTORIAL(tutorialName) \
	luanics::testing::core::Composite tutorial{#tutorialName};

#define LUANICS_ADD_PART(partName, isEnabled) \
	luanics::testing::core::Composite part##partName{#partName}; \
	luanics::testing::core::Installer part##partName##Installer{&tutorial, &part##partName}; \

#define LUANICS_ADD_CHAPTER(partName, chapterName, isEnabled) \
	extern luanics::testing::core::Composite luanics##Chapter##chapterName##Instance; \
	luanics::testing::core::Installer chapter##chapterName##Installer{&part##partName, &luanics##Chapter##chapterName##Instance};

#define LUANICS_TEST_SET_INSTANCE_EXTERNAL(name) luanicsTestSetInstance##name

#define LUANICS_ADD_PROJECT(partName, projectNameSpace, projectName, isEnabled) \
	namespace luanics { \
	namespace projectNameSpace { \
	extern luanics::testing::core::Composite LUANICS_TEST_SET_INSTANCE_EXTERNAL(projectName); \
	luanics::testing::core::Installer project##projectName##Installer{&part##partName, &LUANICS_TEST_SET_INSTANCE_EXTERNAL(projectName)}; \
	} }

#define LUANICS_CHAPTER_INSTANCE(name) luanics##Chapter##name##Instance

#define LUANICS_BEGIN_CHAPTER(name)\
	luanics::testing::core::Composite LUANICS_CHAPTER_INSTANCE(name){#name};\
	namespace {\
		luanics::testing::tutorial::CompositeReference chapterReference{& LUANICS_CHAPTER_INSTANCE(name)};

#define LUANICS_END_CHAPTER(name) \
	}

#define LUANICS_SECTION_CLASS_NAME(name) Luanics##name##Section
#define LUANICS_SECTION_INSTANCE_NAME(name) luanics##name##SectionInstance
#define LUANICS_SECTION_INSTALLER_INSTANCE_NAME(name) luanics##name##SectionInstallerInstance
#define LUANICS_REPORTER_NAME luanics##Reporter

#define LUANICS_SECTION(name)\
	class LUANICS_SECTION_CLASS_NAME(name) : public luanics::testing::core::Leaf {\
	public: \
		LUANICS_SECTION_CLASS_NAME(name)() : Leaf{#name} {} \
		virtual void doRun(luanics::testing::core::Reporter &) override final;\
	}; \
	LUANICS_SECTION_CLASS_NAME(name) LUANICS_SECTION_INSTANCE_NAME(name); \
	luanics::testing::tutorial::ComponentInstaller LUANICS_SECTION_INSTALLER_INSTANCE_NAME(name){& chapterReference, &LUANICS_SECTION_INSTANCE_NAME(name)};\
	void LUANICS_SECTION_CLASS_NAME(name)::doRun(luanics::testing::core::Reporter & LUANICS_REPORTER_NAME)

#define LUANICS_SUBPROJECT_INSTANCE(name) luanics##Subproject##name##Instance

#define LUANICS_BEGIN_SUBPROJECT(name)\
	luanics::testing::core::Composite LUANICS_SUBPROJECT_INSTANCE(name){#name};\
	namespace {\
		luanics::testing::tutorial::CompositeReference subprojectReference{& LUANICS_SUBPROJECT_INSTANCE(name)};

#define LUANICS_END_SUBPROJECT(name) \
	}

#define LUANICS_SUBPROJECT_TEST_CLASS(name) Luanics##name##SubprojectTest
#define LUANICS_SUBPROJECT_TEST_INSTANCE(name) luanics##name##SubprojectTestInstance
#define LUANICS_SUBPROJECT_TEST_INSTALLER_INSTANCE(name) luanics##name##SubprojectTestInstallerInstance
#define LUANICS_REPORTER luanics##Reporter

#define LUANICS_SUBPROJECT_TEST(name) \
	class LUANICS_SUBPROJECT_TEST_CLASS(name) : public luanics::testing::core::Leaf { \
	public: \
		LUANICS_SUBPROJECT_TEST_CLASS(name)() : Leaf{#name} {} \
		virtual void doRun(luanics::testing::core::Reporter &) override final; \
	}; \
	LUANICS_SUBPROJECT_TEST_CLASS(name) LUANICS_SUBPROJECT_TEST_INSTANCE(name); \
	luanics::testing::tutorial::ComponentInstaller LUANICS_SUBPROJECT_TEST_INSTALLER_INSTANCE(name){& subprojectReference, &LUANICS_SUBPROJECT_TEST_INSTANCE(name)}; \
	void LUANICS_SUBPROJECT_TEST_CLASS(name)::doRun(luanics::testing::core::Reporter & LUANICS_REPORTER)
