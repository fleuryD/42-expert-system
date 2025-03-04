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

/**
 * evalNot, evalAnd, evalOr, evalXOr :
 * @brief:	Evaluate the logical operators
 * @notes:	A and B can be either 0, 1 or -1 (true, false or undetermined)
 *
 */

	int evalNot(int A){
		if ((A < 0))
			return -1;
		if (A == 1)
			return 0;
		return 1;
	}

	int evalAnd(int A, int B){
		if ((A < 0) | (B < 0))
			return -1;
		if ((A == 1) && (B == 1))
			return 1;
		return 0;
	}

	int evalOr(int A, int B){
		if ((A == 1) || (B == 1))
			return 1;
		if ((A == 0) && (B == 0))
			return 0;
		return -1;
	}

	int evalXOr(int A, int B){
		if ((A < 0) || (B < 0))
			return -1;
		if ((A == 1) && (B == 0))
			return 1;
		if ((A == 0) && (B == 1))
			return 1;
		return 0;

	}


	std::string removeUnecessaryParentheses(std::string str){

		if (!str[0] || (str[0] != '('))
			return str;

		unsigned long i = 1; // * !! Apres la 1ere parentheses ouvrante
		int level = 1;
		while(str[i]){
			if (str[i] == '('){
				level++;
			}
			else if (str[i] == ')'){
				level--;
				if (level == 0){
					if (i==str.size() - 1)
						return removeUnecessaryParentheses(str.substr(1, str.size()-2));
					else
						return str;
				}
			}
			i++;
		}
		if (level != 0)
			throw std::runtime_error("CODE W45654: Invalid Parentheses in: " + str);	// ! PROD: delete ErreurCode

		return str;
	}

	std::vector<std::string> createTokensFromStr(std::string str){
		std::vector<std::string> tokens;
		str = removeUnecessaryParentheses(str);

		int i=0;
		while(str[i]){
			std::string token;
			if (std::isalpha(str[i]) || (std::string("+|^!").find(str[i]) != std::string::npos)){
				token += str[i];
				tokens.push_back(token);
				i++;
			}
			else if (str[i] == '('){
				int level = 1;
				int j = i+1;
				while(str[j]){
					if (str[j] == '('){
						level++;
					}
					else if (str[j] == ')'){
						level--;
						if (level == 0){
							token = str.substr(i+1, j-i-1);
							token = removeUnecessaryParentheses(token);
							tokens.push_back(token);
							i = j+1;
							break;
						}
					}
					j++;
				}
				if (level != 0)
					throw std::runtime_error("Invalid Parentheses");
			}
			else
				throw std::runtime_error("Invalid Token: " + str);
		}
		return tokens;
	}


	int evaluateTokens(std::vector<std::string> tokens, std::map<char, int> facts) {

		if (tokens.size() == 0){
			throw std::runtime_error("Token Error");
		}

		char ch0 = tokens[0][0];

		if (tokens.size() == 1){
			if (!std::isalpha(ch0))
				throw std::runtime_error("Invalid Rule: \t\"" + tokens[0] + "\"");
			return facts[ch0];
		}

		int eval = -42;

		unsigned long  t = 0;


		while (t<tokens.size()){

			char currentChar = tokens[t][0];

			if (tokens[t].length() > 1){
				eval = evaluateString(tokens[t], facts);
			}
			else if (currentChar == '!'){
				eval = evalNot(evaluateString(tokens[t+1], facts));
				t ++;
			}
			else if (std::isalpha(currentChar)){
				eval = facts[currentChar];
			}
			else if (std::string("+|^").find(currentChar) != std::string::npos){

				int nextTokenEval;
				if (tokens[t+1][0] == '!'){
					if (tokens[t+1].length() > 1)
						nextTokenEval = evalNot(evaluateString(tokens[t+1].substr(1,tokens[t+1].size()-1 ), facts));
					else
						nextTokenEval = evalNot(evaluateString(tokens[t+2], facts));
					t++;
				}
				else{
					nextTokenEval = evaluateString(tokens[t+1], facts);
				}

				if (currentChar == '+'){
					eval = evalAnd(eval, nextTokenEval);
				}
				else if (currentChar == '|'){
					eval = evalOr(eval, nextTokenEval);
				}
				else if (currentChar == '^'){
					eval = evalXOr(eval, nextTokenEval);
				}

				t++;
			}
			else
				throw std::runtime_error("Invalid Rule: \t\"" + tokens[0] + "\"");

			t++;
		}
		return eval;
	}

}


int evaluateString(std::string str, std::map<char, int> facts) {
	str = removeUnecessaryParentheses(str);
	return evaluateTokens(createTokensFromStr(str), facts);
}