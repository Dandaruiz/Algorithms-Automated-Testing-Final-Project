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


TEST(circularLinearizaiton, lexicographicallySmallest) {
    // feed suffices into a map container that will sort it lexicographically for us
    for (int i = 0; i < 10000; i++) {
        std::string substring = "";
        std::map<string,int> patternMap; 
        
        std::string text = randTextGen();
        std::string pattern = randPatternGen(text);
        
        std::vector<int> checkerSuffixArray;
        std::string tempString = "";
        std::map<string,int> orderedStrings;
        text = text+"$";
        for (int i = 0; i < text.length(); i++) {
            tempString = text.substr(i,text.length());
            orderedStrings[tempString] = text.length()-tempString.length();
            tempString = "";
    
        }
        // first key will be the lexicographically smallest
        for (auto it = orderedStrings.begin(); it != orderedStrings.end(); ++it) {
            checkerSuffixArray.push_back(it->second);
        }
        
        std::vector<int> suffixArray = runArray(text);
        
        
        //ASSERT_EQ(suffixArray.size(),checkerSuffixArray.size());
        cout << suffixArray.size() << " " << checkerSuffixArray.size() << endl;
        for (int i = 0; i < checkerSuffixArray.size(); i++) {
            //EXPECT_EQ(suffixArray[i],checkerSuffixArray[i]);
        }
        //if (i > 9990) {
            cout << "text: " << text << endl;
            cout << "dfs suffix array: " << endl;
            for (int i = 0; i < suffixArray.size(); i++) {
                cout << suffixArray[i] << " ";
            }
            cout << endl;
            cout << "naive suffix array: " << endl;
            for (int i = 0; i < checkerSuffixArray.size(); i++) {
                cout << checkerSuffixArray[i] << " ";
            }
            cout << endl;
            
        //}
        // std::string lexString = runLex(pattern);
        // EXPECT_EQ(lexicographical_compare(lexString, pattern), true);
     }
}



int main(int argc, char** argv) {
   testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}