cmake_minimum_required(VERSION 3.29)
project(SplitSCM)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- OpenVCDIFF Paths ---
set(OPENVCDIFF_INCLUDE "${CMAKE_SOURCE_DIR}/external/open-vcdiff/include")
set(OPENVCDIFF_LIB "${CMAKE_SOURCE_DIR}/external/open-vcdiff/lib")

# --- Wrap OpenVCDIFF into a single target ---
add_library(vcdiff INTERFACE)
target_include_directories(vcdiff INTERFACE ${OPENVCDIFF_INCLUDE})
target_link_libraries(vcdiff INTERFACE
        ${OPENVCDIFF_LIB}/vcdcom.lib
        ${OPENVCDIFF_LIB}/vcddec.lib
        ${OPENVCDIFF_LIB}/vcdenc.lib
        ${OPENVCDIFF_LIB}/vcdiff.lib
)

# --- Main library for your project ---
add_library(scm_lib
        src/utils/ObjectStore.cpp
        src/stores/Index.cpp
        src/stores/Repository.cpp
        src/utils/DeltaCompressor.cpp
        src/utils/SHA1.h
        src/utils/Hashing.h
        src/utils/Time.h
        src/components/Commit.h
        src/components/Tree.h
)
target_include_directories(scm_lib PUBLIC src ${OPENVCDIFF_INCLUDE})
target_link_libraries(scm_lib PRIVATE vcdiff)

# --- Main executable ---
add_executable(SplitSCM main.cpp)
target_link_libraries(SplitSCM PRIVATE scm_lib)

# --- Enable testing ---
enable_testing()
include(FetchContent)

# Fetch GoogleTest
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

# --- Test executable ---
add_executable(runTests tests/DeltaCompressorTest.cpp)
target_link_libraries(runTests PRIVATE scm_lib gtest_main)

# --- Discover tests automatically ---
include(GoogleTest)
gtest_discover_tests(runTests)
