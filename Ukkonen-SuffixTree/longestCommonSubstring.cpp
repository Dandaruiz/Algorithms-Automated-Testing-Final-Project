// longest substring of two strings

#include "suffixTree.h"
#include <iostream>
#include <unordered_map> // Required c++11 support.
#include <string>
#include <cassert>
#include <ctime>
#include <chrono>
#include <random>
#include <string>




int main() {
	std::string text = randTextGen();
    text = text+"$"+text+"#";
    //run(text,pattern);
	return 0;
}