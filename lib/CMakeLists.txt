set(INCLUDE ${CMAKE_CURRENT_SOURCE_DIR})
set(SOURCE ${INCLUDE}/lib)

add_library(lib)
target_sources(lib PRIVATE "${SOURCE}/lib.cpp" "${SOURCE}/lib.hpp")
target_include_directories(lib PUBLIC ${INCLUDE})
target_link_libraries(lib PUBLIC  Boost::boost)
add_library(lib::lib ALIAS lib)

add_executable(lib_test)
target_sources(lib_test PRIVATE "${SOURCE}/lib.test.cpp" "${SOURCE}/main.test.cpp")
target_link_libraries(lib_test PRIVATE lib::lib Boost::unit_test_framework)
add_test(NAME lib::test COMMAND lib_test "--color_output=false")

find_package(rapidcheck)

add_executable(lib_pbt)
target_sources(lib_pbt PRIVATE "${SOURCE}/lib.pbt.cpp")
target_link_libraries(lib_pbt PRIVATE lib::lib rapidcheck)
add_test(NAME lib::pbt COMMAND lib_pbt)
