#include <list>
#include <string>
#include <vector>
#include <iterator>

#include "Zalgorithm.h"

// Input: Pattern P, text T, data structure matches to store result
//      P is 1-indexed, so we represent the pattern "abc" by P = " abc"
//      T is also 1-indexed
// Output: Indices corresponding to occurrances of P in T
void ZalgorithmBasedMatching(const std::string& P, const std::string& T, std::list<int>* matches) {
    std::vector<int> v;
    std::string S = P+T;
    Zalgorithm(S,&v);
    std::vector<int>::iterator it;
    int count = 1;
    for(it = v.begin(); it != v.end(); it++)
    {
        if(*it == P.length()-1 && count > P.length())
        {
            matches->push_back(count-P.length()-1);
        }
        count++;
    }
}

// Input: String S, data structure Z to store result
//      S is 1-indexed, so we represent the string "abc" by S = " abc"
// Output: Indices corresponding to occurrances of P in T
void Zalgorithm(const std::string& S, std::vector<int>* Z) {
    int l = 0, r = 0;
    Z->resize(S.length());
    for (int k = 2; k < S.length(); k++) {
        if (k > r) {
            (*Z)[k] = MatchLength(S, 1, k);
            if ((*Z)[k] > 0) {
                l = k;
                r = l + (*Z)[k] - 1;
            }
        } else {
            int beta = r - k + 1;
            int kprime = k - l + 1;
            if ((*Z)[kprime] < beta) {
                (*Z)[k] = (*Z)[kprime];
            } else {
                int q = r + MatchLength(S, beta, r);
                l = k;
                r = q - 1;
                (*Z)[k] = q - k;
            }
        }
    }
}

// Input: String S, positions i and j of S
//      S is 1-indexed, so we represent the string "abc" by S = " abc"
// Output: length of longest common prefix of S[i, n] and S[j, n] where n = |S|
int MatchLength(const std::string& S, int i, int j) {
    int result;
    for (result = 0;i + result < S.length() && j + result < S.length() && S[i + result] == S[j + result]; result++) {
        
    }
    return result;
}
