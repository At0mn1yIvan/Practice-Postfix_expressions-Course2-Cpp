#pragma once

#include <iostream>
#include <vector>

#include "Table.h"


class ExpressionValidator
{
public:
	static bool isValidExpression(const std::vector<std::string>& str, Table<std::string, size_t>& table);
};
