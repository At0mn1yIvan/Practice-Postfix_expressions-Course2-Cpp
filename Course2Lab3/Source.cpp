#include "PostfixExpression.h"
#include "ExpressionValidator.h"

int main(){
	Table<std::string, size_t> priorT(13);
	priorT.Append("+", 1);
	priorT.Append("-", 1);
	priorT.Append("*", 2);
	priorT.Append("/", 2);
	priorT.Append("^", 3);
	priorT.Append("sqrt", 4);
	priorT.Append("sin", 4);
	priorT.Append("cos", 4);
	priorT.Append("tan", 4);
	priorT.Append("asin", 4);
	priorT.Append("acos", 4);
	priorT.Append("atan", 4);
	priorT.Append("(", 0);


	//double a[] = { 1, 2, 3, 4, 5 };
	//double b[] = { 1, 4, 9, 16, 25 };

	std::vector<double> a;
	std::vector<double> b;
	double s = 1;
	for (int i = 0; i < 5; i++){
		a.push_back(s++);
	}

	PostfixExpression exp(priorT);
	std::vector<double> c = exp.solveFunc("x^2", a);
	bool flag = true;
	for (int i = 0; i < 5; i++) {
		std::cout << c[i] << " ";
	}
	return 0;
}