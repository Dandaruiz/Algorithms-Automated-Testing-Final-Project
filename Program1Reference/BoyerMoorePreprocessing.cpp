#include "BoyerMoorePreprocessing.h"

#include <algorithm>
#include <map>
#include <string>
#include <vector>
#include <cstring>
#include <bits/stdc++.h>

#include "Zalgorithm.h"

// Input: Pattern P, alphabet Sigma, data structures to store L', l', R
//      P is 1-indexed, so we represent the pattern "abc" by P = " abc"
//      Sigma is 0-indexed, treated as a set of characters
// Output: Pre-processing arrays for the Boyer-Moore Algorithm.
// 			Lprime[i] = L'(i)		(Defined p.20 Gusfield)
// 			lprime[i] = l'(i)		(Defined p.21 Gusfield)
// 			R[x] = R(x) 				(Defined p.17 Gusfield)
void BoyerMoorePreprocessing(
	const std::string& P,
	const std::string& Sigma,
	std::vector<int>* Lprime,
	std::vector<int>* lprime,
	std::map<char, int>* R) {
	std::vector<int> N;
	CalculateN(P, &N);
	CalculateCapitalLprime(P, N, Lprime);
	CalculateLowercaseLprime(P, N, lprime);
	CalculateR(P, Sigma, R);
}

// Input: Pattern P, N values, data structure to store result Lprime[i] = L'(i)
//      P is 1-indexed, so we represent the pattern "abc" by P = " abc"
//      N is 1-indexed, so N[j] = Nj(P)
// Output: Lprime[i] = L'(i)) for all 1 <= i <= n, where n is the length of P
// 			L'(i) is the largest position less than n such that P[i, n] matches
// 			  a suffix of P[i, L'(i)] and the character preceding that suffix
// 			  differs from P(i - 1), or 0 if no such position exists.
void CalculateCapitalLprime(const std::string& P, const std::vector<int>& N, std::vector<int>* Lprime) {
	// TODO: Implement this
		
	  int tempArr[P.size()];

	  for (int i = 1; i < P.size(); i++){
	      tempArr[i] = 0;
	  }

	  for (int i = 1; i < P.size(); i++) {
	    for (int j = 1; j < P.size()-1; j++){
	        i = P.size() -N[j] + 1;
	        tempArr[i] = j;
	    }
	  }

	  for (int i =1; i < P.size(); i++) {
	    Lprime->push_back(tempArr[i]);
	  }

	  Lprime->push_back(0);
}

// Input: Pattern P, N values, data structure to store result lprime[i] = l'(i)
//      P is 1-indexed, so we represent the pattern "abc" by P = " abc"
//      N is 1-indexed, so N[j] = Nj(P)
// Output: lprime[i] = l'(i) for all 1 <= i <= n, where n is the length of P
// 			l'(i) is the largest j <= n - i +1 such that Nj(P) = j
void CalculateLowercaseLprime(const std::string& P, const std::vector<int>& N, std::vector<int>* lprime) {
	lprime->resize(P.length());
	int n = P.length() - 1;
	int j = 0;
	for (int i = 1; i <= n; i++) {
	  if (N[i] == i) {
	      j = i;
	  }
	  (*lprime)[n - i] = j;
	}
}

// Input: Pattern P, data structure to store result N[j] = Nj(P)
//      P is 1-indexed, so we represent the pattern "abc" by P = " abc"
// Output: N[j] = Nj(P) for all 1 <= i <= n, where n is the length of P
// 			Nj(P) is the length of the longest suffix of P[i, j] that is also
// 			a suffix of P
void CalculateN(const std::string& P, std::vector<int>* N) {
	// basically calling Z Algorithm on P reverse
	
	std::string tempP = P;
	std::reverse(tempP.begin(),tempP.end());
	const std::string revP = " "+tempP;
	Zalgorithm(revP, N);
	std::reverse(N->begin(),N->end());
	N->erase(N->end()-1);
}

// Input: Pattern P, alphabet Sigma, data structure to store result R[i] = R(i)
//      P is 1-indexed, so we represent the pattern "abc" by P = " abc"
// Output: R[x] = R(x) for all characters x in Sigma
// 			R(x) is the right-most occurrence of x in P, or 0 if it does not occur in P
void CalculateR(const std::string& P, const std::string& Sigma, std::map<char, int>* R) {
	const char* str1 = Sigma.c_str();
	std::map<char,int>::iterator it;
	for (int i = 0; i < Sigma.length(); i++) {
		char ch = Sigma[i];
		R->insert(std::pair<char,int>(ch, 0));
	}
	for (int i = P.length(); i >= 1; i--) {
		char ch = P[i];
		if ((*R)[ch] != 0) {
			continue;
		}
		else {
			(*R)[ch] = i;
		}
	}
	R->erase(R->begin());
    
}

