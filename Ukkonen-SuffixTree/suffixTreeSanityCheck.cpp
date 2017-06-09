#include "suffixTree.h"
#include "edge.h"
#include "gtest/gtest.h"
//#include "randomGenerator.h"

using testing::Test;
#include <iostream>
#include <algorithm>
#include <random>
#include <string>
#include <list>
#include <chrono>
#include <random>
#include <unordered_map>

extern bool runPart1(string text,string pattern);
extern std::string randTextGen();
extern std::string randPatternGen(std::string text);

//Write a sanity test that creates thousands of test cases 
//(or more) of a text T and a pattern P that matches T and 
//ensure that the 3rd-party code you have downloaded 
//determines that P matches T.

// #define NUM_TEST_CASES 10000
// #define RANDOM_STRING_SIZE 100

TEST(suffixTreeSanityCheck, SubstringMatchesInRandomString) {
    // custom random text and pattern generators
    // pattern takes test as arg to product pattern
    
    for (int i = 0; i < 10000; i++) {
        std::string text = randTextGen();
        std::string pattern = randPatternGen(text);
        EXPECT_EQ(runPart1(text,pattern),true);
        // // display results
        // if (i > 9990) {
        //     cout << "iteration: " << i << endl;
        //     cout << "text: " << text << endl;
        //     cout << "pattern: " << pattern << endl;
        //     if (runPart1(text,pattern)) {
        //         cout << "match found in search function" << endl;
        //     }
        // }
    }
}

int main(int argc, char** argv) {
   testing::InitGoogleTest(&argc, argv);

   return RUN_ALL_TESTS();
}
