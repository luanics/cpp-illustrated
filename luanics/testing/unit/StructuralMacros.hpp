#pragma once

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///
/// @file unit/StructuralMacros.hpp
///
/// @brief Macros for setting up unit test hierarchy.
///
/// Note that all names are decorated (minimally) with "LUANICS_" prefix to avoid name clashes.
///
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

#include "luanics/testing/core/Composite.hpp"
#include "luanics/testing/core/Installer.hpp"
#include "luanics/testing/core/Leaf.hpp"
#include "luanics/testing/core/Reporter.hpp"
#include "luanics/testing/unit/Instance.hpp"

#define LUANICS_DOUBLE_COMPARISON_PRECISION 1e-6

#define LUANICS_TEST_SET_INSTANCE luanicsTestSetInstance
#define LUANICS_TEST_SET_INSTALLER_INSTANCE luanicsTestSetInstallerInstance
#define LUANICS_TEST_SET_INSTANCE_EXTERNAL(name) luanicsTestSetInstance##name

#define LUANICS_BEGIN_TEST_SET(name)\
	luanics::testing::core::Composite LUANICS_TEST_SET_INSTANCE_EXTERNAL(name){#name};\
	namespace {\
		luanics::testing::core::Composite & LUANICS_TEST_SET_INSTANCE = LUANICS_TEST_SET_INSTANCE_EXTERNAL(name);\
		luanics::testing::core::Installer LUANICS_TEST_SET_INSTALLER_INSTANCE{&luanics::testing::unit::suiteInstance, &LUANICS_TEST_SET_INSTANCE};\

#define LUANICS_END_TEST_SET()\
	}

#define LUANICS_TEST_CLASS(name) Luanics##name##Test
#define LUANICS_TEST_INSTANCE(name) luanics##name##TestInstance
#define LUANICS_TEST_INSTALLER_INSTANCE(name) luanics##name##TestInstallerInstance
#define LUANICS_REPORTER luanics##Reporter

#define LUANICS_TEST(name)\
	class LUANICS_TEST_CLASS(name) : public luanics::testing::core::Leaf {\
	public: \
		LUANICS_TEST_CLASS(name)() : Leaf{#name} {} \
		virtual void doRun(luanics::testing::core::Reporter &) override final;\
	}\
	LUANICS_TEST_INSTANCE(name);\
	luanics::testing::core::Installer LUANICS_TEST_INSTALLER_INSTANCE(name){&LUANICS_TEST_SET_INSTANCE, &LUANICS_TEST_INSTANCE(name)};\
	void LUANICS_TEST_CLASS(name)::doRun(luanics::testing::core::Reporter & LUANICS_REPORTER)
