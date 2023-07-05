#include "pch.h"
#include "C:\C++, C projects\Course2Lab3\Course2Lab3\PostfixExpression.h"

Table<std::string, size_t> priorT(13);

TEST(PostfixExpression_test, init_table) {
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
	EXPECT_EQ(priorT["+"], 1);
	EXPECT_EQ(priorT["sin"], 4);
	EXPECT_EQ(priorT["*"], 2);
	EXPECT_EQ(priorT["^"], 3);
}

TEST(TStack_test, test_throw_pop) {
	TStack<int> st(10);
	ASSERT_ANY_THROW(st.Pop());
}

TEST(TStack_test, test_pop) {
	TStack<int> st(10);
	st.Push(10);
	EXPECT_EQ(st.Pop(), 10);
}

TEST(TStack_test, test_throw_top) {
	TStack<int> st(5);
	ASSERT_ANY_THROW(st.Top());

}

TEST(TStack_test, test_top_2) {
	TStack<int> st(10);
	st.Push(10);
	st.Push(11);
	st.Push(12);
	EXPECT_EQ(st.Top(), 12);
}

TEST(TStack_test, test_drill) {
	TStack<int> st(10);
	st.Push(10);
	st.Push(11);
	st.Push(12);
	st.Pop();
	EXPECT_EQ(st.Top(), 11);
}

TEST(PostfixExpression_test, can_solve_first) {
	PostfixExpression exp(priorT);
	double res = exp.Calculate("10+4");
	EXPECT_EQ(res, 14);
}

TEST(PostfixExpression_test, can_solve_second) {
	PostfixExpression exp(priorT);
	double res = exp.Calculate("10+2*8");
	EXPECT_EQ(res, 26);
}

TEST(PostfixExpression_test, can_solve_third) {
	PostfixExpression exp(priorT);
	double res = exp.Calculate("(10+6)/2");
	EXPECT_EQ(res, 8);
}

TEST(PostfixExpression_test, can_solve_fourth) {
	PostfixExpression exp(priorT);
	double res = exp.Calculate("(14+2)/(2+6)");
	EXPECT_EQ(res, 2);
}

TEST(PostfixExpression_test, can_solve_fifth) {
	PostfixExpression exp(priorT);
	double res = exp.Calculate("((4+3)*2)^2");
	EXPECT_EQ(res, 196);
}

TEST(PostfixExpression_test, can_solve_sin) {
	PostfixExpression exp(priorT);
	double res = exp.Calculate("sin(0)");
	std::cout << res;
	EXPECT_EQ(res, 0);
}

TEST(PostfixExpression_test, can_solve_cos) {
	PostfixExpression exp(priorT);
	double res = exp.Calculate("cos(0)");
	EXPECT_EQ(res, 1);
}

TEST(PostfixExpression_test, can_solve_sqrt) {
	PostfixExpression exp(priorT);
	double res = exp.Calculate("sqrt(4)/2+2*5");
	EXPECT_EQ(res, 11);
}



TEST(PostfixExpression_test, can_solve_divide_by_zero) {
	PostfixExpression exp(priorT);
	ASSERT_ANY_THROW(exp.Calculate("1/0"));
}

TEST(PostfixExpression_test, can_solve_divide_by_zero_2){
	PostfixExpression exp(priorT);
	Table<std::string, size_t> operands(3);
	operands.Append("a", 5);
	operands.Append("b", 0);
	operands.Append("c", 3);
	ASSERT_ANY_THROW(exp.Calculate("a/b*c"));
}

TEST(PostfixExpression_test, can_solve_brackets) {
	PostfixExpression exp(priorT);
	ASSERT_ANY_THROW(exp.Calculate("()+1"));
}

TEST(PostfixExpression_test, can_solve_hard_sqrt) {
	PostfixExpression exp(priorT);
	double res = exp.Calculate("sqrt(((sqrt(16)+5)*2)^2)/2");
	EXPECT_EQ(res, 9);
}
TEST(PostfixExpression_test, can_solve_sqrt_less_zero) {
	PostfixExpression exp(priorT);
	ASSERT_ANY_THROW(exp.Calculate("sqrt(-1)+1"));
}

TEST(PostfixExpression_test, can_solve_with_variables) {
	Table<std::string, double> operands(3);
	operands.Append("a", 5);
	operands.Append("b", 2);
	operands.Append("c", 16);
	PostfixExpression exp(priorT, operands);
	double res = exp.Calculate("sqrt(((sqrt(c)+a)*2)^b)/b");
	EXPECT_EQ(res, 9);
}

TEST(PostfixExpression_test, expression_with_mistake_1) {
	PostfixExpression exp(priorT);
	ASSERT_ANY_THROW(exp.Calculate("sqrt((sqrt(16)+5)*2)^2)/2"));
}

TEST(PostfixExpression_test, expression_with_mistake_2) {
	PostfixExpression exp(priorT);
	ASSERT_ANY_THROW(exp.Calculate("sqrt(+16)"));
}

TEST(PostfixExpression_test, expression_with_mistake_3) {
	PostfixExpression exp(priorT);
	ASSERT_ANY_THROW(exp.Calculate("18+*2"));
}

TEST(PostfixExpression_test, function_test) {
	std::vector<double> a;
	std::vector<double> b;
	double s = 1;
	for (int i = 0; i < 5; i++) {
		a.push_back(s++);
	}
	b.push_back(2);
	b.push_back(4);
	b.push_back(6);
	b.push_back(8);
	b.push_back(10);

	PostfixExpression exp(priorT);
	std::vector<double> c = exp.solveFunc("x*2", a);
	bool flag = true;
	for (int i = 0; i < 5; i++) {
		if (c[i] != b[i]) {
			flag = false;
			break;
		}
	}
	EXPECT_EQ(flag, true);
}