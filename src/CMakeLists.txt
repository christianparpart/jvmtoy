add_definitions(-pthread -std=c++0x)

add_library(jvm SHARED Class.cpp ConstantPool.cpp JvmEnv.cpp)

add_executable(test test.cpp)
target_link_libraries(test jvm)
