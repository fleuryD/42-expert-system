#ifndef APP_HPP
#define APP_HPP

class App {

	private:
		std::map<char, int>	facts;
		std::vector<Rule>	rules;
		std::string			strInitialFacts;
		std::string			strQueries;
		unsigned long		leftColWidth;
		unsigned long		rightColWidth;

		// * Constructeur privé
		App();

		// * Méthodes privés:
		void	createMapFromFilename(std::string fileName);
		void	createFacts();
		void	decomposeBiDirectionalRules();
		void	initFactsWithInitialData();
		void	printFacts();
		void	printMapRules();
		int		applyRule(Rule &rule);
		std::map<char, int>	getModifiedFacts(Rule rule);
		void 	generateCombinationsRecursive(MapFactsType& facts, std::vector<MapFactsType>& combinations, std::string& unknownKeys, size_t index);
		std::vector<MapFactsType> generateGoodCombinations(Rule rule, std::string unknownKeys, const MapFactsType& facts);


	public:
		static App& getInstance();

		// * Méthodes publiques:
		void	initFromArgs(int argc, char **argv);
		int		applyAllRules();
		void	evaluateAllRules();
		void	evaluateAllEnabledRules();
		void	printState();
		void	printFinalResult();
		void	checkAllRulesConflicts();
		void	disableFalseOrUselessRules();

		// * Getters
		// const std::map<char, int>&	getFacts() const;
		// const std::vector<Rule>&	getRules() const;
		// const std::string& 			getStrInitialFacts() const;
		// const std::string& 			getStrQueries() const;
		// const unsigned long&		getLeftColWidth() const;
		// const unsigned long&		getRightColWidth() const;

		// * Setters
		// void setFacts(const std::map<char, int>& newFacts);
		// void setRules(const std::vector<Rule>& newRules);
		// void setStrInitialFacts(const std::string& newStrInitialFacts);
		// void setStrQueries(const std::string& newStrQueries);

		// * Supprime les constructeurs et opérateurs de copie pour éviter la duplication du singleton
		App(const App&) = delete;
		App& operator=(const App&) = delete;

};

#endif // APP_HPP
