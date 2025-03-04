#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <fstream> // * pour lire un fichier
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <filesystem>
#include <cctype>
#include <regex>
#include <utility> // * pour std::pair dans splitAtFirstHash
#include <optional> // * Pour std::optional
// #include <stdlib.h>
#include <random>
#include <chrono> // Pour std::chrono
#include <thread> // pour this_thread::sleep_for(std::chrono::milliseconds(500));

#include <ranges>    // pour std::ranges::transform
#include <cctype>    // pour std::strToUpper

#include <stdexcept> // Pour std::runtime_error

// using namespace std;	// * NON : crée des conflits avec std::byte
namespace fs = std::filesystem;

#ifdef _WIN32
# include <windows.h>
#endif




#define C_NOR "\x1b[m"
#define C_GRA "\x1b[30m"
#define C_RED "\x1b[31m"
#define C_GRE "\x1b[32m"
#define C_YEL "\x1b[33m"
#define C_BLU "\x1b[34m"
#define C_MAG "\x1b[35m"
#define C_CYA "\x1b[36m"
#define C_WHI "\x1b[37m"

#define B_GRA "\x1b[40m"
#define B_RED "\x1b[41m"
#define B_GRE "\x1b[42m"
#define B_YEL "\x1b[43m"
#define B_BLU "\x1b[44m"
#define B_MAG "\x1b[45m"
#define B_CYA "\x1b[46m"
#define B_WHI "\x1b[47m"

#define S_BOLD "\x1b[1m"
#define S_UNDER "\x1b[4m"
#define S_REV "\x1b[7m"


using MapFactsType = std::map<char, int>;


#include "Rule.hpp"
#include "App.hpp"

#define STL_STEP "\n \x1b[47m\x1b[30m  "


// *******************			utils_files.cpp			*******************

std::string getFilenameWithFilesSelectorUI(int gFileId);

// *******************			utils_string.cpp			*******************

std::pair<std::string, std::string> splitAtFirstHash(const std::string& str);
std::vector<std::string> splitWords(const std::string& str);
std::string trim(const std::string& str);
std::string removeAllWhitespaces(std::string str);
std::string strToUpper(const std::string& str);
bool stringIsPositiveDigit(const std::string& str);
bool strContainsLowercase(const std::string& str);
bool strContainsChar(const std::string& str, const char c);
bool strContainsAnyChar(const std::string& str1, const std::string& str2);

// *******************			utils_print.cpp			*******************


void enableANSIColors();
void printCharMultipleTimes(char c, int count);
void printAppHeader();
void printEvalColor(int val);


// *******************			utils_tokens.cpp			*******************

int evaluateString(std::string str, std::map<char, int> facts);


// *******************			xxxxxxxxxxx.cpp			*******************