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
    std::string lang = "--bf";
    if( argc >= 2 )
        lang = argv[ 1 ];

    if(lang=="--bf")
        runFromStdin(BFInterpreter<>(), false);
    if(lang=="--ls")
        runFromStdin(LilStackInterpeter<>(), true );
    
    return 0;
}
