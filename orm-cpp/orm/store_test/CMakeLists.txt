cmake_minimum_required(VERSION 3.10.0)

set(STORE_INTERFACE_TEST
   "${CMAKE_CURRENT_SOURCE_DIR}/store_interface_test.cpp"
   "${CMAKE_SOURCE_DIR}/orm/core/property.cpp"
   "${CMAKE_SOURCE_DIR}/orm/core/scalar.cpp"
   "${CMAKE_SOURCE_DIR}/orm/store_test/person.cpp"
   "${CMAKE_SOURCE_DIR}/orm/test_mock/store_mock/orm/store_mark/store.cpp")

set(STORE_INTERFACE_INCLUDE_DIR
   "${CMAKE_SOURCE_DIR}/orm/test_mock/store_mock")

fnConfigTest(STORE_INTERFACE_TEST "${STORE_INTERFACE_TEST}" "${STORE_INTERFACE_INCLUDE_DIR}")


set(STORE_TEST
   "${CMAKE_CURRENT_SOURCE_DIR}/store_test.cpp"
   "${CMAKE_SOURCE_DIR}/orm/core/property.cpp"
   "${CMAKE_SOURCE_DIR}/orm/core/scalar.cpp"
   "${CMAKE_SOURCE_DIR}/orm/database_mark/database.cpp"
   "${CMAKE_SOURCE_DIR}/orm/memory/data.cpp"
   "${CMAKE_SOURCE_DIR}/orm/memory_mark/record.cpp"
   "${CMAKE_SOURCE_DIR}/orm/store_mark/factory.cpp"
   "${CMAKE_SOURCE_DIR}/orm/store_mark/store.cpp")

fnConfigTest(STORE_TEST "${STORE_TEST}" "")
