#include <iostream>
#include <vector>
#include <limits>
#include <cstdlib>
#include <string>
#include <fstream>
#define SizeOfBoard 15

using namespace std;

char board[15][15]; // Global char array for the board



void addToFile(vector<string>& generation) {
    ifstream inputFile("Automaton.txt");
    if (inputFile.is_open()) {
        string line;
        while (getline(inputFile, line)) {
            generation.push_back(line);
        }
        inputFile.close();
    } else {
        cerr << "Error: Unable to open the file 'Automaton.txt' for reading.\n";
    }

    ofstream outputFile("Automaton.txt");
    for (string cell : generation) {
        outputFile << cell << endl;
    }
    outputFile.close();
}

void applyingRule(vector<int> &parentGeneration, int numGenerations)
{
    vector<int> ruleSet(8);
    string ruleSetInput;
    vector<string> charGrid;
    
    while (true)
    {
        cout << "Enter a rule set as an 8-bit binary string (e.g., 00011110) or just give the rule (e.g., 30): ";
        cin >> ruleSetInput;
        bool validInput;
        try
        {
            int num = std::stoi(ruleSetInput);

            // Check if the input is 8 characters long and consists of '0' or '1' characters.
            if (ruleSetInput.length() == 8 && (ruleSetInput.find_first_not_of("01") == string::npos))
            {
                for (int i = 0; i < 8; i++)
                {
                    ruleSet[i] = ruleSetInput[i] - '0';
                }
                int decimalValue;
                decimalValue = stoi(ruleSetInput, nullptr, 2);
                string whichRule = "Using Rule " + to_string(decimalValue);
                charGrid.push_back(whichRule);
                validInput = true;
            }
            else if (num >= 1 && num < 256)
            {
                string whichRule = "Using Rule " + to_string(num);
                charGrid.push_back(whichRule);
                string binaryString;
                while (num > 0)
                {
                    binaryString = to_string(num % 2) + binaryString;
                    num /= 2;
                }
                int numZerosToAdd = 8 - binaryString.length();
                for (int i = 0; i < numZerosToAdd; i++)
                {
                    binaryString = "0" + binaryString;
                }
                for (int i = 0; i < 8; i++)
                {
                    ruleSet[i] = binaryString[i] - '0';
                }
                
                validInput = true;
            }else {
                validInput = false;
            }

            if (validInput)
            {
                break; // Exit the loop if the input is valid.
            }
            else
            {
                cout << "Invalid input. Please enter an 8-bit binary string (consisting of 0s and 1s) or rule upto 256.\n";
            }
        }
        catch (const std::invalid_argument &)
        {
            cout << "Incorrect Input" << endl;
            continue;
        }
    }

    int n = parentGeneration.size();
    vector<int> nextGeneration(n);

    for (int generation = 0; generation < numGenerations; generation++)
    {
        for (int i = 0; i < n; i++)
        {
            int left = parentGeneration[(i - 1 + n) % n]; // Wrap left end
            int right = parentGeneration[(i + 1) % n];    // Wrap right end
            if (left == 1 && right == 1 && parentGeneration[i] == 1)
            {
                if (ruleSet[0] == 1)
                {
                    nextGeneration[i] = 1;
                }
                else
                {
                    nextGeneration[i] = 0;
                }
            }
            else if (left == 1 && right == 1 && parentGeneration[i] == 0)
            {
                if (ruleSet[1] == 1)
                {
                    nextGeneration[i] = 1;
                }
                else
                {
                    nextGeneration[i] = 0;
                }
            }
            else if (left == 1 && right == 0 && parentGeneration[i] == 1)
            {
                if (ruleSet[2] == 1)
                {
                    nextGeneration[i] = 1;
                }
                else
                {
                    nextGeneration[i] = 0;
                }
            }
            else if (left == 1 && right == 0 && parentGeneration[i] == 0)
            {
                if (ruleSet[3] == 1)
                {
                    nextGeneration[i] = 1;
                }
                else
                {
                    nextGeneration[i] = 0;
                }
            }
            else if (left == 0 && right == 1 && parentGeneration[i] == 1)
            {
                if (ruleSet[4] == 1)
                {
                    nextGeneration[i] = 1;
                }
                else
                {
                    nextGeneration[i] = 0;
                }
            }
            else if (left == 0 && right == 1 && parentGeneration[i] == 0)
            {
                if (ruleSet[5] == 1)
                {
                    nextGeneration[i] = 1;
                }
                else
                {
                    nextGeneration[i] = 0;
                }
            }
            else if (left == 0 && right == 0 && parentGeneration[i] == 1)
            {
                if (ruleSet[6] == 1)
                {
                    nextGeneration[i] = 1;
                }
                else
                {
                    nextGeneration[i] = 0;
                }
            }
            else if (left == 0 && right == 0 && parentGeneration[i] == 0)
            {
                if (ruleSet[7] == 1)
                {
                    nextGeneration[i] = 1;
                }
                else
                {
                    nextGeneration[i] = 0;
                }
            }
        }

        string parentGenerationString;
        // Print the current generation
        for (int cell : parentGeneration)
        {
            if (cell == 1)
            {
                cout << " V "; // You can change the character to visualize the output.
                parentGenerationString = parentGenerationString + " V ";
            }
            else
            {
                cout << " . ";
                parentGenerationString = parentGenerationString + " . ";
            }
        }
        cout << endl;
        
        charGrid.push_back(parentGenerationString);
        // Update the parent generation with the next generation
        parentGeneration = nextGeneration;
    }
    char choice;
     while (true) {
        cout << "Do you want to save the output to a file? (y/n): ";
        cin >> choice;
        if (choice == 'y' || choice == 'n') {
            if(choice == 'y'){
                addToFile(charGrid);
            }
            break;
        } else {
            cout << "Invalid input. Please enter 'y' for yes or 'n' for no.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}


void CellularAutomaton()
{
    while (true)
    {
        cout << "Select an option:\n";
        cout << "1. Enter a custom first generation\n";
        cout << "2. Generate a random first generation\n";
        cout << "3. Exit\n";

        int option;
        cin >> option;

        switch (option)
        {
        case 1:
        {
            cout << "Enter the custom first generation as a binary string: (e.g., 00000100000)";
            string customGeneration;
            cin >> customGeneration;

            if (customGeneration.find_first_not_of("01") != string::npos)
            {
                cout << "Invalid input. Please enter an 8-bit binary string (consisting of 0s and 1s).\n";
                continue; // Restart the loop
            }

            vector<int> firstGeneration;

            // Convert the binary string to an array of integers.
            for (char bit : customGeneration)
            {
                int value = bit - '0';
                firstGeneration.push_back(value);
            }

            cout << "Enter the number of generations to produce: ";
            int numGenerations;
            while (true)
            {
                cin >> numGenerations;

                if (numGenerations <= 0)
                {
                    cout << "Invalid input.Please enter a positive integer for the length.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                else
                {
                    break;
                }
            }

            applyingRule(firstGeneration, numGenerations);

            break;
        }
        case 2:
        {
            cout << "Enter the length of the random first generation: ";
            int length = 0;

            while (true)
            {
                cin >> length;

                if (length <= 0)
                {
                    cout << "Invalid input.Please enter a positive integer for the length.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                else
                {
                    break;
                }
            }

            vector<int> randomGeneration;

            for (int i = 0; i < length; ++i)
            {
                int randomBit = rand() % 2; // Generate 0 or 1 randomly.
                randomGeneration.push_back(randomBit);
            }

            cout << "Enter the number of generations to produce: ";
            int numGenerations;

            while (true)
            {
                cin >> numGenerations;

                if (numGenerations <= 0)
                {
                    cout << "Invalid input.Please enter a positive integer for the length.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                else
                {
                    break;
                }
            }
            applyingRule(randomGeneration, numGenerations);

            break;
        }
        case 3:
        {
            cout << "Exiting the program.\n";
            return;
        }
        default:
            cout << "Invalid option selected. Please enter a valid option.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

void displayBoard(char board[SizeOfBoard][SizeOfBoard])
{

    cout << "\nUpdated Grid with Cells:\n";
    cout << " ";
    for (int col = 1; col <= SizeOfBoard - 5; col++)
    {
        cout << "   " << col;
    }
    for (int col = 11; col <= SizeOfBoard; col++)
    {
        cout << "  " << col;
    }

    cout << "\n  ";
    for (int col = 0; col < SizeOfBoard; col++)
    {
        cout << "|---";
    }
    cout << "|\n";

    for (int row = 0; row < SizeOfBoard; row++)
    {
        if (row + 1 < 10)
        {
            cout << " " << row + 1 << "|";
        }
        else
        {
            cout << row + 1 << "|";
        }
        for (int col = 0; col < SizeOfBoard; col++)
        {
            cout << " " << board[row][col] << " |";
        }
        cout << "\n  ";
        for (int col = 0; col < SizeOfBoard; col++)
        {
            cout << "|---";
        }
        cout << "|\n";
    }
}

void motion()
{
    char parentBoard[SizeOfBoard][SizeOfBoard];
    for (int i = 0; i < SizeOfBoard; i++)
    {
        for (int j = 0; j < SizeOfBoard; j++)
        {
            parentBoard[i][j] = board[i][j];
        }
    }
    char childBoard[SizeOfBoard][SizeOfBoard];
    while (true)
    {
        for (int i = 0; i < SizeOfBoard; i++)
        {
            for (int j = 0; j < SizeOfBoard; j++)
            {
                // Count live neighbors
                int liveNeighbors = 0;
                for (int offsetX = -1; offsetX <= 1; offsetX++)
                {
                    for (int offsetY = -1; offsetY <= 1; offsetY++)
                    {
                        if (offsetX == 0 && offsetY == 0)
                            continue; // Skip the current cell
                        int neighborI = i + offsetX;
                        int neighborJ = j + offsetY;
                        if (neighborI >= 0 && neighborI < SizeOfBoard && neighborJ >= 0 && neighborJ < SizeOfBoard && parentBoard[neighborI][neighborJ] == 'V')
                        {
                            liveNeighbors++;
                        }
                    }
                }

                if (parentBoard[i][j] == 'V')
                {
                    // Current cell is alive
                    if (liveNeighbors < 2 || liveNeighbors > 3)
                    {
                        childBoard[i][j] = '.'; // Cell dies
                    }
                    else
                    {
                        childBoard[i][j] = 'V'; // Cell survives
                    }
                }
                else
                {
                    // Current cell is dead
                    if (liveNeighbors == 3)
                    {
                        childBoard[i][j] = 'V'; // Cell becomes alive
                    }
                    else
                    {
                        childBoard[i][j] = '.'; // Cell remains dead
                    }
                }
            }
        }
        displayBoard(childBoard);
        for (int i = 0; i < SizeOfBoard; i++)
        {
            for (int j = 0; j < SizeOfBoard; j++)
            {
                parentBoard[i][j] = childBoard[i][j];
            }
        }
        char ch;
        cin.get(ch);
        if (ch == 'q')
        {
            break;
        }
        else
        {
            continue;
        }
    }
}

void startDeathGame()
{

    int numberOfCells;
    cout << "How many cells: ";
    cin >> numberOfCells;

    // Initialize the board with '.' initially
    for (int i = 0; i < SizeOfBoard; i++)
    {
        for (int j = 0; j < SizeOfBoard; j++)
        {
            board[i][j] = '.';
        }
    }

    for (int i = 0; i < numberOfCells; i++)
    {
        int cellRow, cellCol;

        cout << "Enter the row and column for cell " << i + 1 << " (e.g., 1 3): ";
        cin >> cellRow >> cellCol;

        if (cellRow >= 1 && cellRow <= SizeOfBoard && cellCol >= 1 && cellCol <= SizeOfBoard)
        {
            board[cellRow - 1][cellCol - 1] = 'V'; // Place a cell at the specified row and column
            displayBoard(board);
        }
        else
        {
            cout << "Invalid input. Please enter a valid row and column." << endl;
            i--; // Decrement counter to re-enter cell placement for the same cell
        }
    }

    cout << "Are you done? y/n";

    while (true)
    {
        char check;
        cin >> check;

        if (check == 'y')
        {
            motion();
            break;
        }
        else if (check == 'n')
        {

            break;
        }
        else
        {
            cout << "Invalid input. Plaese type y/n";
        }
    }
}

int main()
{
    int choice;

    while (true)
    {
        cout << "Menu:\n";
        cout << "1. Run 1D Cellular Automaton\n";
        cout << "2. Start Death Game\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice))
        {
            // If the input is not an integer, clear the error flag and discard the input.
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid option.\n";
            continue;
        }
        switch (choice)
        {
        case 1:
            CellularAutomaton();
            break;
        case 2:
            startDeathGame();
            break;
        case 3:
            cout << "Exiting the program. Goodbye!" << endl;
            return 0;
        default:
            cout << "Invalid choice. Please select a valid option.\n";
        }
    }

    return 0;
}
