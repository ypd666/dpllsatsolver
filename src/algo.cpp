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
        bool hasUnassigned = false;
        for (const auto &lit : cl.literals) {
            if (!lit.assigned) {
                hasUnassigned = true;
                break;
            }
        }
        if (!hasUnassigned) {
            return true;
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
        for (auto &lit : cl.literals) {
            if (!lit.assigned) {
                unassignedCount++;
                unassignedLit = &lit;
            }
        }
        if (unassignedCount == 1 && unassignedLit != nullptr) {
            unassignedLit->assigned = true;
            unassignedLit->value = (unassignedLit->original_value > 0);
            propagated = true;
            // 将这个文字的值应用到所有出现该文字的地方
            for (auto &clause : clauses) {
                for (auto &literal : clause.literals) {
                    if (literal.original_value == unassignedLit->original_value || literal.original_value == -unassignedLit->original_value) {
                        literal.assigned = true;
                        literal.value = (literal.original_value > 0);
                        std::cout << "Propagating " << unassignedLit->original_value << " = " << (unassignedLit->value ? "true" : "false") << std::endl;
                    }
                }
            }
        }
        
    }
    for(auto &cl : clauses){
        bool hasUnassigned = false;
        for(auto &lit : cl.literals){
            if(!lit.assigned){
                hasUnassigned = true;
                break;
            }
        }
        if(!hasUnassigned){
            cl.satisfied = false;
            for(auto &lit : cl.literals){
                if(lit.value == (lit.original_value > 0)){
                    cl.satisfied = true;
                    break;
                }
            }
        }
    }
    return propagated;
}

// 递归地尝试赋值为真或假
bool dpll(std::vector<clause> &clauses) {
    if (allClausesSatisfied(clauses)) {
        return true;
    }
    if (hasEmptyClause(clauses)) {
        return false;
    }

    while (unitPropagation(clauses)) {
        if (allClausesSatisfied(clauses)) {
            return true;
        }
        if (hasEmptyClause(clauses)) {
            return false;
        }
    }

    literal* lit = selectUnassignedLiteral(clauses);
    if (lit == nullptr) {
        return false;
    }

    lit->assigned = true;
    lit->value = true;
    std::cout << "Assigning " << lit->original_value << " = true" << std::endl;
    // 将这个文字的值应用到所有出现该文字的地方
    for (auto &clause : clauses) {
        for (auto &literal : clause.literals) {
            if (literal.original_value == lit->original_value || literal.original_value == -lit->original_value) {
                literal.assigned = true;
                literal.value = (literal.original_value > 0);
            }
        }
    }
    if (dpll(clauses)) {
        return true;
    }

    lit->value = false;
    std::cout << "Assigning " << lit->original_value << " = false" << std::endl;
    // 将这个文字的值应用到所有出现该文字的地方
    for (auto &clause : clauses) {
        for (auto &literal : clause.literals) {
            if (literal.original_value == lit->original_value || literal.original_value == -lit->original_value) {
                literal.assigned = true;
                literal.value = (literal.original_value > 0);
            }
        }
    }
    if (dpll(clauses)) {
        return true;
    }

    lit->assigned = false;
    return false;
}