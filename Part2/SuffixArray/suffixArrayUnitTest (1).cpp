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

extern std::vector<int> runArray(string text);
extern std::string randTextGen();
extern std::string randPatternGen(std::string text);
extern std::string randPermTextGen(); 



TEST(suffixArrayUnitTest, lexicographicallySmallest) {
    // custom random text and pattern generators
    // pattern takes test as arg to product pattern
    std::string text = "aaaa$";
    int array [] = {4,3,2,1,0};
    std:vector <int> returnSuffixArray = runArray(text);
    for( int i = 0; i < text.length(); i++)
    {
        cout << returnSuffixArray[i] << endl;
        EXPECT_EQ(array[i], returnSuffixArray[i]);
    }

}

TEST(suffixArrayUnitTest, generateRandomPermutatedString) 
{
    // int count;
    // for (int i = 0; i < 10000; i++) {

    // std::string permText = randPermTextGen();
    // std::vector<int> suffixArrayresult = runArray(permText);
        
    // // checkerSuffixArray will be the map generated indexed array
    // std::vector<int> checkerSuffixArray;
    // std::string tempString = "";
    // std::map<string,int> orderedStrings;
    
    // for (int i = 0; i < permText.length(); i++) {
    //     tempString = permText.substr(i,permText.length());
    //     orderedStrings[tempString] = permText.length()-tempString.length();
    //     tempString = "";
    // }
    // // first key will be the lexicographically smallest
    // for (auto it = orderedStrings.begin(); it != orderedStrings.end(); ++it) {
    //     checkerSuffixArray.push_back(it->second);
    // }

    // bool checker = true;
    //     //ASSERT_EQ(suffixArray.size(),checkerSuffixArray.size());
    // for (int i = 0; i < checkerSuffixArray.size(); i++) {
    //     if (suffixArrayresult[i] != checkerSuffixArray[i]) {
    //         checker = false;
    //     }
    //     else {
    //         continue;
    //     }
    // }
    // if (checker) {
    //     count++;
    // }
    // if (i > 9990) {
    //         // for (int i = 0; i < suffixArrayresult.size(); i++) {
    //         //     cout << suffixArrayresult[i] << " ";
    //         // }
    //         // cout << endl;
    //         // cout << "naive suffix array: " << endl;
    //         // cout << "count right: " << count << endl;
    //         // for (int i = 0; i < checkerSuffixArray.size(); i++) {
    //         //     cout << checkerSuffixArray[i] << " ";
    //         // }
    //         // cout << endl;
            
    // }
//}

}
int main(int argc, char** argv) {
   testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}