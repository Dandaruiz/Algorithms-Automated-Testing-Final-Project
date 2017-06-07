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


extern bool run(string text,string pattern);
extern std::string randTextGen();
extern std::string randPatternGen(std::string text);


TEST(CheckPatternInSuffixTreeTest, patternLargerText) {
    
    std::string text = randTextGen();
    // pattern is larger than text
    std::string pattern = text+text;
    // should always return false
    EXPECT_EQ(run(text,pattern),false);
}

TEST(CheckPatternInSuffixTreeTest, patternNotInAlphabet) {
    std::string text = randTextGen();
    std::string pattern = "#$&#@";
    cout<<"CheckPatternInSuffixTreeTest"<<endl;
    cout<<"text: "<<text<<endl;
    cout<<"pattern: "<<pattern<<endl;
    // should always return false
    EXPECT_EQ(run(text,pattern),false);
}