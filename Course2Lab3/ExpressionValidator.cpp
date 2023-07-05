#include "ExpressionValidator.h"

bool ExpressionValidator::isValidExpression(const std::vector<std::string>& str, Table<std::string, size_t>& table)
{
	int bracketsCounter = 0;
	std::string prevEl = "";
	for (size_t i = 0; i < str.size(); i++) {
		if (str[i] == "(")
			bracketsCounter++;
		if (table.isKeyExist(prevEl) && table.isKeyExist(str[i]) && str[i] != "(" && table[str[i]] != table.maxValue())
			throw "Invalid action: There cannot be two or more lexemes standing next to each other";
		if (str[i] == ")")
			bracketsCounter--;
		if (bracketsCounter < 0)
			throw "Invalid amount of brackets in expression";
		if (prevEl == "/" && str[i] == "0")
			throw "Invalid action: Cannot divide by zero";
		if (prevEl == "(" && str[i] == ")")
			throw "Empty brackets";
		if (str[i] != "(" && table.isKeyExist(str[i])) {
			if (prevEl == "") {
				if (table[str[i]] == table.maxValue())
					prevEl = str[i];
				else
					throw "Lexemes cannot stay before operands";
			}
		}
		prevEl = str[i];
	}
	if (bracketsCounter != 0)
		throw "Invalid amount of brackets in expression";

	return true;
}
