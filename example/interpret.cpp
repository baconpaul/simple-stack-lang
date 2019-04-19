#define IMPLEMENT_SIMPLE_STACK_LANG
#include "simple-stack-lang.hpp"
#include <iomanip>
#include <iostream>
#include <strstream>

int main(int argc, char **argv)
{
    std::ostrstream oss;
    
    std::cout << "Interpreter" << std::endl;

    while(std::cin)
    {
        std::string line;
        std::getline(std::cin, line);
        oss << line << "\n";
    }
    std::string program = oss.str();
    std::cout << "Program is:\n" <<  program << std::endl;

    BFInterpreter bfi(program);
    bfi.run();
    
    return 0;
}
