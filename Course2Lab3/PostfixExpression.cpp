#include "PostfixExpression.h"

PostfixExpression::PostfixExpression(const Table<std::string, size_t>& priority, const Table<std::string, double>& variables = Table<std::string, double>(0))
{
	_priority = priority;
	_variables = variables;
}

std::vector<std::string> PostfixExpression::GetInfix() const
{
	return _infix;
}

std::vector<std::string> PostfixExpression::GetPostFix() const
{
	return _postfix;
}

void PostfixExpression::initialize(const std::string& strInit)
{
	std::string buffer;
	for (size_t i = 0; i < strInit.size(); i++) {
		std::string symb;
		symb.push_back(strInit[i]);
		if (strInit[i] == ' ')
			continue;
		if (strInit[i] == '(' || strInit[i] == ')' || _priority.isKeyExist(symb)) {
			if (buffer != "") {
				_infix.push_back(buffer);
				buffer.clear();
			}
			_infix.push_back(symb);
			continue;
		}
		buffer.push_back(strInit[i]);
	}
	if (buffer != "")
		_infix.push_back(buffer);
}

void PostfixExpression::ToPostfix(const std::string& expr)
{
	initialize(expr);
	if (_exprCheck.isValidExpression(_infix, _priority)) {
		for (size_t i = 0; i < _infix.size(); i++) {
			if (_priority.isKeyExist(_infix[i])) {
				if (_infix[i] != "(")
					while (!_operandsStack.CheckEmpty() && _priority[_infix[i]] <= _priority[_operandsStack.Top()]) {
						_postfix.push_back(_operandsStack.Pop());
					}
				_operandsStack.Push(_infix[i]);

			}
			else {
				if (_infix[i] != ")") {
					_postfix.push_back(_infix[i]);
				}
				else {
					while (_operandsStack.Top() != "(") {
						_postfix.push_back(_operandsStack.Pop());
					}
					_operandsStack.Pop();
				}

			}

		}
		while (!_operandsStack.CheckEmpty()) {
			_postfix.push_back(_operandsStack.Pop());
		}
	}
}

double PostfixExpression::Calculate(const std::string& expr)
{
	ToPostfix(expr);
	for (size_t i = 0; i < _postfix.size(); i++) {
		if (!_priority.isKeyExist(_postfix[i])) {
			if (!_variables.isKeyExist(_postfix[i])) {
				_valueStack.Push(std::stod(_postfix[i]));
			}
			else {
				_valueStack.Push(_variables[_postfix[i]]);
			}
		}
		else {
			double operand2 = _valueStack.Pop();
			double operand1;
			if (!_valueStack.CheckEmpty())
				operand1 = _valueStack.Pop();
			if (_postfix[i] == "+") {
				_valueStack.Push(operand1 + operand2);
				continue;
			}
			if (_postfix[i] == "-") {
				_valueStack.Push(operand1 - operand2);
				continue;
			}
			if (_postfix[i] == "*") {
				_valueStack.Push(operand1 * operand2);
				continue;
			}
			if (_postfix[i] == "/") {
				if (operand2 == 0)
					throw "Cannot divide by zero";
				_valueStack.Push(operand1 / operand2);
				continue;
			}
			if (_postfix[i] == "^") {
				_valueStack.Push(pow(operand1, operand2));
				continue;
			}
			if (_postfix[i] == "sin") {
				_valueStack.Push(operand1);
				_valueStack.Push(sin(operand2));
				continue;
			}
			if (_postfix[i] == "cos") {
				_valueStack.Push(operand1);
				_valueStack.Push(cos(operand2));
				continue;
			}
			if (_postfix[i] == "tan") {
				_valueStack.Push(operand1);
				_valueStack.Push(tan(operand2));
				continue;
			}
			if (_postfix[i] == "atan") {
				_valueStack.Push(operand1);
				_valueStack.Push(atan(operand2));
				continue;
			}
			if (_postfix[i] == "asin") {
				_valueStack.Push(operand1);
				_valueStack.Push(asin(operand2));
				continue;
			}
			if (_postfix[i] == "acos") {
				_valueStack.Push(operand1);
				_valueStack.Push(acos(operand2));
				continue;
			}
			if (_postfix[i] == "sqrt") {
				_valueStack.Push(operand1);
				if (operand2 < 0)
					throw "Cannot to extract the root from a number less than zero";
				_valueStack.Push(sqrt(operand2));
				continue;
			}
		}
	}
	return _valueStack.Pop();
}

std::vector<double> PostfixExpression::solveFunc(const std::string& func, std::vector<double>& arr)
{
	Table<std::string, double> operands(1);
	operands.Append("x", arr[0]);
	std::vector<double> arrRes;

	for (int i = 0; i < arr.size(); i++) {
		operands.Change("x", arr[i]);
		this->_variables = operands;
		double res = this->Calculate(func);
		this->_infix.clear();
		this->_postfix.clear();
		arrRes.push_back(res);
	}
	return arrRes;
}
