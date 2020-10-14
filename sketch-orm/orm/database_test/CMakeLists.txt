cmake_minimum_required(VERSION 3.10.0)

set(DATABASE_TEST
   "${CMAKE_CURRENT_SOURCE_DIR}/database_test.cpp"
   "${CMAKE_SOURCE_DIR}/orm/core/property.cpp"
   "${CMAKE_SOURCE_DIR}/orm/core/scalar.cpp"
   "${CMAKE_SOURCE_DIR}/orm/database_mark/database.cpp")

fnConfigTest(DATABASE_TEST "${DATABASE_TEST}" "")
