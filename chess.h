#ifndef CONSTANTS
#include "constants.h"
#endif

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#define CHESS_HEADER_CONSTANT

class chessPlayer;
class chessPiece;


class chessGame{
    private:
        bool isStarted;
        chessPlayer* players[2];//array of pointers pointing at chess players
                                //0 - white
                                //1 - black
        chessPiece*** globalChessboard; ////2d global chessboard array of chesspiece object pointers
        int** globalBoard;          //pointer to 2d array on which all pieces are saved
        int** WhiteMoveBoard; //pointer to 2d array on which moves of white and bindings are saved
        int** BlackMoveBoard;  //pointer to 2d array on which moves of black and possible new bindings are save
        chessPiece** WhiteKingsArray; //pointer to kings array for white pieces
        chessPiece** BlackKingsArray; //pointer to kings array for black pieces
        sf::Sprite* piecesSprites[64];
        const bool SFMLSupport[2];
        bool turn;
        friend class chessPlayer;
    protected:
        
    public:
        int processAll();
        chessGame(chessPlayer* whitePlayer, chessPlayer* blackPlayer, bool whiteSFMLProcessingSupport,
                    bool blackSFMLProcessingSupport, sf::Sprite** sprites);
        int start();
        int fieldClicked(sf::Vector2f mousePosition);
        int move();
        //~chessGame();   //to do
};

class chessPlayer{
    protected:
        chessGame* game;
        chessPiece*** globalChessboard; ////2d global chessboard array of chesspiece object pointers
        int** globalBoard;          //pointer to 2d array on which all pieces are saved
        int** friendGlobalMoveBoard; //pointer to 2d array on which ally moves and bindings are saved
        int** hostileGlobalMoveBoard;  //pointer to 2d array on which hostile moves and possible new bindings are saved
        int sideIdentifier;   //identifies on which side(black or white) object is playing
        int endTurn();      //all action necessarily needed for ending(switching) turn
        int checkFieldForFigure(sf::Vector2i attackedField);
        int makeMove(sf::Vector2i destinatedField, chessPiece* piece);
    public:
        int getSide() const;
        int getColour() const;
        chessPlayer();
        int initialize(chessGame* gamePointer, int** friendMoveBoard, int** hostileMoveBoard,
                            chessPiece*** globalChess, int** globalBoardd, int side);
        virtual int processMove(sf::Vector2i) = 0;
        //~chessPlayer();
};

class humanPlayer : public chessPlayer{
    private:
        sf::Vector2i fieldClicked;     //holds cordinates of last mouse click
        sf::VertexArray* pointerToCircles;  //pointer to "circle" array
        int** moveBoard;
        chessPiece* selectedPiece;      //currently selected piece
    public:
        humanPlayer(sf::VertexArray* circles);
        sf::Vector2i convertPosToInt(sf::Vector2f);
        int processMove(sf::Vector2i);
};

class chessPiece {
    private:
        chessPiece*** const globalChessboard;   //2d global chessboard array of chesspiece object pointers
        int** const globalBoard;         //pointer to 2d array on which all pieces are saved
        sf::Vector2i pos;                      //position of the piece on x axis and y axis
        bool binded;                    //bool value specifying if piece is hard-binded
        const int colour;               //colour value 1 = black 0 = white
        int moveCount;                 //movement counter  
    //protected:
        int** const friendGlobalMoveBoard; //pointer to 2d array on which ally moves and bindings are saved
        int** const hostileGlobalMoveBoard;  //pointer to 2d array on which hostile moves and possible new bindings are saved                   
        int* bindArray[8]; //2d array for for on which can move binded piece
        
    protected:
        chessPiece** const kings;    /*pointer to kings array 
                                        0 points to allied king 
                                            1 to hostile king*/
        bool attackWithoutMove(sf::Vector2i field);
        int movePiece(sf::Vector2i destination);
        int clearGlobalMoveBoards();
        int clearMoveBoard();
        chessPiece* getPiece(sf::Vector2i pos);
        int bind(chessPiece* piece) const;
        virtual int setCheck();
        virtual int setCheck(sf::Vector2i pos);
        virtual int unsetCheck();
        virtual int linearMovement(sf::Vector2i shift);
        int checkFieldForFigure(sf::Vector2i attackedField);
        bool possibleMove(sf::Vector2i designatedField);
        bool attackField(sf::Vector2i attackedField);
        bool setBindingOnField(sf::Vector2i designatedField);   //sets POSSIBLE_BINDING on field, marking the field as to be covered
    public:
        int* moveArray[8];  //2d array specifying valid fields to which piece can move
        int getMoveCount() const;
        chessPiece(int** global_moveBoard, int** hostileMoves, int** friendMoves,
                chessPiece*** global_Chessboard, chessPiece** kingsArray, int Xposition,
                int Yposition, int color);
        sf::Vector2i getPosition() const; 
        int getColour() const;
        bool isBinded() const;
        virtual int whatIs() const = 0;
        virtual int process() = 0;
        virtual int isCheck() const;
        friend int bindField(chessPiece* piece, sf::Vector2i field);
        friend class chessPlayer;
};

class pawn : public chessPiece{
    private:
        const int orientation;

    //private:
    public:
        pawn(int** global_MoveBoard, int** hostileMoves, int** friendMoves, chessPiece*** global_Chessboard,
            chessPiece** kingsArray, int Xposition, int Yposition, int color, int orientation);
        int whatIs() const;
        int process();

};

class rook : public chessPiece{
    private:
        const int side;        //variable defining on which side rook is 
                                    //0 - left
                                    //1 - right
                                    //2 - undefined
    public:
        rook(int** global_MoveBoard, int** hostileMoves, int** friendMoves, chessPiece*** global_Chessboard,
            chessPiece** kingsArray, int Xposition, int Yposition, int color);
        int whatIs() const;
        int process();

};

int bindField(chessPiece* piece, sf::Vector2i field);

//to do
class knight : public chessPiece{
    public:
        knight(int** global_MoveBoard, int** hostileMoves, int** friendMoves, chessPiece*** global_Chessboard,
                chessPiece** kingsArray, int Xposition, int Yposition, int color);
        int whatIs() const { return 0;};
        int process(){return 0;};
};

//to do
class bishop : public chessPiece{
    public:
        bishop(int** global_MoveBoard, int** hostileMoves, int** friendMoves, chessPiece*** global_Chessboard,
                chessPiece** kingsArray, int Xposition, int Yposition, int color);
        int whatIs() const { return 0;};
        int process(){return 0;};
};

//to do
class queen : public chessPiece{
    public:
        queen(int** global_MoveBoard, int** hostileMoves, int** friendMoves, chessPiece*** global_Chessboard,
                chessPiece** kingsArray, int Xposition, int Yposition, int color);
        int whatIs() const { return 0;};
        int process(){return 0;};
};

//in progress
class king : public chessPiece{
    private:
        int check;  //check counter 0 - no check, 1 - single check, 2 - double check
        sf::Vector2i checkingPiece;
        int possibleCastling(bool side);    //0 - long castle(left) 1 - short castle(right)
    public:
        king(int** global_MoveBoard, int** hostileMoves, int** friendMoves, chessPiece*** global_Chessboard,
                chessPiece** kingsArray, int Xposition, int Yposition, int color);
        int whatIs() const;
        int setCheck();
        int setCheck(sf::Vector2i checkingPiece);    //passes position from check is coming( used onli for pieces with linearmovement scheme)
        int unsetCheck();
        int process();
        sf::Vector2i getCheckingPiecePosition();    //returns checkingPiece
        int isCheck() const;
};