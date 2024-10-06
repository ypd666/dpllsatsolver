#include "getin.h"

void getin(std::ifstream &in, std::string &filename,int &variables, int &clause)
{
    if (filename.empty())
    {
        std::cout << "Enter filename: ";
        std::cin >> filename;
    }
    in.open(filename.c_str());
    if (!in.is_open())
    {
        std::cerr << "Error opening file " << filename << std::endl;
        exit(1);
    }
    char ch;//in "c" for comment "p" for problem
    in >> ch;
    if (ch == 'c'){
        std::string comment;
        std::getline(in, comment);
        std::cout << comment << std::endl;
    }
    else if(ch == 'p'){
        std::string problem;
        in>>problem;
        std::cout << problem << std::endl;
        in >> variables >> clause;
        std::cout << "Variables: " << variables << " Clauses: " << clause << std::endl;
    }
    else{
        std::cerr << "Error reading file " << filename << std::endl;
        exit(1);
    }
}

void getClause(std::vector<std::vector<int>> &clauses, std::ifstream &in, int &clause,int &variables)
{
    for(int i = 0; i < clause; i++){
        std::vector<int> temp;
        int lit;
        while(in >> lit && lit != 0){
            temp.push_back(lit);
        }
        clauses.push_back(temp);
    }
}