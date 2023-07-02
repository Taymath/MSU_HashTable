cmake_minimum_required(VERSION 3.23)
project(PRACTICUM)

set(CMAKE_CXX_STANDARD 14)

add_executable(PRACTICUM ListAbstract.h GroupList.h Container.h MemoryManager.h mem.h GroupContainer.h TableAbstract.h Table.h TableList.cpp TableList.h Table.h Table.cpp TableTest.h TableTest.cpp TableTestMain.cpp GroupContainer.cpp GroupList.cpp)
