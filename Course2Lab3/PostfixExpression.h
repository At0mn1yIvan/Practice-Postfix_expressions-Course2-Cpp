#pragma once

#include <string>
#include <vector>
#include <cmath>
#include "TStack.h"
#include "Table.h"
#include "ExpressionValidator.h"




class PostfixExpression
{
private:
	std::vector<std::string> _infix;
	std::vector<std::string> _postfix;
	Table<std::string, size_t> _priority;
	Table<std::string, double> _variables;
	TStack<std::string> _operandsStack;
	TStack<double> _valueStack;
	ExpressionValidator _exprCheck;



public:
	PostfixExpression(const Table<std::string, size_t>& priority, const Table<std::string, double>& variables = Table<std::string, double>(0));
	
	std::vector<std::string> GetInfix() const;
	std::vector<std::string>  GetPostFix() const;

	void initialize(const std::string& strInit);
	void ToPostfix(const std::string& expr);
	double Calculate(const std::string& expr);
	std::vector<double> solveFunc(const std::string& func, std::vector<double>& arr);
};
