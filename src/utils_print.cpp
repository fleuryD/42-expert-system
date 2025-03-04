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

void enableANSIColors() {
#ifdef _WIN32
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hOut == INVALID_HANDLE_VALUE) return;

	DWORD dwMode = 0;
	if (!GetConsoleMode(hOut, &dwMode)) return;

	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(hOut, dwMode);
#endif
}


void printCharMultipleTimes(char c, int count) {
	for (int i = 0; i < count; ++i) {
		std::cout << c;
	}
}

void printAppHeader() {
	std::cout << C_CYA;
	std::cout << "\n";
	std::cout << " ***************************************************************************************\n";
	std::cout << " *                                                                                     *\n";
	std::cout << " *            :::      ::::::::       EXPERT SYSTEM                                    *\n";
	std::cout << " *          :+:      :+:    :+:                                                        *\n";
	std::cout << " *        +:+ +:+         +:+         How to do simple logic. Or not-so-simple.        *\n";
	std::cout << " *      +#+  +:+       +#+                                                             *\n";
	std::cout << " *    +#+#+#+#+#+   +#+                                                                *\n";
	std::cout << " *         #+#    #+#                                                                  *\n";
	std::cout << " *        ###   ########.fr           By: dfleury <dfleury@student.42.fr>              *\n";
	std::cout << " *                                                                                     *\n";
	std::cout << " ***************************************************************************************\n";
	std::cout << " *   USAGE:                                                                            *\n";
	std::cout << " *      " << C_NOR << "./expert ./maps/...       " << C_CYA << " > Open a file                                       *\n";
	std::cout << " *      " << C_NOR << "./expert -f [id]          " << C_CYA << " > Open a file with the assistant                    *\n";
	std::cout << " *      " << C_NOR << "-i abcd                   " << C_CYA << " > Define the InitialFacts                           *\n";
	std::cout << " ***************************************************************************************\n";
	std::cout << C_NOR;
}

void printEvalColor(int val) {
	if (val == -1)
		std::cout << C_CYA;
	else if (val == 0)
		std::cout << C_RED;
	else if (val == 1)
		std::cout << C_GRE;
	else
		std::cout << C_NOR;
}
