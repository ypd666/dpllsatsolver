#ifndef ALGO_H
#define ALGO_H

#include <vector>
#include "getin.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
// 检查所有子句是否满足
bool allClausesSatisfied(const std::vector<clause> &clauses);

// 检查是否存在空子句
bool hasEmptyClause(const std::vector<clause> &clauses);

// 选择一个未赋值的文字
literal* selectUnassignedLiteral(std::vector<clause> &clauses);

// 单位子句传播
bool unitPropagation(std::vector<clause> &clauses);

// 递归地尝试赋值为真或假
bool dpll(std::vector<clause> &clauses);

#endif // ALGO_H