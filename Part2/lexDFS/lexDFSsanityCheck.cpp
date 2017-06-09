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

extern std::string runLex(string text);
extern std::string randTextGen();
extern std::string randPatternGen(std::string text);

// check 10,000 strings and lexicographically compare it to the output
// of runLex to check that the output of the program is always lex.
// smaller than the original inputted string.


TEST(lexDFSSanityCheck, RandomStringIsLexicographicallyOrdered) {
    // custom random text and pattern generators
    // pattern takes test as arg to product pattern
    
     for (int i = 0; i < 10000; i++) {
        std::string text = randTextGen();
        // use naive method for comparison
        std::string checkerSmallestString = "";
        std::string text2 = text+text;
        std::string tempString = "";
        std::map<string,int> orderedStrings;
    
        for (int i = 0; i < text.length(); i++) {
            tempString = text2.substr(i,text.length());
            orderedStrings[tempString] = i;
            tempString = "";
    
        }
        // first key will be the lexicographically smallest
        for (auto it = orderedStrings.begin(); it != orderedStrings.end(); ++it) {
            checkerSmallestString = it->first;
            break;
    
        }
        
        std::string smallestString = runLex(text);
        EXPECT_EQ(smallestString, checkerSmallestString);
        // display results
        if (i > 9990) {
            cout << "iteration: " << i << endl;
            cout << "smallestString: " << smallestString << endl;
            cout << "checkerSmallestString: " << checkerSmallestString << endl;
        }
     }
}

int main(int argc, char** argv) {
   testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}