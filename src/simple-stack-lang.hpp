#pragma once

#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <iomanip>
#include <deque>
#include <sstream>

struct StdInIOHandler
{
    std::ostream& out = std::cout;
    std::istream& in  = std::cin;
};

struct ParseError
{
    std::string line;
    ParseError(std::string l) : line(l) { }
};

template<class IOHandler = StdInIOHandler>
struct BFInterpreter
{
    int stackSize;
    std::string program;
    std::set<char> validCommands;
    bool debug=false;
    std::string name="ModifiedBrainF*ck";
    IOHandler ioh;

    BFInterpreter(int istackSize=30000) {
        stackSize = istackSize;

        validCommands.insert('+');
        validCommands.insert('-');
        validCommands.insert('>');
        validCommands.insert('<');
        validCommands.insert(']');
        validCommands.insert('[');
        validCommands.insert(',');
        validCommands.insert('.');
        validCommands.insert('{'); // put an explicit number onto the stack
    }

    void setDebug(bool d) { debug=d; }

    typedef std::vector<std::tuple<char,int>> parseResult_t;
    parseResult_t parse(std::string program) {
        parseResult_t programCommands;
        bool inNumber = false;
        std::string number;
        for(auto c : program)
        {
            if(validCommands.find(c) != validCommands.end())
                programCommands.push_back(std::make_tuple(c,0));
            if( c == '}' )
            {
                inNumber = false;
                if( std::get<0>(programCommands.back()) == '{' )
                {
                    auto num = std::atoi(number.c_str());
                    std::get<1>(programCommands.back()) = num;
                }
                else
                {
                    // That's a parse error. But this is a terrible language. So lets not tell anyone
                }
            }
            if( inNumber )
                number += c;
            
            if( c == '{' )
            {
                inNumber = true;
            }
        }
        return programCommands;
    }

    void run(const parseResult_t &programCommands) {
        int stk0=stackSize/2, pgm=0, stk=0;
        std::deque<int> loopPoints;
        std::vector<int> stack;
        stack.resize(stackSize, 0);

        while(pgm < programCommands.size())
        {
            auto ccmd = programCommands[pgm];
            if(debug)
            {
                ioh.out << "cmd='" << std::get<0>(ccmd) << "' ";
                if( std::get<0>(ccmd) == '{' )
                    ioh.out << " (n=" << std::get<1>(ccmd) << ") ";
            }
            switch(std::get<0>(ccmd))
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
                ioh.out << "Command . -> stackptr=" << stk << " val=" << (int)(stack[stk+stk0]) << std::endl;
                pgm++;
                break;
            case ',':
                pgm++;
                break;
            case '{':
                stack[stk+stk0] = std::get<1>(ccmd);
                pgm++;
                break;
            }
            if(debug)
            {
                ioh.out << "STATE"
                          << " pgm=" << std::setw(5) << pgm
                          << " stk=" << std::setw(5) << stk 
                          << " sval: ";
                for(int i=-2;i<3;++i)
                    if(stk+stk0+i>=0 && stk+stk0+i<stackSize)
                        ioh.out << " s[" << std::setw(3) << stk+i << "]=" << std::setw(5) << stack[stk + stk0 + i];
                
                ioh.out << " loop: ";
                for(auto lp : loopPoints )
                    ioh.out << " " << std::setw(4) << lp;
                ioh.out << std::endl;
            }
        }
    }
};

template<class IOHandler = StdInIOHandler>
struct LilStackInterpeter
{
    typedef enum Instruction
    {
        c_sets,
        c_movs,
        c_adds,
        c_muls,
        c_while,
        c_elihw,
        c_inc,
        c_dec,
        c_out
    } Instruction;
    struct Cmd
    {
        Instruction i;
        int arg;
    };
    
    std::string name = "LilStackLanguage";
    IOHandler ioh;
    LilStackInterpeter(int stackSize = 10000) {
    }

    bool debug = false;
    void setDebug( bool d ) { debug = d; }

    typedef std::vector<Cmd> parseResult_t;
    parseResult_t parse(std::string program) {
        parseResult_t res;

        std::istringstream f(program);
        std::string line;    
        while (std::getline(f, line)) {
            // Strip out #
            auto pos = line.find( '#' );
            if(pos != std::string::npos)
            {
                line = line.substr(0,pos);
            }
            line.erase(line.begin(), std::find_if(line.begin(), line.end(), [](int ch) {
                        return !std::isspace(ch);
                    }));
            if(line.size()!=0)
            {
                pos = line.find(' ');
                auto cmd = line.substr(0,pos);
                auto arg = line.substr(pos+1);
                int iarg;
                if( arg.size() )
                    iarg = atoi(arg.c_str());
                Cmd c;
                c.arg = iarg;
                
                if(cmd=="movs") c.i=c_movs;
                else if(cmd=="sets") c.i=c_sets;
                else if(cmd=="adds") c.i=c_adds;
                else if(cmd=="muls") c.i=c_muls;
                else if(cmd=="while") c.i=c_while;
                else if(cmd=="elihw") c.i=c_elihw;
                else if(cmd=="out") c.i=c_out;
                else if(cmd=="dec") c.i=c_dec;
                else if(cmd=="int") c.i=c_inc;
                else throw ParseError(line);

                res.push_back(c);
            }


        }
        return res;
    }

    void run(parseResult_t pgm) {
    }
};
