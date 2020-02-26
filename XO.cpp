#include <iostream>

struct table
{
    char label;
    bool used;
    table ()
        : label('+'), used(false) {}
};

struct player
{
    char Character, Chose;
    player(unsigned int& player)
        :Chose('Q')
    {
        std::cout << "Enter your character player" << player++%2 + 1 << ": ";
        std::cin >> Character;
    }
};

enum states {T,F,M};

void readyingBody(table B[7][7])
{
    for (int i = 1, Number = 49; i < 7; i += 2)
        for (int j = 1; j < 7; j += 2, Number++)
            B[i][j].label = Number;
}

bool labelCheck(table B[7][7])
{
    if ((B[1][1].label == B[1][3].label && B[1][3].label == B[1][5].label) || \
        (B[1][1].label == B[3][1].label && B[3][1].label == B[5][1].label) || \
        (B[1][1].label == B[3][3].label && B[3][3].label == B[5][5].label) || \
        (B[3][1].label == B[3][3].label && B[1][3].label == B[3][5].label) || \
        (B[5][1].label == B[5][3].label && B[5][3].label == B[5][5].label) || \
        (B[1][3].label == B[3][3].label && B[3][3].label == B[5][3].label) || \
        (B[1][5].label == B[3][5].label && B[3][5].label == B[5][5].label) || \
        (B[1][1].label == B[3][1].label && B[3][1].label == B[5][1].label) || \
        (B[1][5].label == B[3][3].label && B[3][3].label == B[3][1].label))
        return true;
    return false;
}

states settingChose(table B[7][7], const char& C, const char& Index)
{
    for (int i = 1; i < 7; i += 2)
        for (int j = 1; j < 7; j += 2)
            if (B[i][j].label == Index && !B[i][j].used)
            {
                B[i][j].label = C;
                B[i][j].used = true;
                return labelCheck(B) ? T : F;
            }
    return M;
}

std::ostream& operator<<(std::ostream& stream, const table B[7][7])
{
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j< 7; j++)
            stream << B[i][j].label << ' ';
        stream << std::endl;
    }
    return stream;
}

int main()
{
    table Body[7][7];
    readyingBody(Body);
    do
    {
        static unsigned int PlayerTurn = 0, FullTable = 9;
        static player Players[2](PlayerTurn);
        std::cout << Body;
        std::cout << "Player" << PlayerTurn%2 + 1 << " turn: ";
        std::cin >> Players[PlayerTurn%2].Chose;
        states Check = settingChose(Body, Players[PlayerTurn%2].Character, Players[PlayerTurn%2].Chose);
        FullTable--;
        if (Check == M)
        {
            std::cout << "Please try again.\n";
            continue;
        }
        if (FullTable == 0)
        {
            std::cout << "Tie!";
            return 0;
        }
        if (Check == T)
        {
            std::cout << Body;
            std::cout << "Player" << PlayerTurn%2 + 1 << " Wins!";
            return 0;
        }
        PlayerTurn++;
    }while (true);
}
