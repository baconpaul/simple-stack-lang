#define IMPLEMENT_SIMPLE_STACK_LANG
#include "simple-stack-lang.hpp"
#include <iomanip>
#include <iostream>
#include <strstream>

template<class T>
void runFromStdin(T interpreter, bool debug)
{
    std::ostrstream oss;
    interpreter.setDebug(debug);
    
    std::cout << "Interpreter [" << interpreter.name << "]" << std::endl;
    while(std::cin)
    {
        std::string line;
        std::getline(std::cin, line);
        oss << line << "\n";
    }
    std::string program = oss.str();

    typename T::parseResult_t pr = interpreter.parse(program);
    interpreter.run(pr);
}
    

int main(int argc, char **argv)
{

    runFromStdin(BFInterpreter(), true);
    
    return 0;
}
