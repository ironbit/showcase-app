cmake_minimum_required(VERSION 3.10.0)

set(STORE_INTERFACE_TEST
		"${CMAKE_CURRENT_SOURCE_DIR}/store_interface_test.cpp"
		"${CMAKE_SOURCE_DIR}/orm/core/property.cpp"
		"${CMAKE_SOURCE_DIR}/orm/test_mock/store_mock/orm/store_mark/store.cpp")

set(STORE_INTERFACE_INCLUDE_DIR
		"${CMAKE_SOURCE_DIR}/orm/test_mock/store_mock")

fnConfigTest(STORE_INTERFACE_TEST "${STORE_INTERFACE_TEST}" "${STORE_INTERFACE_INCLUDE_DIR}")
