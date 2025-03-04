#ifndef RULE_HPP
# define RULE_HPP


class Rule {

private:

	std::string	fullStr;
	std::string	leftStr;
	std::string	rightStr;
	bool		isBiconditional;
	int			evaluation;
	bool		disabled;

	void splitLeftRightStrs();

public:

	// * Constructeurs:
	Rule();
	Rule(const std::string& full);

	// * Méthodes publiques:
	void print(std::map<char, int> facts, int leftColWidth, int rightColWidth);
	void evaluate(std::map<char, int> facts);
	std::string getUndeterminedFactsOnRight(std::map<char, int> facts);
	void checkConflict(std::map<char, int> facts);

	// * Getters
	std::string	getFullStr() const;
	std::string	getLeftStr() const;
	std::string	getRightStr() const;
	bool		getIsBiconditional() const;
	int			getEvaluation() const;
	bool		getDisabled() const;

	// * Setters
	void setDisabled(bool disable);
};

#endif // * RULE_HPP

