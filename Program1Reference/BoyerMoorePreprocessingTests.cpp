#include "BoyerMoorePreprocessing.h"
#include "gtest/gtest.h"

using testing::Test;

// Unit tests for BoyerMoorePreprocessing. Because unit tests are a first line
// of defense, ideally, each test should:
//  1) Be deterministic (For consistent results)
//  2) Test exactly one thing (To quickly diagnose bugs)
//  3) Run quickly, ex. ~0-1ms per test (To minimize overhead while compiling with make)

// Testing L' calculation with string P = " cabdabdab", P.20 Gusfield
TEST(CalculateCapitalLprimeTest, GusfieldExamplePageTwenty) {
    bool checker = true;
    const std::string& P = " cabdabdab";
    std::vector<int> N;
    std::vector<int> Lprime;
    int lprimeArray[] = {0,0,0,0,0,6,0,0,3,0};   
    CalculateN(P, &N);
    //calculate N to pass into CalculateLowercaseLprime
    CalculateCapitalLprime(P, N, &Lprime);

    ASSERT_EQ(Lprime.size(),sizeof(lprimeArray)/4);
    for (int i = 1; i < P.length(); i++) {
        if (Lprime[i] != lprimeArray[i]) {
            checker = false;
        }
    }
    EXPECT_EQ(checker,true);
}

// Testing L' calculation with string P = " dabcdbdab"
TEST(CalculateLowercaseLprimeTest, Pattern_dabcdbdab) {
    // TODO: Implement this. Check the entire L' vector
    bool checker = true;
    const std::string& P = " dabcdbdab";
    std::vector<int> N;
    std::vector<int> Lprime;
    int lprimeArray[] = {3,3,3,3,3,3,3,0,0,0};   
    CalculateN(P, &N);
    CalculateLowercaseLprime(P, N, &Lprime);
    ASSERT_EQ(Lprime.size(),sizeof(lprimeArray)/4);
    for (int i = 1; i < P.length(); i++) {
        if (Lprime[i] != lprimeArray[i]) {
          checker = false;
        }
    }
    EXPECT_EQ(checker,true);
}

// Testing N calculation with string P = " cabdabdab", p. 21 Gusfield
TEST(CalculateNTest, GusfieldExamplePageTwentyOne) {
    // TODO: Implement this. Check only values given in the text
    bool checker = true;
    const std::string& P = " cabdabdab";
    std::vector<int> N;
    int i = 0;
    //values given in text for N[j] = Nj(P):
    // N[3] = 2 & N[6] = 5
    int CheckArray[] = {0,0,0,2,0,0,5,0,0,0};
    
    CalculateN(P, &N);   
    // check output of N with CheckArray
    std::vector<int>::iterator it;
    
    for (it = N.begin(); it !=N.end(); it++)
    {
        if (CheckArray[i] != *it ) {
          checker = false;
        }
        i++;
    }
    EXPECT_EQ(checker,true);
    
}

// Testing R calculation with an empty pattern P
TEST(CalculateRTest, EmptyPattern) {
    // TODO: Implement this
    bool checker = true;
    const std::string emptyP = " ";
    const std::string Sigma = " abcdefghijklmnopqrstuvwxyz";
    std::map<char,int> testR;   
    std::map<char,int> R;
    for (int i = 0; i < Sigma.length(); i++) {
        char ch = Sigma[i];
        testR.insert(std::pair<char,int>(ch, 0));
    }
    CalculateR(emptyP,Sigma, &R);
    // R should return R[' '] = 0;
    for (int i = 0; i < Sigma.length(); i++) {
        char ch = Sigma[i];
        if (testR[ch] != R[ch]) {
          checker = false;
        }
    }
    EXPECT_EQ(checker, true);
}

// ( Testing R calculation with a pattern P that is a single character
TEST(CalculateRTest, SingleCharacterPattern) {
    // TODO: Implement this
    bool checker = true;
    std::map<char,int> R;
    std::string singleP = " a";
    const std::string Sigma = " abcdefghijklmnopqrstuvwxyz";
    std::map<char, int> testR;
    for (int i = 0; i < Sigma.length(); i++) {
        char ch = Sigma[i];
        if (i == 1) {
            testR.insert(std::pair<char,int>(ch, 1));
        }
        else {
            testR.insert(std::pair<char,int>(ch, 0));
        }
    }
    CalculateR(singleP,Sigma, &R);
    ASSERT_EQ(R.size(), Sigma.length());
    for (int i = 0; i < Sigma.length(); i++) {
        char ch = Sigma[i];
        if (testR[ch] != R[ch]) { 
          checker = false;
        }
    }
    EXPECT_EQ(checker, true);
}

// Testing R calculation with a pattern P that has at least
//  one character that appears two or more times
TEST(CalculateRTest, RepeatedCharacterPattern) {
    bool checker = true;
    std::map<char,int> R;
    const std::string P = " dabcdbdab";
    const std::string Sigma = " abcdefghijklmnopqrstuvwxyz";
   // std::map<char,int> testR;
    int checkArray[] = { 0,8,9,4,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
    CalculateR(P,Sigma, &R);
     for (int i = 0; i < Sigma.length(); i++) {
        char ch = Sigma[i];
        if (checkArray[i] != R[ch]){
          checker = false;
        }
    }
    EXPECT_EQ(checker, true);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
