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

int main(int argc, char **argv) {

	try {
		printAppHeader();
		App& app = App::getInstance();
		app.initFromArgs(argc, argv);
		app.evaluateAllEnabledRules();

		while (true){
			int changeCount = app.applyAllRules();
			app.evaluateAllEnabledRules();
			app.checkAllRulesConflicts();
			app.disableFalseOrUselessRules();
			if (changeCount == 0){
				break;
			}
		}

		std::cout << STL_STEP << "END OF ALGORITHM   "<<C_NOR << "\n";
		app.evaluateAllRules();
		app.printState();
		app.checkAllRulesConflicts();

		std::cout << STL_STEP << "RESULTS   " <<C_NOR << "\n\n";

		app.printFinalResult();


	} catch (const std::exception& e) {
		std::cout << S_BOLD << C_RED << "\n\n   ERROR :\n" << C_NOR << C_RED << "   " <<  e.what() << C_NOR << "\n\n";
		return 1;
	}
	return 0;




}
