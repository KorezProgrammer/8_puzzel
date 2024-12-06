#include <iostream>
#include <conio.h>
#include <ctime>
#include <vector>

#define cout std::cout
#define cin std::cin
#define string std::string

void printTableWithLines(const std::vector<std::vector<char>>& arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << "+";
        for (int j = 0; j < size; j++)
        {
            cout << "---+";
        }
        cout << "\n|";
        for (int j = 0; j < size; j++)
        {
            cout << " " << arr[i][j] << " |";
        }
        cout << "\n";
    }
    cout << "+";
    for (int j = 0; j < size; j++)
    {
        cout << "---+";
    }
    cout << "\n";
}

bool checkGoal(const std::vector<std::vector<char>>& arr, const std::vector<std::vector<char>>& goal, const std::vector<std::vector<char>>& reverseGoal, int size)
{
    bool normalGoal = true, reverseGoalAchieved = true;

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (arr[i][j] != goal[i][j])
                normalGoal = false;
            if (arr[i][j] != reverseGoal[i][j])
                reverseGoalAchieved = false;
        }
    }

    return normalGoal || reverseGoalAchieved;
}

bool isSolvable(const std::vector<std::vector<char>>& arr, int size)
{
    int invCount = 0;
    std::vector<char> flat;

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (arr[i][j] != ' ')
                flat.push_back(arr[i][j]);
        }
    }

    for (size_t i = 0; i < flat.size(); i++)
    {
        for (size_t j = i + 1; j < flat.size(); j++)
        {
            if (flat[i] > flat[j])
            {
                invCount++;
            }
        }
    }
    return (invCount % 2 == 0);
}

void shufflePuzzle(std::vector<std::vector<char>>& arr, int size)
{
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
    do
    {
        for (int i = 0; i < size * size; i++)
        {
            int x1 = rand() % size, y1 = rand() % size;
            int x2 = rand() % size, y2 = rand() % size;
            std::swap(arr[x1][y1], arr[x2][y2]);
        }
    } while (!isSolvable(arr, size));
}

void printNeighbors(const std::vector<std::vector<char>>& arr, int emptyX, int emptyY, int size)
{
    cout << "Existing operations:";
    if (emptyY > 0)
        cout << " Right: " << arr[emptyX][static_cast<std::vector<char, std::allocator<char>>::size_type>(emptyY) - 1] << "|";
    if (emptyY < size - 1)
        cout << " Left: " << arr[emptyX][static_cast<std::vector<char, std::allocator<char>>::size_type>(emptyY) + 1] << "|";
    if (emptyX > 0)
        cout << " Down: " << arr[static_cast<std::vector<char, std::allocator<char>>::size_type>(emptyX) - 1][emptyY] << "|";
    if (emptyX < size - 1)
        cout << " Up: " << arr[static_cast<std::vector<char, std::allocator<char>>::size_type>(emptyX) + 1][emptyY] << "|";
}

int main()
{
    cout << "Enter the size of the puzzle (e.g., 3 for 3x3): ";
    int size = 0;
    cin >> size;
    std::vector<std::vector<char>> start(size, std::vector<char>(size));
    std::vector<std::vector<char>> goal(size, std::vector<char>(size));
    std::vector<std::vector<char>> reverseGoal(size, std::vector<char>(size));
    string numbers = "123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz ";
    int totalElements = size * size;
    int k = 0;
    int z = totalElements - 2;
    int emptyX, emptyY;
    char cOperator = 0;
    int control = 0;

    while (size <= 2 || size % 2 == 0)
    {
        cout << "The number must be odd and bigger than 2. Please enter again: ";
        cin >> size;
    }
    if (size == 5)
    {
        cout << "\nNumbers > Letters\n";
    }
    else if (size == 7)
    {
        cout << "\nNumbers > Capital letters > Lowercase letters\n";
    }

    if (totalElements > numbers.size())
    {
        cout << "Error: Puzzle size too large!";
        return -1;
    }

    // Initialize goal and reverseGoal
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (i == size - 1 && j == size - 1) 
            {
                reverseGoal[i][j] = ' ';
            }
            else 
            {
                reverseGoal[i][j] = numbers[z--];
            }
            goal[i][j] = numbers[k++];
        }
    }
    goal[static_cast<std::vector<char, std::allocator<char>>::size_type>(size) - 1][static_cast<std::vector<char, std::allocator<char>>::size_type>(size) - 1] = ' ';

    // Shuffle the start state
    start = goal;
    shufflePuzzle(start, size);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (start[i][j] == ' ')
            {
                emptyX = i;
                emptyY = j;
            }
        }
    }

    cout << "\nStart state:\n";
    printTableWithLines(start, size);
    cout << "Use arrow keys to move (Esc to exit):\n";
    printNeighbors(start, emptyX, emptyY, size);
    cout << "\n";

    while (cOperator != 27)
    {
        if (checkGoal(start, goal, reverseGoal, size))
        {
            cout << "\nPuzzle solved! :) Total moves: " << control << "\n";
            break;
        }

        if (_kbhit())
        {
            cOperator = _getch();

            if (cOperator == 80 && emptyX > 0)
            {
                cout << "\nDown arrow";
                std::swap(start[static_cast<std::vector<char, std::allocator<char>>::size_type>(emptyX)-1][emptyY], start[emptyX][emptyY]);
                emptyX--;
                control++;
                cout << "\nTotal moves: " << control << "\n";
                printNeighbors(start, emptyX, emptyY, size);
                cout << "\n";
                printTableWithLines(start, size);
            }
            else if (cOperator == 72 && emptyX < size - 1)
            {
                cout << "\nUp arrow";
                std::swap(start[static_cast<std::vector<char, std::allocator<char>>::size_type>(emptyX)+1][emptyY], start[emptyX][emptyY]);
                emptyX++;
                control++;
                cout << "\nTotal moves: " << control << "\n";
                printNeighbors(start, emptyX, emptyY, size);
                cout << "\n";
                printTableWithLines(start, size);
            }
            else if (cOperator == 75 && emptyY < size - 1)
            {
                cout << "\nLeft arrow";
                std::swap(start[emptyX][static_cast<std::vector<char, std::allocator<char>>::size_type>(emptyY)+1], start[emptyX][emptyY]);
                emptyY++;
                control++;
                cout << "\nTotal moves: " << control << "\n";
                printNeighbors(start, emptyX, emptyY, size);
                cout << "\n";
                printTableWithLines(start, size);
            }
            else if (cOperator == 77 && emptyY > 0)
            {
                cout << "\nRight arrow";
                std::swap(start[emptyX][static_cast<std::vector<char, std::allocator<char>>::size_type>(emptyY)-1], start[emptyX][emptyY]);
                emptyY--;
                control++;
                cout << "\nTotal moves: " << control << "\n";
                printNeighbors(start, emptyX, emptyY, size);
                cout << "\n";
                printTableWithLines(start, size);
            }
        }
    }
    cOperator = _getch();
    return 0;
}
