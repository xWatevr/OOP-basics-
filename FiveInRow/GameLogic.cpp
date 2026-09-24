#include "GameLogic.h"

Board::Board()
{
    clear();
}

void Board::clear()
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            cells[i][j] = CellState::Empty;
        }
    }
}

bool Board::isInside(int row, int col) const
{
    return row >= 0 && row < SIZE && col >= 0 && col < SIZE;
}

bool Board::isEmpty(int row, int col) const
{
    return isInside(row, col) && cells[row][col] == CellState::Empty;
}

bool Board::setCell(int row, int col, CellState value)
{
    if (!isEmpty(row, col))
    {
        return false;
    }

    cells[row][col] = value;
    return true;
}

CellState Board::getCell(int row, int col) const
{
    if (!isInside(row, col))
    {
        return CellState::Empty;
    }

    return cells[row][col];
}

bool Board::isFull() const
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (cells[i][j] == CellState::Empty)
            {
                return false;
            }
        }
    }

    return true;
}

int Board::getSize() const
{
    return SIZE;
}

// ---------------- Game ----------------

Game::Game()
{
    newGame();
}

void Game::newGame()
{
    board.clear();
    currentPlayer = CellState::X;
    gameOver = false;
    winner = CellState::Empty;
}

bool Game::makeMove(int row, int col)
{
    if (gameOver)
    {
        return false;
    }

    if (!board.setCell(row, col, currentPlayer))
    {
        return false;
    }

    if (checkWin(row, col))
    {
        gameOver = true;
        winner = currentPlayer;
    }
    else if (board.isFull())
    {
        gameOver = true;
        winner = CellState::Empty;
    }
    else
    {
        switchPlayer();
    }

    return true;
}

void Game::switchPlayer()
{
    if (currentPlayer == CellState::X)
    {
        currentPlayer = CellState::O;
    }
    else
    {
        currentPlayer = CellState::X;
    }
}

int Game::countDirection(int row, int col, int dRow, int dCol) const
{
    CellState player = board.getCell(row, col);

    int count = 0;
    int r = row + dRow;
    int c = col + dCol;

    while (board.isInside(r, c) && board.getCell(r, c) == player)
    {
        count++;
        r += dRow;
        c += dCol;
    }

    return count;
}

bool Game::checkWin(int row, int col) const
{
    int horizontal = 1 + countDirection(row, col, 1, 0) + countDirection(row, col, -1, 0);
    int vertical = 1 + countDirection(row, col, 0, 1) + countDirection(row, col, 0, -1);
    int diagonal1 = 1 + countDirection(row, col, 1, 1) + countDirection(row, col, -1, -1);
    int diagonal2 = 1 + countDirection(row, col, 1, -1) + countDirection(row, col, -1, 1);

    return horizontal >= 5 || vertical >= 5 || diagonal1 >= 5 || diagonal2 >= 5;
}

CellState Game::getCurrentPlayer() const
{
    return currentPlayer;
}

CellState Game::getWinner() const
{
    return winner;
}

bool Game::isGameOver() const
{
    return gameOver;
}

bool Game::isDraw() const
{
    return gameOver && winner == CellState::Empty;
}

const Board& Game::getBoard() const
{
    return board;
}