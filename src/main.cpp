#include "getin.h"
#include "algo.h"
#include <fstream>
#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {
    std::ifstream in;
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }
    std::string filename = argv[1];
    int variables, clauseCount;
    std::vector<clause> clauses;

    // 从文件中读取子句
    getin(in, filename, variables, clauseCount, clauses);
    in.close();

    // 输出读取到的数据
    std::cout << "Variables: " << variables << std::endl;
    std::cout << "Clauses: " << clauseCount << std::endl;
    for (const auto &cl : clauses) {
        std::cout << "Clause: ";
        for (const auto &lit : cl.literals) {
            std::cout << lit.original_value << " ";
        }
        std::cout << std::endl;
    }

    // 调用DPLL算法
    if (dpll(clauses)) {
        std::cout << "SATISFIABLE" << std::endl;
        std::cout << "One possible assignment:" << std::endl;
        for (const auto &cl : clauses) {
            for (const auto &lit : cl.literals) {
                if (lit.assigned) {
                    std::cout << (lit.original_value > 0 ? lit.original_value : -lit.original_value) << " = " << (lit.value ? "true" : "false") << std::endl;
                }
            }
        }
    } else {
        std::cout << "UNSATISFIABLE" << std::endl;
    }

    return 0;
}