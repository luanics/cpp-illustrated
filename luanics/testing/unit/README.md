# luanics::testing::unit

Unit-test framework based on luanics::testing::core framework. Provides a testing hierarchy with three levels:
1. Test Suite - Holds Test Sets.
2. Test Set - A group of Tests focused on a single class/file.
3. Test - A single Test.

The macros provided register the Test Sets with a single global Test Suite instance, declared in luanics/testing/unit/Instance.hpp.