cmake_minimum_required(VERSION 3.10.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_COMPILER $ENV{CXX})
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

function(fnConfigTest TEST_NAME TEST_SOURCE TEST_INCLUDE_DIR)
	add_executable(${TEST_NAME} ${TEST_SOURCE})

	string(COMPARE NOTEQUAL "${TEST_INCLUDE_DIR}" "" result)
	if (result)
		target_include_directories(${TEST_NAME} PUBLIC ${TEST_INCLUDE_DIR})
	endif()

	target_include_directories(${TEST_NAME} PUBLIC ${CMAKE_SOURCE_DIR})

	target_link_libraries(${TEST_NAME} gmock gtest gtest_main pthread)

	add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endfunction(fnConfigTest)

enable_testing()
add_subdirectory(${CMAKE_SOURCE_DIR}/orm/database_test)
add_subdirectory(${CMAKE_SOURCE_DIR}/orm/store_test)
