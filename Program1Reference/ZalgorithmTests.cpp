#include "Zalgorithm.h"
#include "gtest/gtest.h"

#include <string>

using testing::Test;

// Testing MatchLength calculation when no matches occur
TEST(MatchLengthTest, NoMatchTest) {
    
    bool checker = true;
    const std::string& S = " abc";
    int i = 1;
    int j = 2;
    //result should be equal to zero
    if (MatchLength(S,i,j) == 0) {
        checker = false;
    }
    
    EXPECT_EQ(checker,false);
}

// Testing MatchLength calculation when geginning of string matches
TEST(MatchLengthTest, BeginningStringMatch) {
    
    bool checker = false;
    const std::string& S = " aab";
    int i = 1;
    int j = 2;
    
    if (MatchLength(S,i,j) == 1) {
        checker = true;
    }
    
    EXPECT_EQ(checker, true);
}

// Testing MatchLength calculation when middle of the string matches
TEST(MatchLengthTest, MidStringMatch) {
    
    bool checker = false;
    
    const std::string& S = " caacaad";
    int i = 1;
    int j = 4;
    int result =  MatchLength(S,i,j);
    if ((S.length()-1) % 2 !=0 && (((S.length()-1)/2)+1 == j) && result == 3) {
        checker = true;
    }
    
    EXPECT_EQ(checker, true);
}

// Testing MatchLength calculation when match stops at end of string
TEST(MatchLengthTest, EndOfStringMatch) {
    
    bool checker = false;
    
    const std::string& S = " abbabb";
    int i = 1;
    int j = 4;
    int result = MatchLength(S, i, j);
    
    if ( j+result == S.length()) {
        checker = true;
    }
    
    EXPECT_EQ(checker, true);
}

// Testing Zalgorithm calculation with string S = " aabcaabxaaz", p.7 Gusfield
TEST(ZalgorithmTest, GusfieldExamplePageSeven) {
    std::vector<int> Z;
    
    std::string S = " aabcaabxaaz";
    int CheckArray[] = {0,0,1,0,0,3,1,0,0,2,1,0};
    int count=0;
    int i = 0;
    bool checker = true;
    Zalgorithm(S, &Z);
    
    std::vector<int>::iterator it;
    
    for (it = Z.begin(); it != Z.end();it++) {
        if (CheckArray[i] != *it) {
            checker = false;
        }
        i++;
    }
    
    
    EXPECT_EQ(checker, true);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
