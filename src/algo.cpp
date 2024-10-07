#include "algo.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>

// 检查所有子句是否满足
bool allClausesSatisfied(const std::vector<clause> &clauses) {
    for (const auto &cl : clauses) {
        if (!cl.satisfied) {
            return false;
        }
    }
    return true;
}

// 检查是否存在空子句
bool hasEmptyClause(const std::vector<clause> &clauses) {
    for (const auto &cl : clauses) {
        bool allAssigned = true; // 是否所有文字都被赋值
        bool clauseSatisfied = false; // 是否子句被满足

        for (const auto &lit : cl.literals) {
            if (!lit.assigned) {
                allAssigned = false; // 如果存在未赋值的文字，子句不应视为空子句
                break;
            }
            if (lit.assigned && lit.value == (lit.original_value > 0)) {
                clauseSatisfied = true; // 如果子句被满足，跳过这个子句
                break;
            }
        }

        // 如果所有字面量都已赋值且子句没有被满足，视为空子句
        if (allAssigned && !clauseSatisfied) {
            return true; // 找到真正的空子句
        }
    }
    return false;
}


// 选择一个未赋值的文字
literal* selectUnassignedLiteral(std::vector<clause> &clauses) {
    for (auto &cl : clauses) {
        for (auto &lit : cl.literals) {
            if (!lit.assigned) {
                return &lit;
            }
        }
    }
    return nullptr;
}

// 单位子句传播
bool unitPropagation(std::vector<clause> &clauses) {
    bool propagated = false;
    for (auto &cl : clauses) {
        int unassignedCount = 0;
        literal* unassignedLit = nullptr;
        bool clauseSatisfied = false;

        // 检查子句中的所有文字
        for (auto &lit : cl.literals) {
            if (lit.assigned) {
                if (lit.value == (lit.original_value > 0)) {
                    clauseSatisfied = true; // 子句已经被满足
                    break;
                }
            } else {
                unassignedCount++;
                unassignedLit = &lit;
            }
        }

        // 如果子句被满足，跳过这个子句
        if (clauseSatisfied) {
            cl.satisfied = true;
            continue;
        }

        // 如果子句只剩下一个未赋值的文字，进行传播
        if (unassignedCount == 1 && unassignedLit != nullptr) {
            unassignedLit->assigned = true;
            unassignedLit->value = (unassignedLit->original_value > 0);
            propagated = true;

            // 输出调试信息
            std::cout << "Unit propagating literal " << unassignedLit->original_value 
                      << " = " << (unassignedLit->value ? "true" : "false") << std::endl;

            // 将这个文字的值应用到所有相关子句
            for (auto &clause : clauses) {
                for (auto &literal : clause.literals) {
                    if (literal.original_value == unassignedLit->original_value || 
                        literal.original_value == -unassignedLit->original_value) {
                        literal.assigned = true;
                        literal.value = (literal.original_value > 0);
                        std::cout << "Updating literal " << literal.original_value << " after propagation." << std::endl;
                    }
                }
            }
        }
    }
    return propagated;
}

// 递归地尝试赋值为真或假，并处理回溯
bool dpll(std::vector<clause> &clauses) {
    std::cout << "Entering DPLL function..." << std::endl;

    // 如果所有子句都已满足，返回true
    if (allClausesSatisfied(clauses)) {
        std::cout << "All clauses satisfied!" << std::endl;
        return true; 
    }

    // 如果存在空子句，表示该路径无解，回溯
    if (hasEmptyClause(clauses)) {
        std::cout << "Found empty clause, need to backtrack." << std::endl;
        return false;
    }

    // 单位子句传播，优先处理确定的文字
    while (unitPropagation(clauses)) {
        std::cout << "Propagation happened." << std::endl;
        if (allClausesSatisfied(clauses)) {
            std::cout << "All clauses satisfied after propagation!" << std::endl;
            return true;
        }
        if (hasEmptyClause(clauses)) {
            std::cout << "Empty clause found after propagation, backtracking." << std::endl;
            return false;
        }
    }

    // 选择一个未赋值的文字
    literal* lit = selectUnassignedLiteral(clauses);
    if (lit == nullptr) {
        std::cout << "No more literals to assign, backtracking..." << std::endl;
        return false; // 无可赋值的文字，回溯
    }

    // 尝试将文字赋值为 true
    lit->assigned = true;
    lit->value = true;
    std::cout << "Assigning literal " << lit->original_value << " = true" << std::endl;

    // 递归调用 dpll
    if (dpll(clauses)) {
        return true; // 如果成功找到解
    }

    // 若赋值为 true 失败，则撤销并尝试赋值为 false
    lit->value = false;
    std::cout << "Assigning literal " << lit->original_value << " = false" << std::endl;

    // 尝试递归调用 dpll
    if (dpll(clauses)) {
        return true;
    }

    // 如果赋值 false 也失败，撤销赋值
    lit->assigned = false;
    std::cout << "Unassigning literal " << lit->original_value << std::endl;
    return false;
}