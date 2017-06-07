// circular string

#include "suffixTree.h"
#include <iostream>
#include <unordered_map> // Required c++11 support.
#include <string>
#include <cassert>
#include <ctime>
#include <chrono>
#include <random>
#include <string>


//bool search(string pattern, string Input, unordered_map <long, Edge> &hash) {

std::string circStringLinearization()
{
    std::unordered_map <long, Edge> edgeHash;
    static const char alphanum[] = "abcdefghijklmnopqrstuvwxyz";
    //std::string text = randTextGen();
    
    std::string text = "aab";
    std::string circText = text+text+"#";
    
    int iter = circText.length() - text.length(); 
    int ValArray[iter] = {};

    cout << "circText is; " << circText << endl;


    // find the lexically smallest substring:
    // testArray to store all possible substrings of circText
    // circular string
}

// std::string returnMinString(std::string testString, int iter)
// {
    
    
    
    
    
    
    
// }



int main()
{
    //std::unordered_map <long, Edge> edgeHash;
    static const char alphanum[] = "abcdefghijklmnopqrstuvwxyz";
    //std::string text = randTextGen();
    
    string text = "aab";
    string circText = text+text+"#";
    
    int iter = circText.length() - text.length(); 
    int ValArray[iter];

    cout << "circText is; " << circText << endl;

    int sum1 = 122; //'z'
    int sum2 = 122+122; // 'z'+'z'
    int sum3 = 122+122+122; // 'z'+'z'+'z'
    string minString = "zzz";
    // find the lexically smallest substring:
    // testArray to store all possible substrings of circText
    string testStr;
    for ( int i = 0; i < iter; i++)
    {
        testStr = circText.substr(i, 3);
        cout << "testStr is: " << testStr << endl;



            // calculate and store the values for each testArray
            for ( int j = 0; j < iter; j++)
            {
                //check to see if our current lexicograph value is bigger than the one we give it
                //cout << (int) testStr[0] << endl;
                if ((int)testStr[0] != 36)
                {
                    if (sum1 > (int) testStr[0])
                {
                    cout << "in if with : " << (int) testStr[0] << endl;
                    sum1 = (int)testStr[0];
                
                    if (sum2 > (int) testStr[0] + (int) testStr[1])
                    {
                        sum2 = (int) testStr[0] + (int) testStr[1];
                        cout << "in if with : " << (int) testStr[0] + (int) testStr[1] << endl;

                        if ( sum3 > (int) testStr[0] + (int) testStr[1]+ (int) testStr[2])
                        {
                            sum3 = (int) testStr[0] + (int) testStr[1]+ (int) testStr[2];
                            
                            minString = testStr;

                            //cout << minString << endl;


                        }
                    }

                }

                }

                 
                cout << minString << endl;
                //int ValArray[j] = sum;
            }
    }

    return 0;
}
    
        
               /*     
        // make the suffix tree for circText
        std::string = "&&&";
        run(circText,nullstr); // should return false
        
        // call search with the lexically smallest string
        search(circText,testArray,edgeHash);
        
*/
    
    
	return testStr;
}
