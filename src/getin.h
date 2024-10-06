#ifndef GETIN_H
#define GETIN_H
#include <fstream>
#include <iostream>
#include<vector>
void getin(std::ifstream &in, std::string &filename,int &variables,int &clause);
void getClause(std::vector<std::vector<int>> &clauses, std::ifstream &in, int &clause,int &variables);
#endif // GETIN_H