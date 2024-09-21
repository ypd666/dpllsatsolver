#include "getin.h"

void main(int argc, char *argv[])
{
    std::ifstream in;
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return;
    }
    std::string filename = argv[1];
    getin(in, filename);
    std::string line;
    in.close();
}