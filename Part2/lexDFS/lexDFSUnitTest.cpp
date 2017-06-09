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
extern std::string randPermTextGen();


// possible unit test case: 
// test for null or invalid characters?
// maybe test for strings up to length 10 instead of 10,000 strings all at length 10
// or check that one string permutated multiple times will return the same output


TEST(lexDFSTest, lexicographicallySmallest) {
    // custom random text and pattern generators
    // pattern takes test as arg to product pattern
    std::string text = "aaaa";
    std::string checkerSmallestString = "aaaa";
    std::string smallestString= runLex(text);
    cout << "checker: " << checkerSmallestString << endl;
    cout << "smallest string: " << smallestString << endl;
    EXPECT_EQ(smallestString, checkerSmallestString);

}

TEST(lexDFSUnitTest, generateRandomPermutatedString) 
{
    // generate 10,000 strings or variable length up to 10
    for (int i = 0; i < 1000; i++) {

        std::string permText = randPermTextGen();
        std::string smallestString = runLex(permText);
        
        // checkerSuffixArray will be the map generated indexed array
        std::string checkerSmallestString = "";
        std::string text2 = permText+permText;
        std::string tempString = "";
        std::map<string,int> orderedStrings;
    
        for (int i = 0; i < permText.length(); i++) {
            tempString = text2.substr(i,permText.length());
            orderedStrings[tempString] = i;
            tempString = "";
    
        }
        // first key will be the lexicographically smallest
        for (auto it = orderedStrings.begin(); it != orderedStrings.end(); ++it) {
            checkerSmallestString = it->first;
            break;
    
        }
        ASSERT_EQ(checkerSmallestString.size(),smallestString.size());
        
        if (i > 990) {
            cout << "iteration: " << i << endl;
            cout << "checker: " << checkerSmallestString << endl;
            cout << "smallest string: " << smallestString << endl;
            
        }
    
        EXPECT_EQ(smallestString, checkerSmallestString);
    }

}

int main(int argc, char** argv) {
   testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}