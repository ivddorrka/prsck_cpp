cmake_minimum_required(VERSION 3.23)

set(PROJECT_NAME proxycpp)
project(${PROJECT_NAME} C CXX)


set(CMAKE_CXX_STANDARD 17)


###### sanitizers

set(WARNINGS_AS_ERRORS OFF)
#! UndefinedBehaviorSanitizer (UBSan)
#  Info: https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html
set(ENABLE_UBSan OFF)
#! AddressSanitizer -- detects use after free or after scope exit,
#  memory overflows and leaks.
#  Info: https://github.com/google/sanitizers/wiki/AddressSanitizer
set(ENABLE_ASAN OFF)
#! ThreadSanitizer -- detects data races.
set(ENABLE_TSan OFF)
#! MemorySanitizer detects uninitialized memory reads
#  Info: https://github.com/google/sanitizers/wiki/MemorySanitizer
set(ENABLE_MSAN OFF)

###### sanitizers end



if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()


add_executable(proxycpp main.cpp src/proxysocket.h)
target_include_directories(${PROJECT_NAME} PRIVATE src)



INSTALL(PROGRAMS
        $<TARGET_FILE:${PROJECT_NAME}>	# ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}
        DESTINATION bin)


# Define ALL_TARGETS variable to use in Sanitizers
set(ALL_TARGETS ${PROJECT_NAME})