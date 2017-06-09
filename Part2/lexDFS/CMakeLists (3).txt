cmake_minimum_required (VERSION 3.2) # If your CMake version is older, try modifying this line
project(SuffixTree)

add_definitions(-std=c++1z -g)

########## Create libraries
add_library(suffixTreeLib suffixTree.cpp edge.cpp randomGenerator.cpp )

########## Link GoogleTest
include_directories($ENV{GMOCK_HOME}/gtest/include)
link_directories($ENV{GMOCK_HOME}/gtest/mybuild/)

########## Add unit tests. 
add_executable(lexDFSUnitTest lexDFSUnitTest.cpp)
target_link_libraries(lexDFSUnitTest gtest)
target_link_libraries(lexDFSUnitTest pthread)
target_link_libraries(lexDFSUnitTest suffixTreeLib)
add_custom_command(TARGET lexDFSUnitTest
                   POST_BUILD
                   COMMAND lexDFSUnitTest
                   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                   COMMENT "Running lexDFSUnitTest" VERBATIM)
                   
########## Add unit tests. 
########## add_executable(suffixArrayUnitTests suffixArrayUnitTest.cpp)
########## target_link_libraries(suffixArrayUnitTests gtest)
########## target_link_libraries(suffixArrayUnitTests pthread)
########## target_link_libraries(suffixArrayUnitTests suffixTreeLib)
########## add_custom_command(TARGET suffixArrayUnitTests
##########                    POST_BUILD
##########                    COMMAND suffixArrayUnitTests
##########                    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
##########                    COMMENT "Running suffixArrayUnitTests" VERBATIM)
                   

add_executable(lexDFSsanityCheck lexDFSsanityCheck.cpp suffixTree.cpp)
target_link_libraries(lexDFSsanityCheck gtest)
target_link_libraries(lexDFSsanityCheck pthread)
target_link_libraries(lexDFSsanityCheck suffixTreeLib)

