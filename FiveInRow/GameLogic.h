#pragma once

// cell condition
enum class CellState
{
    Empty,
    X,
    O
};

class Board
{
private:
    static const int SIZE = 15;
    CellState cells[SIZE][SIZE];

public:
    Board();

    void clear();
    bool isInside(int row, int col) const; // check if cell inside the board
    bool isEmpty(int row, int col) const; // check if cell empty
    bool setCell(int row, int col, CellState value); // place into cell X or O
    CellState getCell(int row, int col) const; // return cell's state
    bool isFull() const; //check if board the board is full
    int getSize() const;
};

class Game
{
private:
    Board board;
    CellState currentPlayer;
    bool gameOver;
    CellState winner;

    // how many identical characters appear in a row in the same direction
    int countDirection(int row, int col, int dRow, int dCol) const;  
    
    // check whether the player has won after moving into a square
    bool checkWin(int row, int col) const;
    void switchPlayer();

public:
    Game();

    void newGame();
    bool makeMove(int row, int col);

    CellState getCurrentPlayer() const;
    CellState getWinner() const;
    bool isGameOver() const;
    bool isDraw() const;

    const Board& getBoard() const;
};