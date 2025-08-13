cmake_minimum_required(VERSION 3.29)
project(SplitSCM)

set(CMAKE_CXX_STANDARD 20)

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
        src/utils/Delta.h
        src/utils/DeltaInstruction.h)
