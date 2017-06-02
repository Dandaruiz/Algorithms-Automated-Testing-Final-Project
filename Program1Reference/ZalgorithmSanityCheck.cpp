#include "Zalgorithm.h"
#include "gtest/gtest.h"

using testing::Test;

#include <algorithm>
#include <random>
#include <string>
#include <time.h>
#include <stdlib.h>

#define NUM_TEST_CASES 10000
#define RANDOM_STRING_SIZE 100

// Sanity check for ZalgorithmBasedMatching.
// Does NUM_TEST_CASES times:
//    1) Generate random string T of size RANDOM_STRING_SIZE
//    2) Generate a random substring P of T
//    3) Runs ZalgorithmBasedMatching and checks there is at least one match
// Use <random> & uniform_int_distribution for your random number generation
TEST(ZalgorithmSanityCheck, SubstringMatchesInRandomString) {
    for (int i = 0; i < NUM_TEST_CASES; i++) {
        int pos1,pos2;
        std::string P = " ";
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, RANDOM_STRING_SIZE);
        std::list<int> matches;
        bool checker = false;
        std::string T = " ";
        static const char alphanum[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
        std::uniform_int_distribution<> cis(0,(sizeof(alphanum) - 1));
        for (int i = 0; i < RANDOM_STRING_SIZE; i++) {
            T = T+alphanum[cis(gen)];
        }
        pos1 = dis(gen);
        pos2 = dis(gen);
        if (pos2 > pos1) {
            P += T.substr(pos1,pos2);
        }
        else {
            P += T.substr(pos2,pos1);
        }
        ZalgorithmBasedMatching(P,T,&matches);
        EXPECT_GE(matches.size(),1);
    }
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
