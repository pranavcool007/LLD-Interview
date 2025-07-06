#include <bits/stdc++.h>
using namespace std;

class Player{
private:
    string name;
    char symbol;

public:
    Player(string name, char symbol) : name(name), symbol(symbol) {} ;

    string getName(){
        return name;
    }
    char getSymbol(){
        return symbol;
    }
};

class Board{
private:
    vector<vector<char>> grid;
    const int n = 3;
    int countMoves;

public:
    Board(){
        grid = vector<vector<char>>(n, vector<char>(n, '-'));
        countMoves = 0;
    }
    
    void displayBoard(){
        for(int i=0; i<n; ++i){
            for(int j=0; j<n; ++j){
                cout<<grid[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
    }

    bool isFull() {
        if(countMoves == n*n){
            return true;
        }
        return false;
    }

    bool isWin(char symbol) {
        // check vertically horizontally and diagonally all 3 shd be same

        //row wise
        for(int i=0; i<n; ++i){
            if(grid[i][0] == symbol && grid[i][1] == symbol && grid[i][2] == symbol){
                return true;
            }
        }
        // column wise
        for(int j=0; j<n; ++j){
            if(grid[0][j] == symbol && grid[1][j] == symbol && grid[2][j] == symbol){
                return true;
            }
        }
        // diagnol
        if(grid[0][0] == symbol && grid[1][1] == symbol && grid[2][2] == symbol){
            return true;
        }
        // anti diagnol
        if(grid[0][2] == symbol && grid[1][1] == symbol && grid[2][0] == symbol){
            return true;
        } 

        return false;
    }

    bool isValidMove(int row, int col, char symbol) {
        if(row < 0 || row >= n || col < 0 || col >= n || grid[row][col] != '-'){
            return false;
        }
        return true;
    }

    bool makeMove(int row, int col, Player &p1) {     // only move when its -
        char symbol = p1.getSymbol();
        if(!isValidMove(row,col,symbol)){
            cout<<"InValid Move "<<endl;
            return false;
        }
        grid[row][col] = p1.getSymbol();
        ++countMoves;
        return true;
    }
};

class Game{
private:
    Player p1;
    Player p2;
    Board board;
    Player &currPlayer;

public:
    Game(Player p1, Player p2, Board board, Player &player) : p1(p1), p2(p2), board(board), currPlayer(player) {};

    void play() {   // alternate turns 
        while(true){
            board.displayBoard();
            cout<<"Player : "<<currPlayer.getName()<<"\tMake your move "<<endl;
            int row, col;
            cin>>row>>col;
            if(!board.makeMove(row,col,currPlayer)){
                continue;
            }
            if(board.isWin(currPlayer.getSymbol()) || board.isFull()){
                break;
            }

            // switch the players
            currPlayer = currPlayer.getName() == p1.getName() ? p2 : p1;
        }

        if(board.isWin(currPlayer.getSymbol())){
            cout<<"Player : "<<currPlayer.getName()<<" Won!! "<<endl;
            board.displayBoard();
            return;
        }
        if(board.isFull()){
            cout<<"Game ended in a Draw!! "<<endl;
            board.displayBoard();
        }
    }
};
int main()
{
    Player p1("P1", 'X');
    Player p2("P2", 'O');
    Board board;
    Game game(p1,p2,board,p1);
    game.play();
    return 0;
}