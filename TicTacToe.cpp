#include <iostream>
#include <cstdlib> // для system()
#include <ctime> // для srand()
using namespace std;

char board[3][3] = { {'-', '-', '-'}, {'-', '-', '-'}, {'-', '-', '-'} };
char player1 = 'X';
char player2 = 'O';
int moves = 0;

// Отображение поля
void display_board() 
{
    cout << "   0  1  2\n";
    for (int i = 0; i < 3; i++) 
    {
        cout << i << " ";
        for (int j = 0; j < 3; j++) 
        {
            cout << "[" << board[i][j] << "]";
        }
        cout << "\n";
    }
}

// Очищение поля
void clear_board() 
{
    for (int i = 0; i < 3; i++) 
    {
        for (int j = 0; j < 3; j++) 
        {
            board[i][j] = '-';
        }
    }
}

// Очищение консоли
void clear_console() 
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Проверка допустимости хода
bool is_valid_move(int row, int col) 
{
    if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == '-') 
    {
        return true;
    }
    else 
    {
        return false;
    }
}

// Проверка наличия победителя
bool check_win(char player) 
{
    for (int i = 0; i < 3; i++) 
    {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) 
        {
            return true;
        }
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) 
        {
            return true;
        }
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) 
    {
        return true;
    }
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) 
    {
        return true;
    }
    return false;
}

// Игрок против игрока
void playerVSplayer(char player)
{
    int row, col;
    bool valid_move;
    while (moves < 9)
    {
        valid_move = false;
        while (!valid_move)
        {
            cout << "Игрок " << player << ", введите строку и столбец для вашего хода: ";
            cin >> row >> col;
            if (is_valid_move(row, col))
            {
                valid_move = true;
            }
            else
            {
                cout << "Неверный ход, попробуйте ещё раз.\n";
            }
        }
        board[row][col] = player;
        display_board();
        if (check_win(player))
        {
            cout << "Игрок " << player << " победил!\n";
            return;
        }
        player = (player == player1) ? player2 : player1;
        moves++;
    }
    cout << "Это ничья!\n";
}

// Игрок против компьютера
void playerVScomputer(char player)
{
    srand(time(NULL));
    int row, col;
    bool valid_move;
    while (moves < 9)
    {
        valid_move = false;
        if (moves % 2 == 0)
        { 
            while (!valid_move)
            {
                cout << "Игрок " << player << ", введите строку и столбец для вашего хода: ";
                cin >> row >> col;
                if (is_valid_move(row, col))
                {
                    valid_move = true;
                }
                else
                {
                    cout << "Неверный ход, попробуйте ещё раз.\n";
                }
            }
            board[row][col] = player;
            display_board();
            if (check_win(player))
            {
                cout << "Игрок " << player << " победил!\n";
                return;
            }
            player = (player == player1) ? player2 : player1;
        }
        else
        {
            while (!valid_move)
            {
                row = rand() % 3;
                col = rand() % 3;
                if (is_valid_move(row, col))
                {
                    valid_move = true;
                }
            }
            board[row][col] = player;
            cout << "Компьютер сделал ход: " << row << " " << col << endl;
            display_board();
            if (check_win(player))
            {
                cout << "Компьютер победил!\n";
                return;
            }
            player = (player == player1) ? player2 : player1;
        }
        moves++;
    }
    cout << "Это ничья!\n";
}

// Компьютер против компьютера
void computerVScomputer(char player)
{
    srand(time(NULL));
    int row, col;
    bool valid_move;
    while (moves < 9)
    {
        valid_move = false;
        while (!valid_move)
        {
            row = rand() % 3;
            col = rand() % 3;
            if (is_valid_move(row, col))
            {
                valid_move = true;
            }
        }
        board[row][col] = player;
        cout << "Компьютер " << player << " сделал ход: " << row << " " << col << endl;
        display_board();
        if (check_win(player))
        {
            cout << "Компьютер " << player << " победил!\n";
            return;
        }
        player = (player == player1) ? player2 : player1;
        moves++;
    }
    cout << "Это ничья!\n";
}

// Основная функция игры
void play_game(int game_mode) 
{
    if (game_mode == 1) 
    {
        int player_player;
        cout << "Выберите сторону (1 - 'X', 2 - 'O'): ";
        cin >> player_player;
        if (player_player == 1) 
        {
            playerVSplayer(player1);
        }
        else if (player_player == 2) 
        {
            playerVSplayer(player2);
        }
        else {
            cout << "Некорректный ввод. Завершение игры.\n";
        }
    }
    else if (game_mode == 2) 
    {
        int computer_computer;
        cout << "Выберите сторону (1 - 'X', 2 - 'O'): ";
        cin >> computer_computer;
        if (computer_computer == 1) 
        {
            playerVScomputer(player1);
        }
        else if (computer_computer == 2) 
        {
            playerVScomputer(player2);
        }
        else 
        {
            cout << "Некорректный ввод. Завершение игры.\n";
        }
    }
    else if (game_mode == 3) 
    {
        int computer_player;
        cout << "Выберите сторону (1 - 'X', 2 - 'O'): ";
        cin >> computer_player;
        if (computer_player == 1) 
        {
            computerVScomputer(player1);
        }
        else if (computer_player == 2) 
        {
            computerVScomputer(player2);
        }
        else 
        {
            cout << "Некорректный ввод. Завершение игры.\n";
        }
    }
    else 
    {
        cout << "Некорректный ввод. Завершение игры.\n";
    }
}

int main() 
{
    setlocale(LC_ALL, "Russian");
    while (true) 
    {
        cout << "Игра крестики-нолики\n";
        clear_board();
        display_board();
        int game_mode;
        cout << "Выберите режим игры:\n";
        cout << "1 - Игрок против игрока\n";
        cout << "2 - Игрок против компьютера\n";
        cout << "3 - Компьютер против компьютера\n";
        cin >> game_mode;
        play_game(game_mode);
        char choice;
        cout << "Хотите сыграть ещё раз? (y/n) ";
        cin >> choice;
        if (choice != 'y') 
        {
            break;
        }
        clear_console();
        moves = 0;
    }
    return 0;
}