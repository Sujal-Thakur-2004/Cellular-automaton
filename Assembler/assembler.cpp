#include <iostream>
#include <fstream>
using namespace std;


void checkline(string line)
{
    cout << line << endl;
}


void loadFile(string fileName)
{
    ifstream inputFile(fileName);

    if (!inputFile.is_open())
    {
        cerr << "Error opening file!" << std::endl;
        return;
    }

    string line;

    for (int i = 0; i < 2; i++)
    {
        while (getline(inputFile, line))
        {
            int semicolonPos = line.find(';');

            if (semicolonPos != string::npos)
            {
                if (semicolonPos == 0)
                {
                    cout << "Skipping comments" << endl;
                }
                else
                {
                    checkline(line.substr(0, semicolonPos));
                }
            }
            else
            {
                checkline(line);
            }
        }
    }

    inputFile.close();
}

string InstructionSet(string instruction){
	if(instruction == "JMP"){
		return "000";
	}else if(instruction == "JRP"){
		return "100";
	}else if(instruction == "LDN"){
		return "010";
	}else if(instruction == "STO"){
		return "110";
	}else if(instruction == "SUB"){
		return "001";
	}else if(instruction == "CMP"){
		return "011";
	}else if(instruction == "STP"){
		return "111";
	}else{
		return "";
	}
}



void outputFile()
{
}

int main(int argc, char const *argv[])
{
    loadFile("BabyTest1-Assembler.txt");
    return 0;
}
