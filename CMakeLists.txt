cmake_minimum_required(VERSION 3.29)
project(SplitSCM)

set(CMAKE_CXX_STANDARD 20)

# Path to OpenVCDIFF
set(OPENVCDIFF_INCLUDE "${CMAKE_SOURCE_DIR}/external/open-vcdiff/include")
set(OPENVCDIFF_LIB "${CMAKE_SOURCE_DIR}/external/open-vcdiff/lib")

add_executable(SplitSCM main.cpp
        src/utils/ObjectStore.cpp
        src/utils/ObjectStore.h
        src/components/Tree.h
        src/components/Commit.h
        src/stores/CommitHistory.h
        src/stores/Index.h
        src/stores/Index.cpp
        src/stores/Repository.cpp
        src/stores/Repository.h
        src/utils/DeltaCompressor.h
        src/utils/Hashing.h
        src/utils/SHA1.h
        src/utils/Time.h
        src/utils/DeltaCompressor.cpp
)

# Add OpenVCDIFF include directory
target_include_directories(SplitSCM PRIVATE ${OPENVCDIFF_INCLUDE})

# Link OpenVCDIFF static libraries
target_link_libraries(SplitSCM
        ${OPENVCDIFF_LIB}/vcdcom.lib
        ${OPENVCDIFF_LIB}/vcddec.lib
        ${OPENVCDIFF_LIB}/vcdenc.lib
        ${OPENVCDIFF_LIB}/vcdiff.lib
)