cmake_minimum_required(VERSION 3.28)
project(DynamicPartitioning)

set(CMAKE_CXX_STANDARD 17)

add_executable(DynamicPartitioning main.cpp
        Process.h
        PartitionSpace.h
        RAM.h
        CPU.cpp
        CPU.h
        RAM.cpp
        RAMwithOeder.h
        Process.cpp
        PartitionSpace.cpp
        RAMwithBest.h
        RAMwithWorst.h
        Menu.cpp
        Menu.h
)
