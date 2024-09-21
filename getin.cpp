#include "getin.h"

void getin(std::ifstream &in, std::string &filename)
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
        //std::cout << comment << std::endl;
        in >> ch;
    }

}
