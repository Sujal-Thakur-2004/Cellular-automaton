
/*

Manchester Baby Simulator
Group 5 Submission Date:1 December 2023 AC21009
Names: Abz Mohamed, Khoi Nguyen, Khushaal Choithramani, Sanskar Basnet, Sujal Thakur

*/

#include "Simulator.h"
#include <iostream>
#include <fstream>
#include <vector>

Simulator::Simulator() : store(32, std::vector<int>(32, 0)), CI(0), accumulator(), stopLamp(false) {}

void Simulator::loadProgram()
{
    std::string filename;
    std::cout << " Enter program file name: ";
    std::cin >> filename;

    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cerr << " Error (Unable to open the file) " << filename << std::endl;
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        return;
    }

    std::string line;
    int lineCount = 0;

    while (std::getline(file, line) && lineCount < store.size())
    {
        if (line.length() == 32)
        {
            for (int i = 0; i < 32; ++i)
            {
                if (line[i] == '0' || line[i] == '1')
                {
                    store[lineCount][i] = line[i] - '0';
                }
                else
                {
                    std::cerr << " Error (Invalid characters in the file) " << filename << " at line " << lineCount + i << ", position " << i + 1 << std::endl;
                    file.close();
                    return;
                }
            }
            ++lineCount;
        }
        else
        {
            std::cerr << " Error (Invalid line length in file) " << std::endl;
            file.close();
            return;
        }
    }

    file.close();
}

void Simulator::runSim()
{

    do
    {

        increment_CI();
        std::vector<int> instruction = fetch();
        if (!instruction.empty())
        {
            int opcode, operand;

            decode(instruction, opcode, operand);
            std::cout << "Executing: Opcode: " << opcode << " Operand: " << operand << std::endl;

            std::cout << "Before Execution - ";
            printState();

            execute(opcode, operand);
            std::cout << "After Execution - ";
            printState();
        }
        else
        {
            std::cerr << " Error (Invalid instruction) " << std::endl;
            stopLamp = true;
        }
        if (stopLamp)
        {
            break;
        }

    } while (true);
}

void Simulator::increment_CI()
{

    CI++;
}

std::vector<int> Simulator::fetch()
{

    if (CI >= 0 && CI < store.size())
    {
        return store[CI];
    }
    else
    {
        std::cerr << " Error (Control instruction out of bounds)" << std::endl;
        stopLamp = true;
        return std::vector<int>();
    }
}

// Decoding instruction and fetching operand
void Simulator::decode(const std::vector<int> &instruction, int &opcode, int &operand)
{

    if (instruction.size() != 8)
    {
        std::cerr << " Error (Invalid instruction size in decode) " << std::endl;
        stopLamp = true;
        return;
    }

    opcode = (instruction[0] << 2) | (instruction[1] << 1) | instruction[2];
    operand = (instruction[3] << 4) | (instruction[4] << 3) | (instruction[5] << 2) | (instruction[6] << 1) | instruction[7];

    if (operand > 15 || operand < -16)
    {
        std::cerr << "Error (Invalid operand in decode)" << std::endl;
        stopLamp = true;
        return;
    }

    if (operand > 15)
    {
        operand -= 32;
    }

    if (opcode < 0 || opcode > 7)
    {
        std::cerr << " Error (Invalid opcode in decode) " << std::endl;
        stopLamp = true;
        return;
    }
}

void Simulator::execute(int opcode, int operand)
{

    switch (opcode)
    {
    case 0:
        JMP(operand);
        break; // 000
    case 1:
        JRP(operand);
        break; // 100
    case 2:
        LDN(operand);
        break; // 010
    case 3:
        STO(operand);
        break; // 110
    case 4:
        SUB(operand);
        break; // 001
    case 5:
        SUB(operand);
        break; // 101
    case 6:
        CMP();
        break; // 011
    case 7:
        STP();
        break; // 111
    case 8:
        ADD(operand);
        break; // 1101
    case 9:
        MUL(operand);
        break; // 1111
    default:
        break;
    }

    std::cout << "After execution:" << std::endl;
    printState();
}

void Simulator::printState()
{
    std::cout << " CI: " << CI << ",  Accumulator: ";
    for (int bit : accumulator)
    {
        std::cout << bit;
    }
    std::cout << ", Memory: ";

    for (const auto &row : store)
    {
        for (int bit : row)
        {
            std::cout << bit;
        }
        std::cout << " ";
    }

    std::cout << std::endl;
}

void Simulator::JMP(int operand)
{

    if (operand >= 0 && operand < store.size())
    {
        CI = operand;
    }
    else
    {
        std::cerr << " Error (Invalid operand in JMP instruction) " << std::endl;
        stopLamp = true;
        return;
    }
}

void Simulator::JRP(int operand)
{

    if (operand >= 0 && CI + operand < store.size())
    {
        CI += operand;
    }
    std::cerr << " Error (Invalid operand in JRP instruction) " << std::endl;
    stopLamp = true;
    return;
}

void Simulator::LDN(int operand)
{
    for (int i = 0; i < accumulator.size(); ++i)
    {
        accumulator[i] = -store[operand][i];
    }
}

void Simulator::STO(int operand)
{

    for (int i = 0; i < accumulator.size(); ++i)
    {
        store[operand][i] = accumulator[i];
    }
}

void Simulator::SUB(int operand)
{
    for (int i = 0; i < accumulator.size(); ++i)
    {
        accumulator[i] -= store[operand][i];
    }
}

void Simulator::MUL(int operand)
{
    for (int i = 0; i < accumulator.size(); ++i)
    {
        accumulator[i] *= store[operand][i];
    }
}

void Simulator::ADD(int operand)
{
    for (int i = 0; i < accumulator.size(); ++i)
    {
        accumulator[i] += store[operand][i];
    }
}

void Simulator::CMP()
{
    int sum = 0;
    for (int bit : accumulator)
    {
        sum += bit;
    }

    if (sum < 0)
    {
        CI++;
    }
}

void Simulator::STP()
{

    stopLamp = true;
}

void menu()
{
    Simulator simulator;
    int choice;

    do
    {
        std::cout << "Simulator Menu:" << std::endl;
        std::cout << " Option 1. Load in program from file and execute it " << std::endl;
        std::cout << " Exit " << std::endl;

        while (!(std::cin >> choice))
        {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cerr << "Invalid choice. Try again " << std::endl;
        }

        switch (choice)
        {
        case 1:
            simulator.loadProgram();
            simulator.runSim();
            break;
        case 0:
            std::cout << "Exiting... Bye" << std::endl;
            return;

        default:
            std::cout << "Invalid choice. Try again " << std::endl;
            break;
        }
    } while (true);
}

int main()
{

    menu();
    return 0;
}
