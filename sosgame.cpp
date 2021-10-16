#include <iostream>
#include <Windows.h> //in order to change console text color
using std::cout; using std::endl;

class Game
{
    public:
    char board[3][3] = {{'1','2','3'}, {'4','5','6'}, {'7','8','9'}}; //the number setup for starting position
    bool isStarted = false; //keep track of whether or not the players start the game
    bool isMarked[9] = {false,false,false,false,false,false,false,false,false}; //if any element of board is already changed, it cant be changed anymore(like X cant be O)
    int currentPlayer = 1;
    int condition = 0; // if nobody win the game. we will print 'draw' if condition >= 9
    std::string win = "";
    void winner(int& currentPlayer) 
    {
        char winner = currentPlayer == 1 ? 'O' : 'X'; //if any of if statements are true, it means we achieve the win status,
                                                      //'win' will be set to X or O, otherwise 'win' will stay as deafult value.
                                                      //if win is changed it means someone won the game. 
        if(board[0][0] == board[1][0] && board[0][0] == board[2][0])
        win = winner;

        if(board[0][1] == board[1][1] && board[0][1] == board[2][1])
        win = winner;

        if(board[0][2] == board[1][2] && board[0][2] == board[2][2])
        win = winner;

        if(board[0][0] == board[0][1] && board[0][0] == board[0][2])
        win = winner;

        if(board[1][0] == board[1][1] && board[1][0] == board[1][2]) 
        win = winner;

        if(board[2][0] == board[2][1] && board[2][0] == board[2][2])
        win = winner;

        if(board[0][0] == board[1][1] && board[0][0] == board[2][2])
        win = winner;

        if(board[0][2] == board[1][1] && board[0][2] == board[2][0])
        win = winner;
        
    }
    
    void StartTheGame() 
    {
        char a;
        std::cin >> a;
        if(a == 'Y' || a == 'y')
        {
            isStarted = true;
        }
    }
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    void howToPlay() //super explanatory screen that explain how to play
    {
        SetConsoleTextAttribute(hConsole, 30);
        cout << "<---------how to play the game--------->\n";
        cout << "you can either select 'X' or 'O'. \n";
        cout << "after that there are 9 choices for \nstarting player. The numbers between \n1-9 acceptable for game." ;
        cout << " Type either 'Y' or 'y' to start...";
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
        for(int i = 0; i < 3; i++)
        {
            cout <<  "\n\t\t\t    ------------------------"<<endl;
            cout << "\t\t\t\t" ;
            
            for(int j = 0; j < 3; j++)
            {
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                cout << board[i][j];
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                if(j < 2) { cout << "   |   "; }    
            }
            cout <<  "\n\t\t\t    ------------------------"<<endl;
        }
    }
    void Play()
    {
            int index;
            std::string player = currentPlayer == 1 ? "Player 1 (X)" : "Player 2 (O)";
            cout << "\n" << player << " choose a number (1-9): ";
            std::cin >> index;
            if(index > 0 && index < 10)
            {
            Update(currentPlayer, index, isMarked[index - 1]);
            }
            else //index should be between 1-9...
            {
                while(true)
                {
                    cout << "wrong number... type 1-9: \n";
                    std::cin >> index;
                    if( (index > 0 && index < 10) && !isMarked[index - 1])
                    {
                        break;
                    }
                }    
                Update(currentPlayer, index,isMarked[index - 1]);
            }    
    }
    void DrawBoard()
    {
        system("cls"); //refresh screen after each update
        winner(currentPlayer); //determine whether or not someone win the game
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
        cout <<" \n\t\t\t    the game has started \n\n";
        for(int j = 0; j < 3; j++) //simple loops for drawing board
        {
            cout <<  "\n\t\t\t    ------------------------"<<endl;
            cout << "\t\t\t\t" ;
            
            for(int i = 0; i < 3; i++)
            {
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                cout << board[j][i];
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                if(i < 2) { cout << "   |   "; }    
            }
            cout <<  "\n\t\t\t    ------------------------"<<endl;
        }
        if(win == "" && condition >= 9)
        {
            cout << "Game is over... Draw\npress anything to close";
            std::cin.get();
        }
        else if(win != "") //if there is a winner that means 'win' is set to X or O, its not an empty string
        {
            cout << "Congratulations.. " << win << " is the winner"<< "\npress anything to close";
            std::cin.get();
        }
        else
        {
            Play();
        }
            
    }
    void Update(int& currentPlayer, int& index, bool& marked)
    {
            ++condition; /////////
            int i , j;
            if (index <= 3)
            {
                j = index - 1;
                i = 0;
            }
            else if (index <= 6)
            {
                j = index - 4;
                i = 1;
            }
            else if(index <= 9)
            {
                j = index - 7;
                i = 2;
            }
            char c = currentPlayer == 1 ? 'X' : 'O';
            board[i][j] = c;
            currentPlayer = currentPlayer == 1 ? ++currentPlayer : --currentPlayer;
            isMarked[index - 1] = true;
            DrawBoard();
    }
};
    int main()
    {
        Game game;
        
        game.howToPlay();
        game.StartTheGame();

        if(game.isStarted)
        {
            game.DrawBoard();
        }
        std::cin.get();
    }