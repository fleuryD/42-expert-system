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
 * @brief:	Get the Filename to open With Files Selector
 * 			If the file ID > 0, it returns the corresponding filename.
 * 			Otherwise, it displays the list of files in the folder ./maps
 * @return std::string
 */
std::string getFilenameWithFilesSelectorUI(int gFileId) {

	// * Récupération des fichiers du dossier ./maps
	std::string folderPath = "./maps";
	std::vector<std::string> fileList;

	for (const auto& entry : fs::directory_iterator(folderPath)) {
		if (entry.is_regular_file()) {
			fileList.push_back(entry.path().filename().string());
		}
	}

	if (fileList.empty()) {
		std::cout << C_RED << "No files found in the ./maps folder." << C_NOR << "\n";
		exit(1);
	}

	// Tri par ordre alphabétique
	std::sort(fileList.begin(), fileList.end());


	int fileCount = fileList.size();

	if (gFileId >= 1 && gFileId <= fileCount) {
		return fileList[gFileId - 1];
	}

	std::cout << "\n      " << C_CYA << fileCount << " file(s) found in the folder ./maps :" << C_NOR << "\n";

	for (int i = 0; i < fileCount ; ++i) {
		std::cout << "      | " << C_CYA << std::setw(3) << i + 1 << C_NOR <<" : " << fileList[i] << std::endl;

	}
	std::cout << std::endl;

	std::string mystr;
	int fileId = gFileId;
	while (fileId < 1 || fileId > fileCount) {
		std::cout << C_YEL << "      Enter the file ID to open (1-" << fileCount << ")   ?> " << C_NOR;
		getline(std::cin, mystr);
		std::stringstream(mystr) >> fileId;

		if (fileId < 1 || fileId > fileCount) {
			std::cout << C_RED << "      Incorrect value: The file ID must be between 1 and " << fileCount << C_NOR << "\n";
		}
	}

	return fileList[fileId - 1];

}

