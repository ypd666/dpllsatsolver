#include "getin.h"
#include <fstream>
#include <iostream>
#include <sstream>

void getin(std::ifstream &in, std::string &filename, int &variables, int &clauseCount, std::vector<clause> &clauses) {
    if (filename.empty()) {
        std::cout << "Enter filename: ";
        std::cin >> filename;
    }
    in.open(filename.c_str());
    if (!in.is_open()) {
        std::cerr << "Error opening file " << filename << std::endl;
        exit(1);
    }

    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) {
            continue;
        }
        std::istringstream iss(line);
        char ch;
        iss >> ch;
        if (ch == 'c') {
            // 输出评论
            //std::cout << "Comment: " << line.substr(1) << std::endl;
        } else if (ch == 'p') {
            // 读取问题行
            std::string tmp;
            iss >> tmp >> variables >> clauseCount;
            //std::cout << "Problem line: " << tmp << " " << variables << " " << clauseCount << std::endl;
        } else {
            // 读取子句
            std::vector<int> lits;
            int lit;
            iss.putback(ch); // 将第一个字符放回流中
            while (iss >> lit && lit != 0) {
                lits.push_back(lit);
            }
            clauses.push_back(clause(lits));
        }
    }
}

void getClause(std::vector<clause> &clauses, std::ifstream &in, int &clauseCnt, int &variables) {
    for (int i = 0; i < clauseCnt; i++) {
        std::vector<int> lits;
        int lit;
        in >> lit;
        while (lit != 0) {
            lits.push_back(lit);
            in >> lit;
        }
        clauses.push_back(clause(lits));
    }
}