#include<iostream>
#include<string>
using namespace std;

void greetAndInstruct(); //Q1
void displayBoard(char board[]); //Q2
bool checkIfLegal(int cellNbre, char board[]); //Q3
bool checkWinner(char board[]); //Q3
void computerMove(char board[]); //Q4

char board[27];
string num[27] ={"1","2","3","10","11","12","19","20","21","4","5","6","13","14","15","22","23","24","7","8","9","16","17","18","25","26","27"};
char XorY; //used to store winner
bool tie;

int main() //Q5
{
    //initilize a new game
    greetAndInstruct();
    cout << "\n\nThe game has started";
    int move;
    tie = false;
    bool winner = false;

    //run until game ends (someone wins, tie happens, or illegal move played)
    while(true)
    {
        //player's turn
        cout << "\nHere is the copy of the current board:\n";
        displayBoard(board);
        cout << "\n\nPick a number to place an X:\n";
        cin >> move;
        bool canPlay = checkIfLegal(move, board); //1 is true, 0 is false
        if(canPlay == 0)
        {
            cout << "\nIllegal moves are against the rules. Game over :(";
            break;
        }
        //find place to put move
        int loc=0;
        for(int i = 0; i < 27; i ++)
        {
            if(num[i]==to_string(move)) //to string
            {
                loc=i;
                break;
            }
        }
        board[loc]='X';
        num[loc]="0";
        winner = checkWinner(board);
        if(winner == 1)
        {
            if(XorY=='X')
            {
                cout <<"\nPlayer has won\n";
                displayBoard(board);
            }
            else
            {
                cout <<"\nComputer has won\n";
                displayBoard(board);
            }
            cout << "Once someone wins the game is over!\n";
            break;
        }
        if(tie)
        {
            cout << "\nTie Game.";
            break;
        }

        //computer's turn
        computerMove(board);
        cout << "\nThe computer has taken its turn";
        winner = checkWinner(board);
        if(winner == 1)
        {
            if(XorY=='X')
            {
                cout <<"\nPlayer has won\n";
                displayBoard(board);
            }
            else
            {
                cout <<"\nComputer has won\n";
                displayBoard(board);
            }
            cout << "Once someone wins the game is over!\n";
            break;
        }
        if(tie)
        {
            cout << "\nTie Game.";
            break;
        }
    }
    exit(0);
}

void greetAndInstruct()
{
    cout << "Hello and welcome to Tic-Tac-Toe challenge: Player against Compuetr." << endl;
    cout << "The board is numbered from 1 to 27 as per the following:\n";
    cout << "1|2|3\t10|11|12\t19|20|21\n";
    cout << "-----\t---------\t---------\n";
    cout << "4|5|6\t13|14|15\t22|23|24\n";
    cout << "-----\t---------\t---------\n";
    cout << "7|8|9\t16|17|18\t25|26|27\n";
    cout << "\nPlayer starts first. Simply input the number of the cell you want to occupy. Player's move is marked with X. Computer's move is marked with O.\n";
    cout << "Start?(y/n""): ";
    
    string start ="";
    cin >> start;
    if(start=="n")
    {
        exit(0); //program exits
    }
    //otherwise program continues and game starts
}

void displayBoard(char board[])
{
    cout <<endl; //clear line for display
    
    int pos=0;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<9;j++)
        {
            if(board[pos]==0)
            {
                //no moved is played there yet, so display number
                cout<<num[pos];
            }
            else
            {
                //move is played so display character (X or O)
                cout<<board[pos];
            }
            pos++;
            
            if((j+1)%3==0)
            {
                cout<<"\t";
            }
            else
            {
                cout<<"|";
            }
            
        }
        if(i!=2)
        {
            cout << "\n------\t---------\t---------\n";
        }
    }
}

bool checkIfLegal(int cellNbre, char board[])
{
    if(cellNbre > 27 || cellNbre < 0)
    {
        cout << "\nIllegal move, not a real position";
        return false;
    }
    if(board[cellNbre-1] !=0)
    {
        cout << "\nIllegal move, player already went there";
        return false; //character already there
    }
    return true;
}

bool checkWinner(char board[])
{
    int x = 0;
    //checks if there is a 3 in a row for rows
    for(int i=0; i<25;i+=3)
    {
        if(board[i]==board[i+1] && board[i+1]==board[i+2] && board[i] != 0)
        {
            XorY=board[i];
            break;
        }
    }
    while(x<19)
    {
        if(board[0+x]==board[4+x] && board[4+x]==board[8+x] && board[x] != 0)
        {
            XorY=board[x];
            break;
        }
        x+=9;
    }
    
    //checks for columns
    for(int i=0;i<9;i++)
    {
        if(board[i]==board[i+9] && board[i+9]==board[i+18] && board[i] != 0)
        {
            XorY=board[i];
            break;
        }
    }
    x=0;
    while(x<3)
    {
        if(board[x]==board[x+12] && board[x+12]==board[x+24] && board[x] != 0)
        {
            XorY=board[x];
            break; 
        }
        x++;
    }
    
    //checks for diagonals
    for(int i=0;i<7;i+=3)
    {
        if(board[i]==board[i+10] && board[i+10]==board[i+20] && board[i] != 0)
        {
            XorY=board[i];
            break;
        }
    }
    for(int i=2; i<9;i+=3)
    {
        if(board[i]==board[i+8] && board[i+8]==board[i+16] && board[i] != 0)
        {
            XorY=board[i];
            break;
        }
    }
    if(board[0]==board[13]&&board[13]==board[26] && board[0] != 0)
    {
        XorY=board[0];
    }
    if(board[8]==board[13]&&board[13]==board[18] && board[8] != 0)
    {
        XorY=board[8];
    }
    
    //check if in same cell across all tables
    for(int i=0;i<21;i++)
    {
        if(board[i]==board[i+3] && board[i+3]==board[i+6] && board[i] != 0)
        {
            XorY=board[i];
            break;
        }
    }
    
    //if no winner, check if board is full, then declare tie if yes
    bool full=true;
    for(int i = 0; i <27; i ++)
    {
        if(board[i]==0)
        {
            full=false;
        }
    }
    
    //result
    if(XorY=='X' || XorY =='O')
    {
        return true;
    }
    else if(full)
    {
        tie=true;
        return false;
    }
    else
    {
        return false;
    }
}

void computerMove(char board[])
{
    bool checkedWin;
    for(int i=0;i<27;i++)
    {
        if(board[i]!='X' && board[i] != 'O')
        {
            //see if computer can win
            board[i]='O';
            checkedWin=checkWinner(board);
            if(checkedWin)
            {
                XorY='\0';
                tie=false;
                return;
            }
            XorY='\0';
            tie=false;

            //see if player can win and block
            board[i]='X';
            checkedWin=checkWinner(board);
            if(checkedWin)
            {
                board[i]='O'; //blocked player
                XorY='\0';
                tie=false;
                return;
            }
            board[i]='\0'; //reset if don't use
        }
    }
        
        //else play random
    for(int i=0;i<27;i++)
    {
        if(board[i]==0)
        {
            board[i]='O';
            return;
        }
    }
}