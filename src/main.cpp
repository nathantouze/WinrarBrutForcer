#include "ArgParser.hpp"
#include "ArgParserException.hpp"
#include "WinrarBrutForcer.hpp"
#include "BrutforcerPool.hpp"
#include <iostream>
#include <cstdlib>

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
    BrutForcerPool brutforcer(parser.getFilepath() + "/" +  parser.getFilename(), parser.getCharsEnabled());
    brutforcer.setup();
    brutforcer.start();
    brutforcer.clear();
    return 0;
}