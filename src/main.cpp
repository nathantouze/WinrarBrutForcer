#include "ArgParser.hpp"
#include "ArgParserException.hpp"
#include <iostream>

int main(int ac, char **av) 
{
    ArgParser parser(ac, av);

    if (parser.getHelping())
        return 0;
    try {
        parser.fill_labels();
        parser.check_labels();
    } catch (ArgParserException &err) {
        std::cout << err.what() << std::endl;
        return 1;
    }
    return 0;
}