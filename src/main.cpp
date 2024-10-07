#include "getin.h"
#include "algo.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

int main(int argc, char *argv[]) {
    std::ifstream in;
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }
    std::string filename = argv[1];
    int variables, clauseCount;
    std::vector<clause> clauses;


    getin(in, filename, variables, clauseCount, clauses);
    in.close();

    
    /*std::cout << "Variables: " << variables << std::endl;
    std::cout << "Clauses: " << clauseCount << std::endl;
    for (const auto &cl : clauses) {
        std::cout << "Clause: ";
        for (const auto &lit : cl.literals) {
            std::cout << lit.original_value << " ";
        }
        std::cout << std::endl;
    }*/

    // 调用DPLL
    if (dpll(clauses)) {
        std::cout << "SATISFIABLE" << std::endl;
        std::cout << "One possible assignment:" << std::endl;
        std::unordered_set<int> printedLiterals;
        std::vector<std::pair<int, bool>> results;

        for (const auto &cl : clauses) {
            for (const auto &lit : cl.literals) {
                int absValue = std::abs(lit.original_value);
                if (lit.assigned && printedLiterals.find(absValue) == printedLiterals.end()) {
                    results.emplace_back(absValue, lit.value);
                    printedLiterals.insert(absValue);
                }
            }
        }

        
        std::sort(results.begin(), results.end());
        for (const auto &result : results) {
            std::cout << result.first << " = " << (result.second ? "true" : "false") << std::endl;
        }
    } else {
        std::cout << "UNSATISFIABLE" << std::endl;
    }

    return 0;
}