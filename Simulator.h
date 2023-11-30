#ifndef SIMULATOR_H
#define SIMULATOR_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class Simulator {

    private:
        std::vector<std::vector<int>> store;
        int CI;
        std::vector<int> accumulator;
        bool stopLamp;
        int A;

        void increment_CI();
        std::vector<int> fetch();
        void decode(const std::vector<int>& instruction,int& opcode, int& operand);
        void execute(int opcode, int operand);
        void printState();

        void JMP(int operand);
        void JRP(int operand);
        void LDN(int operand);
        void STO(int operand); 
        void SUB(int operand);
        void CMP();
        void STP();
        void MUL(int operand);
        void ADD(int operand);

    public:

        Simulator(); // constructor
        void loadProgram();
        void runSim();

        friend std::ostream& operator<<(std::ostream& os, const Simulator& simulator);

        // add other member functions as needed 
};

#endif


