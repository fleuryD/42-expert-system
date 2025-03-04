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


App& App::getInstance() {
	static App instance;
	return instance;
}

App::App() {}



// * Méthodes PRINT

void App::printFacts() {

	// * Afficher les facts
	std::cout << C_NOR << "   "<< B_WHI << "*" << C_NOR << "  Facts:   ";
	for (auto const& [key, val] : facts) {
		printEvalColor(val);
		std::cout << key << " ";
	}
	std::cout << C_NOR << "\n   "<< B_WHI << "*" << C_NOR << "  Queries: ";
	for (auto const& [key, val] : facts) {
		printEvalColor(val);
		if (strQueries.find(key) != std::string::npos)
			std::cout << key << " ";
		else
			std::cout << "  ";
	}
	std::cout << "\n";
}

void App::printMapRules() {
	std::cout << C_NOR << "   "<< B_WHI << "*" << C_NOR << "  \n";
	std::cout << C_NOR << "   "<< B_WHI << "*" << C_NOR << "  Rules:\n";

	// * Regles TRUE:
	for (unsigned long  i=0; i< rules.size(); i++) {
			if (rules[i].getDisabled() && (rules[i].getEvaluation() == 1) ){
			std::cout << C_NOR << "   "<< B_WHI << "*" << C_NOR;
			rules[i].print(facts, leftColWidth+4, 0);
			std::cout << C_NOR << "\n";
		}
	}
	// * Regles FALSE:
	for (unsigned long  i=0; i< rules.size(); i++) {
			if (rules[i].getDisabled() &&  (rules[i].getEvaluation() == 0) ){
			std::cout << C_NOR << "   "<< B_WHI << "*" << C_NOR;
			rules[i].print(facts, leftColWidth+4, 0);
			std::cout << C_NOR << "\n";
		}
	}
	// * Regles eval -1 mais disabled:
	for (unsigned long  i=0; i< rules.size(); i++) {
		if (rules[i].getDisabled() && (rules[i].getEvaluation() == -1)){
			std::cout << C_NOR << "   "<< B_WHI << "*" << C_NOR;
			rules[i].print(facts, leftColWidth+4, 0);
			std::cout << C_NOR << "\n";
		}
	}

	// * Regles restantes:
	std::cout << C_NOR << "   "<< B_WHI << "*" << C_NOR << "  Remaining rules:\n";
	for (unsigned long  i=0; i< rules.size(); i++) {
		if (!rules[i].getDisabled() ){
			std::cout << C_NOR << "   "<< B_WHI << "*" << C_NOR;
			rules[i].print(facts, leftColWidth+4, 0);
			std::cout << C_NOR << "\n";
		}
	}
}

// PUBLIC
void App::printState() {

	std::cout << "\n\n" << C_NOR ;
	printFacts();
	printMapRules();
	std::cout << "\n\n" << C_NOR ;
}

// PUBLIC
void App::printFinalResult() {
	for (unsigned long i=0; i< strQueries.size(); i++) {
		char c = strQueries[i];
		std::cout << "   " << c << " is ";
		printEvalColor(facts.at(c));
		if (facts.at(c) < 0)
			std::cout << "UNDETERMINED" << C_NOR;
		else if (facts.at(c) == 0)
			std::cout << "FALSE" << C_NOR;
		else if (facts.at(c) == 1)
			std::cout << "TRUE" << C_NOR;
		std::cout << "\n";
	}
	std::cout << "\n";
}


// * Méthodes READ FILE + INIT APP

void App::createMapFromFilename(std::string fileName) {

	const std::string prefix = "./maps/";
	if (fileName.find(prefix) == 0) { // * `find` retourne 0 si le préfixe est au début
		fileName.erase(0, prefix.length()); // * Supprime les premiers caractères correspondant à `prefix`
	}
	const std::string prefixWindows = ".\\maps\\";
	if (fileName.find(prefixWindows) == 0) { // * `find` retourne 0 si le préfixe est au début
		fileName.erase(0, prefixWindows.length()); // * Supprime les premiers caractères correspondant à `prefix`
	}
	std::cout << C_CYA << " *   OPENING FILE  " << C_NOR << "\"./maps/"  << fileName << "\"\n" << C_NOR;
	std::ifstream file("./maps/" + fileName);
	if (!file.is_open())
		throw std::runtime_error("Unable to open the file.");

	std::string line;

	bool overideStrInitialFacts = (strInitialFacts != "");
	strQueries = "";


	std::cout << C_CYA << " *\n" << C_NOR;

	while (std::getline(file, line)) {
		if (file.fail())
			throw std::runtime_error("Reading error.");


		if (!line.empty()) {

			auto result = splitAtFirstHash(line);

			std::string trimedFirst = trim(result.first);


			if (!trimedFirst.empty()){

				if (trimedFirst.contains("=>")){
					std::cout << C_CYA << " *\t" << C_NOR << trimedFirst ;
					Rule rule = Rule(trimedFirst);
					rules.push_back(rule);
				}
				else if(trimedFirst[0]== '='){
					std::cout << C_CYA << " *\tInitial facts: " << C_GRE << trimedFirst ;
					if (!overideStrInitialFacts){
						if (strInitialFacts != "")
							throw std::runtime_error("Multiple line with Initial facts !");
						strInitialFacts = strToUpper(trimedFirst.substr(1));
					}
					else{
						std::cout << C_CYA << " *\t overaded by: " << C_GRE << strInitialFacts ;
					}
				}
				else if(trimedFirst[0]== '?'){
					std::cout << C_CYA << " *\tQueries: " << C_NOR << trimedFirst ;
					if (strQueries != "")
						throw std::runtime_error("Multiple line with Queries !");
					strQueries = strToUpper(trimedFirst.substr(1));
				}

			}
			if (!result.second.empty()){
				std::cout << C_BLU << "   #" << result.second << C_NOR;
			}


			std::cout  << std::endl;

		}

	}

	std::cout << C_CYA << " ***************************************************************************************\n" << C_NOR;


}

void App::createFacts() {
	facts.clear();

	// * FILL facts from Rules
	for (unsigned long  i=0; i< rules.size(); i++) {
		for (unsigned long  j=0; j< rules[i].getFullStr().size(); j++) {
			char c = rules[i].getFullStr()[j];
			if (std::isalpha(c)) {
				facts[c] = -1;
			}
		}
	}
	// * Add facts from InitialFacts
	for (unsigned long  i=0; i< strInitialFacts.size(); i++) {
		char c = strInitialFacts[i];
		if (!std::isalpha(c))
			throw std::runtime_error("Invalid character in InitialFacts: '" + std::string(1, c) + "'");
		facts[c] = -1;
	}
	// * Add facts from Queries
	for (unsigned long  i=0; i< strQueries.size(); i++) {
		char c = strQueries[i];
		if (!std::isalpha(c))
			throw std::runtime_error("Invalid character in Queries: '" + std::string(1, c) + "'");
		facts[c] = -1;
	}
}

void App::decomposeBiDirectionalRules() {

	bool hasBiconditionalRules = false;
	for (unsigned long  i=0; i< rules.size(); i++) {
		if (rules[i].getIsBiconditional()){
			hasBiconditionalRules = true;
			break;
		}
	}
	if (!hasBiconditionalRules)
		return;


	for (unsigned long  i=0; i< rules.size(); i++) {
		if (rules[i].getIsBiconditional()) {

			std::string left = rules[i].getLeftStr();
			std::string right = rules[i].getRightStr();
			std::cout << C_CYA << "\n   We decompose the bi-directional rule   "<<C_NOR << left <<  " <=> " << right << "\n";
			std::string fullStr;

			fullStr= left + " => " + right;
			std::cout << C_NOR << "      " << fullStr << "\n";
			rules.push_back(Rule(fullStr));

			fullStr= right + " => " + left;
			std::cout << C_NOR << "      " << fullStr << "\n";
			rules.push_back(Rule(fullStr));

			std::string notRight = "!(" + right + ")";
			if (right.size() == 1)
				notRight = "!" + right;
			if (right.size() == 2 && right[0] == '!') // *  !A
				notRight = right[1];


			std::string notLeft = "!(" + left + ")";
			if (left.size() == 1)
				notLeft = "!" + left;
			if (left.size() == 2 && left[0] == '!') // *  !A
				notLeft = left[1];


			fullStr= notRight + " => " + notLeft;
			std::cout << C_NOR << "      " << fullStr << "\n";
			rules.push_back(Rule(fullStr));

			fullStr= notLeft + " => " + notRight;
			std::cout << C_NOR << "      " << fullStr << "\n";
			rules.push_back(Rule(fullStr));

			rules[i].setDisabled(true);
			std::cout << C_NOR "\n";
		}
	}

}

void App::initFactsWithInitialData() {
	// * Facts présents dans initial facts:
	for (unsigned long  i=0; i< strInitialFacts.size(); i++) {
		std::cout << C_NOR << "   " << strInitialFacts[i] << " is in initial facts, so " << C_GRE << strInitialFacts[i] << " is TRUE  " << C_NOR << "\n";
		facts[strInitialFacts[i]] = 1;
	}

	// * Facts non presents a droite:
	for (auto const& [key, val] : facts) {
		bool found = false;
		if (val == 1)	// * deja true
			continue;
		for (unsigned long  r=0; r< rules.size(); r++) {
			if (rules[r].getRightStr().contains(key)) {
				found=true;
				break;
			}
		}
		if (!found){
			std::cout << C_NOR <<  "   " << key << " never appears on the right side, so " << C_RED << key << " is FALSE  " << C_NOR << "\n";
			facts[key] = 0;
		}
	}

	std::cout << "\n";
}

// PUBLIC
void App::initFromArgs(int argc, char **argv) {
	std::string filename = "";

	if (argc == 1)
		throw std::runtime_error("No argument.\nPlease enter -f or a file name.");

	if (std::string(argv[1]) == "-f") {
		int fileId = 0;
		if (argc > 2 && stringIsPositiveDigit( argv[2])) {
			fileId = std::stoi( argv[2]);
		}
		filename =getFilenameWithFilesSelectorUI(fileId);
	}
	else{
		filename = argv[1];
	}

	strInitialFacts = "";
	for (int i = 2; i < argc; i++) {
		if (std::string(argv[i]) == "-i") {
			if (i+1 < argc){
				strInitialFacts = strToUpper(argv[i+1]);
			}
		}
	}

	createMapFromFilename(filename);
	createFacts();
	decomposeBiDirectionalRules();

	std::cout << "   Legend: " << C_GRE << "Green = TRUE" << C_NOR << ", " << C_RED << "Red = FALSE" << C_NOR << ", " << C_CYA << "Cyan = UNDETERMINATED" << "\n\n";


	initFactsWithInitialData();

	leftColWidth = 0;
	rightColWidth = 0;
	for (unsigned long  i=0; i< rules.size(); i++) {
		if (rules[i].getLeftStr().size() > leftColWidth)
			leftColWidth = rules[i].getLeftStr().size();
		if (rules[i].getRightStr().size() > rightColWidth)
			rightColWidth = rules[i].getRightStr().size();
	}

}


// * Méthodes LOGIC


// Fonction récursive pour générer les combinaisons
void App::generateCombinationsRecursive(MapFactsType& facts, std::vector<MapFactsType>& combinations, std::string& unknownKeys, size_t index){
	if (index == unknownKeys.size()) {
		combinations.push_back(facts);
		return;
	}

	char key = unknownKeys[index];

	facts[key] = 0;
	generateCombinationsRecursive(facts, combinations, unknownKeys, index + 1);

	facts[key] = 1;
	generateCombinationsRecursive(facts, combinations, unknownKeys, index + 1);
}

// Generer toutes les combinaisons possibles
std::vector<MapFactsType> App::generateGoodCombinations(Rule rule, std::string unknownKeys, const MapFactsType& facts) {
	std::vector<MapFactsType> combinations;
	std::vector<MapFactsType> goodCombinations;
	MapFactsType modifiedFacts = facts;

	generateCombinationsRecursive(modifiedFacts, combinations, unknownKeys, 0);

	for (unsigned long i=0; i< combinations.size(); i++) {
		if (evaluateString(rule.getRightStr(), combinations[i]) != 0){
			goodCombinations.push_back(combinations[i]);
		}
	}



	return goodCombinations;
}

std::map<char, int>	App::getModifiedFacts(Rule rule) {
	std::map<char, int> modifiedFacts;

	std::string strUndeterminedFacts = rule.getUndeterminedFactsOnRight(facts);
	if (strUndeterminedFacts.size() == 0)
		return modifiedFacts;


	if (rule.getRightStr().size() == 1){
		modifiedFacts[rule.getRightStr()[0]] = 1;
	}
	else if (rule.getRightStr().size() == 2){
		if ((rule.getRightStr()[0] != '!') | !std::isalpha(rule.getRightStr()[1]))
			throw std::runtime_error("#code E1266 : INVALID RULE: \t\"" + rule.getFullStr() + "\"");	// ! PROD: delete ErreurCode
		modifiedFacts[rule.getRightStr()[1]] = 0;
	}
	else if (!strContainsAnyChar(rule.getRightStr(), "!|^")){
		for (unsigned long i=0; i< strUndeterminedFacts.size(); i++) {
			modifiedFacts[strUndeterminedFacts[i]] = 1;
		}
	}
	else{
		std::vector<MapFactsType> combinations = generateGoodCombinations(rule, strUndeterminedFacts, facts);

		if (combinations.size() == 0){
			throw std::runtime_error("(CODE XXXXXXXXXXXDDDDDDDDDD444444444444444444444) : NO POSSIBLE COMBINATION");	// ! PROD: delete ErreurCode
		}

		std::vector<std::map<char, std::string>> possibleCharsValues;
		for (unsigned long i=0; i< strUndeterminedFacts.size(); i++) {
			int newValue = combinations[0][strUndeterminedFacts[i]];

			for (unsigned long c=0; c< combinations.size(); c++) {
				if (combinations[c][strUndeterminedFacts[i]] != newValue){
					newValue = -1;
					break;
				}
			}

			if (newValue != -1){
				modifiedFacts[strUndeterminedFacts[i]] = newValue;
			}
		}


	}

	return modifiedFacts;
}


int App::applyRule(Rule &rule) {

	if (rule.getEvaluation() != 1)
		return 0;




	std::map<char, int>	modifiedFacts = getModifiedFacts(rule);

	if (modifiedFacts.size() == 0)
		return 0;


	std::cout << C_NOR << "   Since we know that ";
	rule.print(facts, leftColWidth, rightColWidth);
	std::cout << C_NOR << "  then  ";

	for (auto const& [key, val] : modifiedFacts) {
		if (val == -1){
			// NE DEVRAIT PAS ARRIVER
			continue;
		}
		if (val == 1){
			std::cout << C_GRE << key << " is TRUE    ";
			if (facts[key] == 0){
				throw std::runtime_error("CONTRADICTION IN THE RULES: " + std::string(1, key) + " is FALSE");
			}
		}
		else if (val == 0){
			std::cout << C_RED << key << " is FALSE    ";
			if (facts[key] == 1){
				throw std::runtime_error("CONTRADICTION IN THE RULES: " + std::string(1, key) + " is TRUE");
			}
		}

		facts[key] = val;
	}
	std::cout << C_NOR << "\n" ;



	return 1;
}

// PUBLIC
void App::evaluateAllEnabledRules() {
	for (unsigned long  i=0; i< rules.size(); i++) {
		if (rules[i].getEvaluation() < 0){
			rules[i].evaluate(facts);
		}
	}
}
// PUBLIC
void App::evaluateAllRules() {
	for (unsigned long  i=0; i< rules.size(); i++) {
		rules[i].evaluate(facts);
	}
}

// PUBLIC
void App::disableFalseOrUselessRules() {

	bool hasFalseRules = false;
	for (unsigned long  i=0; i< rules.size(); i++) {
		if (!rules[i].getDisabled()){
			if (rules[i].getEvaluation() == 0){
				hasFalseRules = true;
				break;
			}
		}
	}
	if (hasFalseRules){
		for (unsigned long  i=0; i< rules.size(); i++) {
			if (!rules[i].getDisabled() && (rules[i].getEvaluation() == 0)){
				rules[i].setDisabled(true);
			}
		}
	}

	bool hasUselessRules = false;
	for (unsigned long  i=0; i< rules.size(); i++) {
		if (!rules[i].getDisabled()){
			if (rules[i].getUndeterminedFactsOnRight(facts).empty()){
				hasUselessRules = true;
				break;
			}
		}
	}
	if (hasUselessRules){
		for (unsigned long  i=0; i< rules.size(); i++) {
			if (!rules[i].getDisabled() && rules[i].getUndeterminedFactsOnRight(facts).empty()){
				rules[i].setDisabled(true);
			}
		}
	}

}

// PUBLIC
void App::checkAllRulesConflicts() {
	for (unsigned long  i=0; i< rules.size(); i++) {
		rules[i].evaluate(facts); // ! ?????????????
		rules[i].checkConflict(facts);
	}
}

// PUBLIC
int App::applyAllRules() {
	int changeCount = 0;
	for (unsigned long  i=0; i< rules.size(); i++) {
		if (!rules[i].getDisabled()){
			changeCount += applyRule(rules[i]);
		}
	}
	return changeCount;
}


// * GETTERS
// const std::map<char, int>& App::getFacts() const {		return facts;}
// const std::vector<Rule>& App::getRules() const {		return rules;}
// const std::string& App::getStrInitialFacts() const {	return strInitialFacts;}
// const std::string& App::getStrQueries() const {			return strQueries;}
// const unsigned long& App::getLeftColWidth() const {		return leftColWidth;}
// const unsigned long& App::getRightColWidth() const {	return rightColWidth;}

// * SETTERS
// void App::setFacts(const std::map<char, int>& newFacts) {				facts = newFacts;}
// void App::setRules(const std::vector<Rule>& newRules) {					rules = newRules;}
// void App::setStrInitialFacts(const std::string& newStrInitialFacts) {	strInitialFacts = newStrInitialFacts;}
// void App::setStrQueries(const std::string& newStrQueries) {				strQueries = newStrQueries;}
