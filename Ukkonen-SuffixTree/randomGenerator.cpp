//#include "randomGenerator.h"
// #ifndef RANDOMGENERATOR_H
// #define RANDOMGENERATOR_H
#include <iostream>
#include <string>
#include <algorithm>
#include <random>


std::string randTextGen(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 10);
    std::string text = "";
    static const char alphanum[] = "abcdefghijklmnopqrstuvwxyz";
    std::uniform_int_distribution<> cis(0,(sizeof(alphanum) - 1));
    for (int i = 0; i < 10; i++) {
        text = text+alphanum[cis(gen)];
    }
    return text;
}

std::string randPatternGen(std::string text){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 10);
    std::string pattern = "";
    int pos1,pos2;
    pos1 = dis(gen);
    pos2 = dis(gen);
     if (pos2 > pos1) {
         pattern += text.substr(pos1,pos2);
     }
     else {
         pattern += text.substr(pos2,pos1);
     }
    return pattern;
}



// #endif