#pragma once

#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <iomanip>
#include <deque>

struct BFInterpreter
{
    int stackSize;
    std::string program;
    std::set<char> validCommands;
    static constexpr bool debug=true;

    BFInterpreter(std::string iprogram, int istackSize=30000) {
        program = iprogram;
        stackSize = istackSize;

        validCommands.insert('+');
        validCommands.insert('-');
        validCommands.insert('>');
        validCommands.insert('<');
        validCommands.insert(']');
        validCommands.insert('[');
        validCommands.insert(',');
        validCommands.insert('.');        
        
        doParse();
    }


    std::vector<char> programCommands;
    
    void doParse() {
        for(auto c : program)
            if(validCommands.find(c) != validCommands.end())
                programCommands.push_back(c);
    }

    void run() {
        int stk0=stackSize/2, pgm=0, stk=0;
        std::deque<int> loopPoints;
        std::vector<int> stack;
        stack.resize(stackSize, 0);

        while(pgm < programCommands.size())
        {
            char ccmd = programCommands[pgm];
            if(debug)
                std::cout << "cmd='" << ccmd << "' ";
            switch(ccmd)
            {
            case '+':
                stack[stk+stk0]++;
                pgm++;
                break;
            case '-':
                stack[stk+stk0]--;
                pgm++;
                break;
            case '>':
                stk++;
                pgm++;
                break;
            case '<':
                stk--;
                pgm++;
                break;
            case '[':
                loopPoints.push_front(pgm);
                pgm++;
                break;
            case ']':
                if(stack[stk+stk0]==0)
                {
                    loopPoints.pop_front();
                    pgm++;
                }
                else
                {
                    pgm = loopPoints.front();
                    pgm++;
                }
                break;
            case '.':
                std::cout << "\n. -> " << stack[stk+stk0] << " = " << (char)(stack[stk+stk0]) << std::endl;
                pgm++;
                break;
            case ',':
                pgm++;
                break;
            }
            if(debug)
            {
                std::cout << "STATE"
                          << " pgm=" << std::setw(5) << pgm
                          << " stk=" << std::setw(5) << stk 
                          << " sval: ";
                for(int i=-2;i<3;++i)
                    if(stk+stk0+i>=0 && stk+stk0+i<stackSize)
                        std::cout << " s[" << std::setw(3) << stk+i << "]=" << std::setw(5) << stack[stk + stk0 + i];
                
                std::cout << " loop: ";
                for(auto lp : loopPoints )
                    std::cout << " " << std::setw(4) << lp;
                std::cout << std::endl;
            }
        }
    }

    
};

#ifdef IMPLEMENT_SIMPLE_STACK_LANG
#endif
