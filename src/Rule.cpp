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

namespace {

	void printColoredStr(std::map<char, int> facts, std::string str) {
		for (unsigned long  j=0; j< str.size(); j++) {
			char c = str[j];
			std::cout << C_NOR;
			if (std::isalpha(c)) {
				printEvalColor(facts[c]);
			}
			std::cout << c ;
		}
	}

	void checkSyntax(std::string str, std::string _fullStr) {



		if(str.empty())
			throw std::runtime_error("Syntax Error in rule: \"" + _fullStr + "\"");

		if (str.find("!!") != std::string::npos) {
			// !!!!!!!!! ERREUR OU PAS ??????
			throw std::runtime_error("Syntax Error: Found \"!!\" in rule: \"" + _fullStr + "\"");
		}

		int levelParenthesis = 0;
		for (unsigned long i = 0; i < str.size(); i++) {
			if (!std::isalpha(str[i]) && !strContainsChar("+!|^()", str[i]))
				throw std::runtime_error("Syntax Error: Invalid character '" + std::string(1, str[i]) + "' in rule: \"" + _fullStr + "\"");



			if (std::isalpha(str[i])){
				// * Lettre suivie par autre chose que des lettres ou ")" ou operateur ou rien
				if (str[i+1] && !strContainsChar("+|^)", str[i+1]) )
					throw std::runtime_error("Syntax Error in rule: \"" + _fullStr + "\"");
			}
			else if (strContainsChar("+|^", str[i])){
				// * operateur "+|^" en debut de chaine
				if (i == 0)
					throw std::runtime_error("Syntax Error: Operator '" + std::string(1, str[i]) + "' at the beginning in rule: \"" + _fullStr + "\"");

				// * operateur "+|^" en fin de chaine
				if (i == str.size() - 1)
					throw std::runtime_error("Syntax Error: Operator '" + std::string(1, str[i]) + "' at the end in rule: \"" + _fullStr + "\"");

				// * operateur "+|^" suivi par autre chose que des lettres ou '(' ou '!'
				if (!std::isalpha(str[i+1]) && !strContainsChar("(!)", str[i+1]))
					throw std::runtime_error("Syntax Error in rule: \"" + _fullStr + "\"");
			}
			else if (str[i] =='('){
				levelParenthesis++;
				if (str[i+1] == ')')
					throw std::runtime_error("Syntax Error: Empty parentheses in rule: \"" + _fullStr + "\"");
			}
			else if (str[i] ==')'){
				levelParenthesis--;
				if(levelParenthesis < 0)
					throw std::runtime_error("Syntax Error: Unopened parenthesis in rule: \"" + _fullStr + "\"");
			}
		}

		if(levelParenthesis > 0)
			throw std::runtime_error("Syntax Error: Unclosed parenthesis in rule: \"" + _fullStr + "\"");
	}

}


/**
 * @access:	PUBLIC
 * @brief:	Default constructor
 */
Rule::Rule(): fullStr(""), leftStr(""), rightStr(""), isBiconditional(false), evaluation(-2), disabled(false) {}

/**
 * @access:	PUBLIC
 * @brief:	Constructor
 */
Rule::Rule(const std::string& full)
	: fullStr(full), leftStr(""), rightStr(""), isBiconditional(false), evaluation(-2), disabled(false) {

	if (strContainsLowercase(fullStr)){
		std::cout << C_RED << "   /!\\ Lowercase letters will be converted /!\\ ";
		fullStr = strToUpper(fullStr);
	}
	splitLeftRightStrs();
	rightStr = removeAllWhitespaces(rightStr);
	leftStr = removeAllWhitespaces(leftStr);
	checkSyntax(rightStr, fullStr);
	checkSyntax(leftStr, fullStr);

}


/**
 * @access:	PRIVATE
 * @brief:	Set and trim leftStr and rightStr from fullStr and set isBiconditional
 */
void Rule::splitLeftRightStrs() {
	std::size_t pos;

	if ((pos = fullStr.find("<=>")) != std::string::npos) {
		isBiconditional = true;
		leftStr = fullStr.substr(0, pos);
		rightStr = fullStr.substr(pos + 3); // 3 pour "<=>"
	}
	else if ((pos = fullStr.find("=>")) != std::string::npos) {
		isBiconditional = false;
		leftStr = fullStr.substr(0, pos);
		rightStr = fullStr.substr(pos + 2); // 2 pour "=>"
	}
	else {
		throw std::runtime_error("Syntax Error in rule: \"" + fullStr + "\"");
	}

	trim(leftStr);
	trim(rightStr);
}

/**
 * @access:	PUBLIC
 * @brief:	set evaluation to 1 if true, 0 if false, -1 if undetermined
 */
void Rule::evaluate(std::map<char, int> facts) {
	evaluation = evaluateString(leftStr, facts);
}

/**
 * @access:	PUBLIC
 * @brief:	Display a rule with the correct format, alignment, and colors.
 */
void Rule::print(std::map<char, int> facts, int leftColWidth, int rightColWidth) {
	std::cout << C_NOR;
	printCharMultipleTimes(' ', leftColWidth - leftStr.size());
	printColoredStr(facts, leftStr);

	printEvalColor(evaluation);
	if (isBiconditional)
		std::cout << " <=>  ";
	else
		std::cout << "  =>  ";

	printColoredStr(facts, rightStr);
	printCharMultipleTimes(' ', rightColWidth - rightStr.size());

}

/**
 * @access:	PUBLIC
 * @brief:	Return undetermined facts present on the right side of the rule.
 * @return:	String (examples: "ABU" or "")
 */
std::string Rule::getUndeterminedFactsOnRight(std::map<char, int> facts){
	std::string undeterminedFacts = "";
	for (unsigned long i=0; i< rightStr.size(); i++) {
		if (std::isalpha(rightStr[i])
		&& facts[rightStr[i]] == -1
		&& undeterminedFacts.find(rightStr[i]) == std::string::npos){
			undeterminedFacts += rightStr[i];
		}
	}
	return undeterminedFacts;
}

/**
 * @access:	PUBLIC
 * @brief:	Throw an exception if there is a contradiction in the rule
 * @note:	(ie. evaluation is 1 but the right side of the rule is false)
 */
void Rule::checkConflict(std::map<char, int> facts) {
	if (evaluation != 1)
		return;
	int evalRight = evaluateString(rightStr, facts);
	if (evalRight == 0)
		throw std::runtime_error("Contradiction in rule: " + std::string(C_NOR) + fullStr);
}


// * Getters
std::string Rule::getFullStr() const { return fullStr; }
std::string Rule::getLeftStr() const { return leftStr; }
std::string Rule::getRightStr() const { return rightStr; }
bool Rule::getIsBiconditional() const { return isBiconditional; }
int Rule::getEvaluation() const { return evaluation; }
bool Rule::getDisabled() const { return disabled; }

// * Setters
void Rule::setDisabled(bool disable) { disabled = disable; }


