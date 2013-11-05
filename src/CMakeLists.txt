add_definitions(-pthread -std=c++0x)

add_executable(test
  Class.cpp
  ConstantPool.cpp
  JvmEnv.cpp
)
