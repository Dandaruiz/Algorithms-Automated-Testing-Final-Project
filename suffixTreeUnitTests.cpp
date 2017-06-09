#include "suffixTree.h"
#include "edge.h"
#include "gtest/gtest.h"
using testing::Test;
#include <iostream>
#include <algorithm>
#include <random>
#include <string>
#include <list>
#include <chrono>
#include <unordered_map>
//#include "randomGenerator.h"


extern bool runPart1(string text,string pattern);
extern std::string randTextGen();
extern std::string randPatternGen(std::string text);


TEST(CheckPatternInSuffixTreeTest, patternLargerText) {
    for (int i = 0; i < 1000; i++) {
        std::string text = randTextGen();
        // pattern is larger than text
        std::string pattern = text+text;
        // should always return false
        EXPECT_EQ(runPart1(text,pattern),false);
        // // display results
        // if (i > 990) {
        //     cout << "iteration: " << i << endl;
        //     cout << "text: " << text << endl;
        //     cout << "pattern: " << pattern << endl;
        //     if (!runPart1(text,pattern)) {
        //         cout << "match not found" << endl;
        //     }
        // }
    }
}

TEST(CheckPatternInSuffixTreeTest, patternNotInAlphabet) {
    for (int i = 0; i < 1000; i++) {
        std::string text = randTextGen();
        std::string pattern = "#$&#@";
        // should always return false
        EXPECT_EQ(runPart1(text,pattern),false);
        // // display results
        // if (i > 990) {
        //     cout << "iteration: " << i << endl;
        //     cout << "text: " << text << endl;
        //     cout << "pattern: " << pattern << endl;
        //     if (!runPart1(text,pattern)) {
        //         cout << "match not found" << endl;
        //     }
        // }
    }
}