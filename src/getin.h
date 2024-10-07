#ifndef GETIN_H
#define GETIN_H
#include <fstream>
#include <iostream>
#include <string>
#include<vector>
struct literal {
    int original_value; // 原始的文字值
    int value;
    bool assigned;
    bool satisfied;
    literal(int val) : original_value(val), value(val), assigned(false), satisfied(false) {}
};
class clause{
    public:
    std::vector<literal> literals;
    bool satisfied;
    clause(std::vector<int> &lits){
        satisfied = false;
        for(int i = 0; i < lits.size(); i++){
            literals.push_back(literal(lits[i]));
        }
    }
};
void getin(std::ifstream &in, std::string &filename,int &variables,int &clauseCnt,std::vector<clause> &clauses);    
void getClause(std::vector<clause> &clauses, std::ifstream &in, int &cla,int &variables);
#endif // GETIN_H