# Source code for the "C++ Illustration" book examples

macro(create_executable target_name target_source)
	message(STATUS "creating ${target_name} with ${target_source}")
	add_executable(${target_name} ${target_source})
	target_link_libraries(${target_name} luanics stdc++fs pthread)
	set_target_properties(${target_name} PROPERTIES OUTPUT_NAME ${target_name}${BUILD_POSTFIX})
endmacro(create_executable)

# Basics
#create_executable(building_main basics/building/Main.cpp;basics/building/Car.cpp)
add_executable(building_main basics/building/Main.cpp basics/building/Car.cpp)
target_link_libraries(building_main luanics stdc++fs)
set_target_properties(building_main PROPERTIES OUTPUT_NAME building_main${BUILD_POSTFIX})
create_executable(building_main_with_args basics/building/MainWithArgs.cpp)
create_executable(people basics/names/People.cpp)
create_executable(namespaces basics/names/Namespaces.cpp)
create_executable(puzzle basics/names/Puzzle.cpp)
create_executable(puzzle2 basics/names/Puzzle2.cpp)
create_executable(scope_and_name_hiding basics/names/ScopeAndNameHiding.cpp)
create_executable(references basics/References.cpp)
create_executable(statements basics/statements/Statements.cpp)
create_executable(statements_example_program basics/statements/Greetings.cpp)
create_executable(preprocessor basics/Preprocessor.cpp)
create_executable(directives basics/Directives.cpp)
create_executable(variables basics/Variables.cpp)
create_executable(objects basics/Objects.cpp)

# Metaprogramming
create_executable(policies metaprogramming/Policies.cpp)

# More Basics
create_executable(integral_types more_basics/IntegralTypes.cpp)
create_executable(floating_point_types more_basics/FloatingPointTypes.cpp)
create_executable(control_flow more_basics/ControlFlow.cpp)
create_executable(cryptography more_basics/Cryptography.cpp)
create_executable(expressions more_basics/Expressions.cpp)
create_executable(functions more_basics/Functions.cpp)
create_executable(classes more_basics/Classes.cpp)
create_executable(introspection more_basics/Introspection.cpp)
create_executable(operators more_basics/Operators.cpp)
create_executable(types more_basics/Types.cpp)

# Not So Basics
create_executable(management_methods not_so_basics/ManagementMethods.cpp)
create_executable(conversions not_so_basics/Conversions.cpp)
create_executable(library not_so_basics/Library.cpp)
create_executable(names not_so_basics/Names.cpp)
create_executable(type_deduction not_so_basics/TypeDeduction.cpp)
create_executable(logging not_so_basics/Logging.cpp)
add_subdirectory(not_so_basics/names)
add_subdirectory(not_so_basics/testing)

# Performance
create_executable(cache_effects performance/CacheEffects.cpp)
create_executable(custom_allocator performance/CustomAllocator.cpp)
create_executable(profiling performance/Profiling.cpp)
