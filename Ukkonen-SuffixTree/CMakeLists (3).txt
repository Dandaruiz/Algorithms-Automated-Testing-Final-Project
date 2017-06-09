cmake_minimum_required (VERSION 3.2) # If your CMake version is older, try modifying this line
project(SuffixTree)

add_definitions(-std=c++1z -g)

########## Create libraries
add_library(suffixTreeLib suffixTreeSanityCheck.cpp suffixTree.cpp edge.cpp randomGenerator.cpp )


########## Link GoogleTest
include_directories($ENV{GMOCK_HOME}/gtest/include)
link_directories($ENV{GMOCK_HOME}/gtest/mybuild/)

########## Add unit tests. 
add_executable(suffixTreeUnitTests suffixTreeUnitTests.cpp)
target_link_libraries(suffixTreeUnitTests gtest)
target_link_libraries(suffixTreeUnitTests pthread)
target_link_libraries(suffixTreeUnitTests suffixTreeLib)
add_custom_command(TARGET suffixTreeUnitTests
                   POST_BUILD
                   COMMAND suffixTreeUnitTests
                   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                   COMMENT "Running suffixTreeUnitTests" VERBATIM)

########## Add unit tests. The custom command runs the unit tests every time we use make to compile
add_executable(suffixTreeSanityCheck suffixTreeSanityCheck.cpp suffixTree.cpp )
target_link_libraries(suffixTreeSanityCheck gtest)
target_link_libraries(suffixTreeSanityCheck pthread)
target_link_libraries(suffixTreeSanityCheck suffixTreeLib)




