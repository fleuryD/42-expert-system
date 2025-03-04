// ***************************************************************************************
// *                                                                                     *
// *            :::      ::::::::       EXPERT SYSTEM                                    *
// *          :+:      :+:    :+:                                                        *
// *        +:+ +:+         +:+         How to do simple logic. Or not-so-simple.        *
// *      +#+  +:+       +#+                                                             *
// *    +#+#+#+#+#+   +#+                                                                *
// *         #+#    #+#                                                                  *
// *        ###   ########.fr           By: dfleury <dfleury@student.42.fr>              *
// *                                                                                     *
// ***************************************************************************************

#include "../include/expert.hpp"


/**
 * @brief:	Diviser une chaîne en deux parties à la première occurrence du caractère "#"
 * @param str: La chaîne à diviser.
 * @return: Un paires contenant la partie avant et après le caractère "#".
 */
std::pair<std::string, std::string> splitAtFirstHash(const std::string& str) {
	size_t pos = str.find('#'); // Trouver le premier "#"
	// Si aucun "#", retourner toute la chaîne dans la première partie
	if (pos == std::string::npos) {
		return {str, ""};
	}
	// Diviser en deux parties : avant et après le "#"
	std::string before = str.substr(0, pos);
	std::string after = str.substr(pos + 1);
	return {before, after};
}

/**
 * @brief:	Diviser une chaîne en mots séparés par des espaces ou des tabulations
 */
std::vector<std::string> splitWords(const std::string& str) {
	const std::string& delimiters =  "[ \\t]+";
	std::vector<std::string> tokens;
	std::regex re(delimiters); // Regex pour les délimiteurs
	std::sregex_token_iterator it(str.begin(), str.end(), re, -1);
	std::sregex_token_iterator end;

	while (it != end) {
		if (!it->str().empty()) { // Ignorer les sous-chaînes vides
			tokens.push_back(*it);
		}
		++it;
	}

	return tokens;
}

/**
 * @brief:	Supprimer les white-spaces de début et de fin d'une chaîne
 */
std::string trim(const std::string& str) {
	// Trouver le premier caractère non-whitespace
	auto start = std::find_if_not(str.begin(), str.end(), [](unsigned char c) { return std::isspace(c); });
	// Trouver le dernier caractère non-whitespace
	auto end = std::find_if_not(str.rbegin(), str.rend(), [](unsigned char c) { return std::isspace(c); }).base();
	// Retourner la sous-chaîne sans whitespaces
	return (start < end) ? std::string(start, end) : std::string();
}

/**
 * @brief:	Supprimer tous les White Spaces d'une chaîne
 */
std::string removeAllWhitespaces(std::string str) {
	str.erase(std::remove_if(str.begin(), str.end(), [](char c) { return std::isspace(c); }), str.end());
	return str;
}


/**
 * @brief:	Convert a string to uppercase.
 * @param:	str The string to convert.
 * @return:	The uppercase string.
 */
std::string strToUpper(const std::string& str) {
	std::string result = str;  // Crée une copie de la chaîne d'origine

	std::ranges::transform(result, result.begin(), [](unsigned char c) {
		return std::toupper(c);
	});

	return result;
}

/**
 * @brief:	Checks if a string contains at least one lowercase character.
 * @return:	true if the string contains at least one lowercase character, false otherwise.
 */
bool strContainsLowercase(const std::string& str) {
	for (char c : str) {
		if (std::islower(c)) {
			return true;
		}
	}
	return false;
}

/**
 * @brief:	Checks if a string contains a specific character.
 * @param:	str		The string to search in.
 * @param:	c		The character to search for.
 * @return:	true if the character is found in the string, false otherwise.
 */
bool strContainsChar(const std::string& str, const char c) {
	for (char ch : str) {
		if (ch == c) {
			return true;
		}
	}
	return false;
}

/**
 * @brief:	Checks if any character from str2 exists in str1.
 * @return:	true if any character from str2 is found in str1, false otherwise.
 */
bool strContainsAnyChar(const std::string& str1, const std::string& str2) {
	for (char c : str2) {
		if (str1.find(c) != std::string::npos) {
			return true;
		}
	}
	return false;
}

/**
 * @brief:	Check if a string contains only digits.
 * @return:	true if the string contains only digits, false otherwise.
 */
bool stringIsPositiveDigit(const std::string& str) {
	for (char c : str) {
		if (!std::isdigit(c)) {
			return false;
		}
	}
	return true;
}