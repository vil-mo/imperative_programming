cmake_minimum_required(VERSION 3.27)
project(task1 C)

set(CMAKE_C_STANDARD 11)

include_directories(task1)

add_executable(task1
        task1/integerset.c
        task1/sample.c
        )

cmake_minimum_required(VERSION 3.27)
project(task2 C)

set(CMAKE_C_STANDARD 11)

include_directories(task2)

add_executable(task2
        task2/main.c
        task2/matrixsqr.c
)