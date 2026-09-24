#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
#include <string>

using namespace std;

class ChessPiece {
protected:
    int x, y;

public:
    // конструктор за замовчуванням
    ChessPiece() : x(0), y(0) {}
    // конструктор ініціалізації
    ChessPiece(int x, int y) : x(x), y(y) {}
    // деструктор
    virtual ~ChessPiece() {}

    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

    virtual bool canMoveEmptyBoard(int newX, int newY) const = 0;
    virtual string getName() const = 0;
};

class Rook : public ChessPiece {
public:
    Rook(int x, int y) : ChessPiece(x, y) {}

    bool canMoveEmptyBoard(int newX, int newY) const override {
        return (x == newX || y == newY) && !(x == newX && y == newY);
    }

    string getName() const override {
        return "Rook";
    }
};

class Bishop : public ChessPiece {
public:
    Bishop(int x, int y) : ChessPiece(x, y) {}

    bool canMoveEmptyBoard(int newX, int newY) const override {
        return abs(newX - x) == abs(newY - y) && !(x == newX && y == newY);
    }

    string getName() const override {
        return "Bishop";
    }
};

class Knight : public ChessPiece {
public:
    Knight(int x, int y) : ChessPiece(x, y) {}

    bool canMoveEmptyBoard(int newX, int newY) const override {
        int dx = abs(newX - x);
        int dy = abs(newY - y);

        return (dx == 2 && dy == 1) || (dx == 1 && dy == 2) && !(x == newX && y == newY);;
    }

    string getName() const override {
        return "Knight";
    }
};

class Queen : public ChessPiece {
public:
    Queen(int x, int y) : ChessPiece(x, y) {}

    bool canMoveEmptyBoard(int newX, int newY) const override {
        return ((x == newX || y == newY) ||
            abs(newX - x) == abs(newY - y)) &&
            !(x == newX && y == newY);
    }

    string getName() const override {
        return "Queen";
    }
};

class King : public ChessPiece {
public:
    King(int x, int y) : ChessPiece(x, y) {}

    bool canMoveEmptyBoard(int newX, int newY) const override {
        int dx = abs(newX - x);
        int dy = abs(newY - y);

        return dx <= 1 && dy <= 1 && !(dx == 0 && dy == 0);
    }

    string getName() const override {
        return "King";
    }
};

class Pawn : public ChessPiece {
public:
    Pawn(int x, int y) : ChessPiece(x, y) {}

    bool canMoveEmptyBoard(int newX, int newY) const override {
        return newX == x && newY == y + 1;
    }

    string getName() const override {
        return "Pawn";
    }
};

class ChessBoard {
private:
    vector<shared_ptr<ChessPiece>> pieces;

    bool isInsideBoard(int x, int y) const {
        return x >= 0 && x <= 7 && y >= 0 && y <= 7;
    }

    shared_ptr<ChessPiece> getPieceAt(int x, int y) const {
        for (const auto& piece : pieces) {
            if (piece->getX() == x && piece->getY() == y) {
                return piece;
            }
        }

        return nullptr;
    }

    bool isPathClear(const ChessPiece& piece, int toX, int toY) const {
        int fromX = piece.getX();
        int fromY = piece.getY();

        int dx = toX - fromX;
        int dy = toY - fromY;

        int stepX;
        if (dx > 0) stepX = 1;
        else if (dx < 0) stepX = -1;
        else stepX = 0;

        int stepY;
        if (dy > 0) stepY = 1;
        else if (dy < 0) stepY = -1;
        else stepY = 0;

        int currentX = fromX + stepX;
        int currentY = fromY + stepY;

        while (currentX != toX || currentY != toY) {
            if (getPieceAt(currentX, currentY) != nullptr) {
                return false;
            }

            currentX += stepX;
            currentY += stepY;
        }

        return true;
    }

public:
    ChessBoard() {}

    void addPiece(shared_ptr<ChessPiece> piece) {
        if (!isInsideBoard(piece->getX(), piece->getY())) {
            cout << "Position is outside the board." << endl;
            return;
        }

        if (getPieceAt(piece->getX(), piece->getY()) != nullptr) {
            cout << "This cell is already occupied." << endl;
            return;
        }

        pieces.push_back(piece);
    }

    bool canMoveOnFilledBoard(int fromX, int fromY, int toX, int toY) const {
        // якщо за межами дошки
        if (!isInsideBoard(fromX, fromY) || !isInsideBoard(toX, toY)) {
            return false;
        }

        shared_ptr<ChessPiece> piece = getPieceAt(fromX, fromY);

        if (piece == nullptr) {
            return false;
        }
        // якщо кінцева клітинка зайнята
        if (getPieceAt(toX, toY) != nullptr) {
            return false;
        }

        if (!piece->canMoveEmptyBoard(toX, toY)) {
            return false;
        }

        string name = piece->getName();

        if (name == "Rook" || name == "Bishop" || name == "Queen") {
            return isPathClear(*piece, toX, toY);
        }

        return true;
    }

    void printBoard() const {
        cout << "Pieces on board:" << endl;

        for (const auto& piece : pieces) {
            cout << piece->getName() << " at (" << piece->getX()
                << ", " << piece->getY() << ")" << endl;
        }
    }
};

int main() {
    ChessBoard board;

    board.addPiece(make_shared<Rook>(0, 0));
    board.addPiece(make_shared<Bishop>(2, 0));
    board.addPiece(make_shared<Knight>(1, 0));
    board.addPiece(make_shared<Queen>(3, 3));
    board.addPiece(make_shared<King>(7, 7));
    board.addPiece(make_shared<Pawn>(4, 1));

    board.printBoard();

    cout << endl;

    cout << "Rook from (0,0) to (0,5): "
        << (board.canMoveOnFilledBoard(0, 0, 5, 0) ? "Allowed" : "Not allowed") << endl;

    cout << "Bishop from (2,0) to (5,3): "
        << (board.canMoveOnFilledBoard(2, 0, 5, 3) ? "Allowed" : "Not allowed") << endl;

    cout << "Knight from (1,0) to (2,2): "
        << (board.canMoveOnFilledBoard(1, 0, 2, 2) ? "Allowed" : "Not allowed") << endl;

    cout << "Queen from (3,3) to (0,0): "
        << (board.canMoveOnFilledBoard(3, 3, 0, 0) ? "Allowed" : "Not allowed") << endl;

    cout << "King from (7,7) to (6,6): "
        << (board.canMoveOnFilledBoard(7, 7, 6, 6) ? "Allowed" : "Not allowed") << endl;

    cout << "Pawn from (4,1) to (4,2): "
        << (board.canMoveOnFilledBoard(4, 1, 4, 2) ? "Allowed" : "Not allowed") << endl;

    return 0;
}