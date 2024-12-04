#include <iostream>
#include <conio.h>
#include <ctime>

#define cout std::cout
#define string std::string

void printTableWithLines(const char arr[3][3]) 
{
    cout << "+---+---+---+\n";
    for (int i = 0; i < 3; i++) 
    {
        for (int j = 0; j < 3; j++) 
        {
            cout << "| " << arr[i][j] << " ";
        }
        cout << "|\n+---+---+---+\n";
    }
}

bool checkGoal(const char arr[3][3], const char goal[3][3]) 
{
    for (int i = 0; i < 3; i++) 
    {
        for (int j = 0; j < 3; j++) 
        {
            if (arr[i][j] != goal[i][j])
                return false;
        }
    }
    return true;
}

bool isSolvable(const char arr[3][3]) 
{
    int invCount = 0;
    char flat[9];
    int k = 0;

    for (int i = 0; i < 3; i++) 
    {
        for (int j = 0; j < 3; j++) 
        {
            flat[k++] = arr[i][j];
        }
    }

    for (int i = 0; i < 9; i++) 
    {
        for (int j = i + 1; j < 9; j++) 
        {
            if (flat[i] != ' ' && flat[j] != ' ' && flat[i] > flat[j]) 
            {
                invCount++;
            }
        }
    }
    return (invCount % 2 == 0);
}

void shufflePuzzle(char arr[3][3]) 
{
    string numbers = "12345678 ";
    srand(time(0));  // Seed the random number generator
    do 
    {
        for (int i = 0; i < 9; i++) 
        {
            int x1 = rand() % 3, y1 = rand() % 3;
            int x2 = rand() % 3, y2 = rand() % 3;
            std::swap(arr[x1][y1], arr[x2][y2]);
        }
    } while (!isSolvable(arr));
}

bool moveTile(char arr[3][3], int& x, int& y, int dx, int dy) 
{
    int newX = x + dx;
    int newY = y + dy;

    if (newX >= 0 && newX < 3 && newY >= 0 && newY < 3) 
    {
        // Move the number into the empty space
        std::swap(arr[newX][newY], arr[x][y]);
        x = newX;
        y = newY;
        return true;
    }
    return false;
}

void printNeighbors(const char arr[3][3], int emptyX, int emptyY) 
{
    cout << "Existing operations:";
    // Check and print left
    if (emptyY > 0)
        cout << " Right: " << arr[emptyX][emptyY - 1] << "|";

    // Check and print right
    if (emptyY < 2)
        cout << " Left: " << arr[emptyX][emptyY + 1] << "|";

    // Check and print up
    if (emptyX > 0)
        cout << " Down: " << arr[emptyX - 1][emptyY] << "|";

    // Check and print down
    if (emptyX < 2)
        cout << " Up: " << arr[emptyX + 1][emptyY] << "|";
}

int main() {
    string numbers = "12345678 ";
    char start[3][3] = 
    {
        {numbers[0], numbers[1], numbers[2]},
        {numbers[3], numbers[4], numbers[5]},
        {numbers[6], numbers[7], numbers[8]}
    };

    const char goal1[3][3] = 
    {
        {numbers[0], numbers[1], numbers[2]},
        {numbers[3], numbers[4], numbers[5]},
        {numbers[6], numbers[7], numbers[8]}
    };

    const char goal2[3][3] = 
    {
        {numbers[7], numbers[6], numbers[5]},
        {numbers[4], numbers[3], numbers[2]},
        {numbers[1], numbers[0], numbers[8]}
    };

    shufflePuzzle(start);

    int emptyX = 0, emptyY = 0;

    // Find the initial empty space position
    for (int i = 0; i < 3; i++) 
    {
        for (int j = 0; j < 3; j++) 
        {
            if (start[i][j] == ' ') 
            {
                emptyX = i;
                emptyY = j;
            }
        }
    }

    cout << "Start state:\n";
    printTableWithLines(start);
    cout << "Use arrow keys to move (Esc to exit):\n";
    printNeighbors(start, emptyX, emptyY);

    char cOperator = 0;
    int control = 0;

    while (cOperator != 27) 
    {
        if (checkGoal(start, goal1) || checkGoal(start, goal2)) 
        {
            cout << "\nPuzzle solved! :) Total moves: " << control << "\n";
            break;
        }

        if (_kbhit()) 
        {
            cOperator = _getch();

            // Move number down into empty space (if the empty space is not in the last row)
            if (cOperator == 80 && emptyX > 0) 
            {
                cout << "\n\ndown array\n";
                std::swap(start[emptyX - 1][emptyY], start[emptyX][emptyY]);
                emptyX--;
                control++;
                cout << "Total moves: " << control << "\n";

                printNeighbors(start, emptyX, emptyY);
                cout << "\n";
                printTableWithLines(start);
            }
            // Move number up into empty space (if the empty space is not in the first row)
            else if (cOperator == 72 && emptyX < 2) 
            {
                cout << "\n\nup array\n";
                std::swap(start[emptyX + 1][emptyY], start[emptyX][emptyY]);
                emptyX++;
                control++;
                cout << "Total moves: " << control << "\n";

                printNeighbors(start, emptyX, emptyY);
                cout << "\n";
                printTableWithLines(start);
            }
            // Move number left into empty space (if the empty space is not in the first column)
            else if (cOperator == 75 && emptyY < 2) 
            {
                cout << "\n\nleft array\n";
                std::swap(start[emptyX][emptyY + 1], start[emptyX][emptyY]);
                emptyY++;
                control++;
                cout << "Total moves: " << control << "\n";

                printNeighbors(start, emptyX, emptyY);
                cout << "\n";
                printTableWithLines(start);
            }
            // Move number right into empty space (if the empty space is not in the last column)
            else if (cOperator == 77 && emptyY > 0) 
            {
                cout << "\n\nright array\n";
                std::swap(start[emptyX][emptyY - 1], start[emptyX][emptyY]);
                emptyY--;
                control++;
                cout << "Total moves: " << control << "\n";

                printNeighbors(start, emptyX, emptyY);
                cout << "\n";
                printTableWithLines(start);
            }
        }
    }
    cOperator = _getch();
    return 0;
}
