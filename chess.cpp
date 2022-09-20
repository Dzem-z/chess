

#ifndef CONSTANTS
#include "constants.h"
#endif

#ifndef CHESS_HEADER_CONSTANT
#include "chess.h"
#endif
extern int s;
extern int cir_a;
extern void ShowCircles(sf::VertexArray*, int, bool);
extern void HideAllCircles(sf::VertexArray*, int);
extern void MoveSprite(int, int, sf::Sprite**);
extern void ShowSprite(sf::Sprite*, bool);

int XYtoNumerical(sf::Vector2i);
void ellipsis(){}

chessGame::chessGame(chessPlayer* whitePlayer,  //pointer to instance representing white player
                    chessPlayer* blackPlayer,   //pointer to instance representing black player
                    bool whiteSFMLProcessingSupport,    //determines if player should be processed
                                                    //with SFML event interface(true for yes)
                    bool blackSFMLProcessingSupport,
                    sf::Sprite** sprites          //array of pointers to pieces' sprites
                                                    //index represents cordinate in notation
                                                    //i = 8 * y + x //i- index x,y cordinates
                    ) : SFMLSupport{whiteSFMLProcessingSupport, blackSFMLProcessingSupport} {
    isStarted = false;
    players[ WHITE_TURN_I ] = whitePlayer;
    players[ BLACK_TURN_I ] = blackPlayer;
    for(int i = 0; i < 64; i++)
        piecesSprites[ i ] = sprites[ i ];

    //global board declaration

    globalBoard = new int*[ 8 ];
    for(int i = 0; i < 8; i++){
        globalBoard[ i ] = new int[ 8 ];
        for(int j = 0; j < 8; j++)
            globalBoard[ i ][ j ] = FREE;
    }
    //globalBoard piece initialization

    globalBoard[ 0 ][ 0 ] = WHITE_ROOK;
    globalBoard[ 7 ][ 0 ] = WHITE_ROOK;
    globalBoard[ 4 ][ 0 ] = WHITE_KING;

    for(int i = 0; i < 8; i++)
        globalBoard[ i ][ 1 ] = WHITE_PAWN;
    
    for(int i = 0; i < 8; i++)
        globalBoard[ i ][ 6 ] = BLACK_PAWN;

    globalBoard[ 7 ][ 7 ] = BLACK_ROOK;
    globalBoard[ 0 ][ 7 ] = BLACK_ROOK;
    globalBoard[ 4 ][ 7 ] = BLACK_KING;
    //end

    WhiteKingsArray = new chessPiece*[ 2 ];
    BlackKingsArray = new chessPiece*[ 2 ];
   

    //movement Boards declaration and initialization

    WhiteMoveBoard = new int*[ 8 ];
    BlackMoveBoard = new int*[ 8 ];
    for(int i = 0; i < 8; i++){
        WhiteMoveBoard[ i ] = new int[ 8 ];
        BlackMoveBoard[ i ] = new int[ 8 ];
        for(int j = 0; j < 8; j++)
            BlackMoveBoard[ i ][ j ] = WhiteMoveBoard[ i ][ j ] = FREE_FIELD;
    }

    //globalchessboard declaration

    globalChessboard = new chessPiece**[ 8 ];
    for(int i = 0; i < 8; i++){
        globalChessboard[ i ] = new chessPiece*[ 8 ];
        for(int j = 0; j < 8; j++)
            globalChessboard[ i ][ j ] = nullptr;
    }
   
    //globalChessboard initialization

    globalChessboard[ 0 ][ 0 ] = new rook(globalBoard, BlackMoveBoard, WhiteMoveBoard, globalChessboard,
                                                WhiteKingsArray, 0, 0, WHITE);
    globalChessboard[ 1 ][ 0 ] = new knight(globalBoard, BlackMoveBoard, WhiteMoveBoard, globalChessboard,
                                                WhiteKingsArray, 1, 0, WHITE);
    globalChessboard[ 2 ][ 0 ] = new bishop(globalBoard, BlackMoveBoard, WhiteMoveBoard, globalChessboard,
                                                WhiteKingsArray, 2, 0, WHITE);
    globalChessboard[ 3 ][ 0 ] = new queen(globalBoard, BlackMoveBoard, WhiteMoveBoard, globalChessboard,
                                                WhiteKingsArray, 3, 0, WHITE);
    globalChessboard[ 4 ][ 0 ] = new king(globalBoard, BlackMoveBoard, WhiteMoveBoard, globalChessboard,
                                                WhiteKingsArray, 4, 0, WHITE);
    globalChessboard[ 5 ][ 0 ] = new bishop(globalBoard, BlackMoveBoard, WhiteMoveBoard, globalChessboard,
                                                WhiteKingsArray, 5, 0, WHITE);
    globalChessboard[ 6 ][ 0 ] = new knight(globalBoard, BlackMoveBoard, WhiteMoveBoard, globalChessboard,
                                                WhiteKingsArray, 6, 0, WHITE);
    globalChessboard[ 7 ][ 0 ] = new rook(globalBoard, BlackMoveBoard, WhiteMoveBoard, globalChessboard,
                                                WhiteKingsArray, 7, 0, WHITE);
    for(int i = 0; i < 8; i++)
        globalChessboard[ i ][ 1 ] = new pawn(globalBoard, BlackMoveBoard, WhiteMoveBoard, globalChessboard,
                                                WhiteKingsArray, i, 1, WHITE, UPSIDE_DOWN);
    for(int i = 0; i < 8; i++)
        globalChessboard[ i ][ 6 ] =  new pawn(globalBoard, WhiteMoveBoard, BlackMoveBoard, globalChessboard,
                                                BlackKingsArray, i, 6, BLACK, NORMAL_ORIENTATION);

    globalChessboard[ 0 ][ 7 ] = new rook(globalBoard, WhiteMoveBoard, BlackMoveBoard, globalChessboard,
                                                BlackKingsArray, 0, 7, BLACK);
    globalChessboard[ 1 ][ 7 ] = new knight(globalBoard, WhiteMoveBoard, BlackMoveBoard, globalChessboard,
                                                BlackKingsArray, 1, 7, BLACK);
    globalChessboard[ 2 ][ 7 ] = new bishop(globalBoard, WhiteMoveBoard, BlackMoveBoard, globalChessboard,
                                                BlackKingsArray, 2, 7, BLACK);
    globalChessboard[ 3 ][ 7 ] = new queen(globalBoard, WhiteMoveBoard, BlackMoveBoard, globalChessboard,
                                                BlackKingsArray, 3, 7, BLACK);
    globalChessboard[ 4 ][ 7 ] = new king(globalBoard, WhiteMoveBoard, BlackMoveBoard, globalChessboard,
                                                BlackKingsArray, 4, 7, BLACK);
    globalChessboard[ 5 ][ 7 ] = new bishop(globalBoard, WhiteMoveBoard, BlackMoveBoard, globalChessboard,
                                                BlackKingsArray, 5, 7, BLACK);
    globalChessboard[ 6 ][ 7 ] = new knight(globalBoard, WhiteMoveBoard, BlackMoveBoard, globalChessboard,
                                                BlackKingsArray, 6, 7, BLACK);
    globalChessboard[ 7 ][ 7 ] = new rook(globalBoard, WhiteMoveBoard, BlackMoveBoard, globalChessboard,
                                                BlackKingsArray, 7, 7, BLACK);                
    //players initialization

    WhiteKingsArray[ 0 ] = BlackKingsArray[ 1 ] = globalChessboard[ 4 ][ 0 ];
    BlackKingsArray[ 0 ] = WhiteKingsArray[ 1 ] = globalChessboard[ 4 ][ 7 ];

    for(int x = 0; x < 8; x++){
        for(int y = 0; y < 8; y++){
            if( globalBoard[ x ][ y ] > FREE)
                ShowSprite(sprites[ XYtoNumerical(sf::Vector2i(x, y)) ], SHOW);
        }
    }


    players[ WHITE_TURN_I ]->initialize(this, WhiteMoveBoard, BlackMoveBoard, globalChessboard, globalBoard, WHITE_TURN_I);
    players[ BLACK_TURN_I ]->initialize(this, BlackMoveBoard, WhiteMoveBoard, globalChessboard, globalBoard, BLACK_TURN_I);
}

int chessGame::start(){ //starts the game with white move
    turn = WHITE_TURN_I;
    isStarted = true;
    processAll(1);
    if( !SFMLSupport[ turn ])
        turn = players[ WHITE_TURN_I ]->processMove(sf::Vector2i(-1,-1));   //blank value
    return turn != WHITE_TURN_I;
}

int chessGame::fieldClicked(sf::Vector2f mousePosition  //position of mouse when field was clicked
                            ){
    //if game not started, abort
    if(!isStarted)
        throw("game not started");
    if( SFMLSupport[ turn ]){
        turn = players[ turn ]->processMove(((humanPlayer*)players[ turn ])->convertPosToInt(mousePosition));
        return 1;
    }else
        return 0;                    
}

int chessGame::move(){  //processes all action required to make move and switch turn
                        //cooperates with fieldClicked in case of human player
    //if game not started, abort
    if(!isStarted)
        throw("game not started");
    if(SFMLSupport[ turn ]){
        return 0;   //if action is required to complete move, function halts and returns 0
    }else{
        turn = players[ turn ]->processMove(sf::Vector2i(-1,-1));   //blank value (-1, -1)
        return 1;   //if no action is required then players instance processes the move
    }

}

bool chessGame::clearChecks() const{
    king* p = (king*)BlackKingsArray[ 0 ];
    while( p->isCheck() )
        p->unsetCheck();
    p = (king*)WhiteKingsArray[ 0 ];
    while( p->isCheck())
        p->unsetCheck();
    return true;
}

int chessGame::clearGlobalMoveBoards(){    //sets all fields in global movement boards to FREE_FIELD
    for(int x = 0; x < 8; x++)
        for(int y = 0; y < 8; y++){
            WhiteMoveBoard[ x ][ y ] = FREE_FIELD;
            BlackMoveBoard[ x ][ y ] = FREE_FIELD;
        }
    return 0;
}

int chessGame::clearAllBindArraysAndBindings(){
    for(int x = 0; x < 8; x++)
        for(int y = 0; y < 8; y++){
            if(globalBoard[ x ][ y ] >= HOSTILE_BASE ){
                globalChessboard[ x ][ y ]->clearBindArray();
                globalChessboard[ x ][ y ]->unbind();
            }
        }
    return 0;
}


int chessGame::processAll(bool marking){  //when true function tells pieces to mark informational values, not doing it otherwise
    //if game not started, abort
    if(!isStarted)
        throw("game not started");
    for(int x = 0; x < 8; x++){
        for(int y = 0; y < 8; y++)
            if(globalBoard[ x ][ y ] > FREE)
                globalChessboard[ x ][ y ]->process(marking);
    }
    return 0;
}

chessPlayer::chessPlayer(){     //default constructor creates empty player object
    friendGlobalMoveBoard = hostileGlobalMoveBoard = nullptr;
    game = nullptr;
}

int chessPlayer::initialize(chessGame* gamePointer,    //pointer to parent chessGame object
                            int** friendMoveBoard,  //pointer to 2d array on which ally moves and bindings are saved
                            int** hostileMoveBoard,  //pointer to 2d array on which hostile moves and possible new bindings are saved
                            chessPiece*** globalChessb, ////2d global chessboard array of chesspiece object pointers
                            int** globalBoardd,        //pointer to 2d array on which all pieces are saved
                            int side    //players side
                            ){
    sideIdentifier = side;
    game = gamePointer;
    friendGlobalMoveBoard = friendMoveBoard;
    globalChessboard = globalChessb;
    globalBoard = globalBoardd;
    hostileGlobalMoveBoard = hostileMoveBoard;
    return 0;
}

int chessPlayer::getSide() const{
    return sideIdentifier;
}

int chessPlayer::getColour() const{
    return sideIdentifier == WHITE_TURN_I ? WHITE : BLACK;
}

int chessPlayer::endTurn(){ //all action needed for ending(switching) turn
    game->clearChecks();
    game->clearGlobalMoveBoards();
    game->clearAllBindArraysAndBindings();
    game->processAll(1);
    game->processAll(0);
    return !getSide();
}

int chessPlayer::checkFieldForFigure( sf::Vector2i attackedField){   //analyzes field and returns proper integer identifier
    if( attackedField.x < 0 || attackedField.x > 7 || attackedField.y < 0 || attackedField.y > 7)
        return OUTSIDE_THE_CHESSBOARD_FIELD;
    chessPiece* piece = globalChessboard[ attackedField.x ][ attackedField.y ];
    if( globalBoard[ attackedField.x ][ attackedField.y ] == FREE)
        if(hostileGlobalMoveBoard[ attackedField.x ][ attackedField.y ] == ATTACKED_BY_HOSTILE_FIELD
                || hostileGlobalMoveBoard[ attackedField.x ][ attackedField.y ] == POSSIBLE_BINDING)
            return hostileGlobalMoveBoard[ attackedField.x ][ attackedField.y ];
        else
            return FREE_FIELD;
    else if( getColour() == 
                globalBoard[ attackedField.x ][ attackedField.y ] - piece->whatIs()){
        return FRIENDLY_BASE + piece->whatIs();
    }
    else{
        return HOSTILE_BASE + piece->whatIs();
    }
}

int chessPlayer::makeMove(sf::Vector2i destinatedField, chessPiece* piece){
    if( game->piecesSprites[ XYtoNumerical(destinatedField) ] != nullptr )
            ShowSprite(game->piecesSprites[ XYtoNumerical(destinatedField) ], HIDE);
        MoveSprite(XYtoNumerical(piece->getPosition()), 
                    XYtoNumerical(destinatedField), game->piecesSprites);
        piece->movePiece(destinatedField);
    return 0;
}

humanPlayer::humanPlayer(sf::VertexArray* circles  //circle array
                            ): chessPlayer(){  //default constructor
    pointerToCircles = circles;
    moveBoard = nullptr;
    selectedPiece = nullptr;
    fieldClicked = sf::Vector2i(-1,-1);
}

sf::Vector2i humanPlayer::convertPosToInt(sf::Vector2f inputPos){ //method for converting position from x, y input to field number
    return sf::Vector2i((int(inputPos.x) * 8 / s), (int(inputPos.y) * 8 / s ));
}

int XYtoNumerical(sf::Vector2i inputCordinates){   //converts X Y cordinates to int cordinate
    return inputCordinates.x + 8 * inputCordinates.y;
}

int humanPlayer::processMove(sf::Vector2i clicked){ //method for processing move
    fieldClicked = clicked;
    if(checkFieldForFigure(clicked) >= FRIENDLY_BASE &&
            checkFieldForFigure(clicked) <= OUTSIDE_THE_CHESSBOARD_FIELD){
        HideAllCircles(pointerToCircles, cir_a);
        selectedPiece = globalChessboard[ fieldClicked.x ][ fieldClicked.y ];
        moveBoard = selectedPiece->moveArray;
        for(int x = 0; x < 8; x++){
            for(int y = 0; y < 8; y++)
                if( moveBoard[ x ][ y ] == POSSIBLE_MOVE || moveBoard[ x ][ y ] == POSSIBLE_CASTLING)
                    ShowCircles(&pointerToCircles[ XYtoNumerical(sf::Vector2i(x,y)) ], cir_a, 1);
        }
        return getSide();
    }
    else if(selectedPiece != nullptr && moveBoard[ fieldClicked.x ][ fieldClicked.y ] == POSSIBLE_MOVE){
        makeMove(clicked, selectedPiece);
        HideAllCircles(pointerToCircles, cir_a);
        moveBoard = nullptr;
        selectedPiece = nullptr;
        return endTurn();
    }
    else if(selectedPiece != nullptr && moveBoard[ fieldClicked.x ][ fieldClicked.y ] == POSSIBLE_CASTLING){
        makeMove(fieldClicked, selectedPiece);
        if( fieldClicked.x > 3)
            makeMove( fieldClicked - sf::Vector2i(1,0), globalChessboard[ 7 ][ fieldClicked.y ]);
        else
            makeMove( fieldClicked + sf::Vector2i(1,0), globalChessboard[ 0 ][ fieldClicked.y ]);
        HideAllCircles(pointerToCircles, cir_a);
        moveBoard = nullptr;
        selectedPiece = nullptr;
        return endTurn();
    }
    else{
        HideAllCircles(pointerToCircles, cir_a);
        moveBoard = nullptr;
        selectedPiece  = nullptr;
        return getSide();
    }
}



chessPiece::chessPiece( //constructor
                        int** global_moveBoard,             //pointer to array on which all pieces are saved
                        int** hostileMoves,       //pointer to array on which hostile moves and bindings are saved
                        int** friendMoves,          //pointer to array on which ally moves and bindings are saved
                        chessPiece*** global_Chessboard,  //pointer to global chessboard array
                        chessPiece** kingsArray,   //pointer to kings array
                        int Xposition,                //xposition of the piece
                        int Yposition,                //yposition of the piece
                        int color                  //colour of the piece     
                    ) : globalBoard(global_moveBoard), globalChessboard(global_Chessboard), 
                    friendGlobalMoveBoard(friendMoves), hostileGlobalMoveBoard(hostileMoves), 
                    kings(kingsArray), colour(color){
    pos = sf::Vector2i(Xposition, Yposition);
    moveCount = 0;
    binded = false;
    globalChessboard[ pos.x ][ pos.y ] = this;
    //moveArray = new int*[ 8 ];
    for(int i = 0; i < 8; i++){
        moveArray[ i ] = new int[ 8 ];
        bindArray[ i ] = new int[ 8 ];
    }
    for(int i = 0; i < 64; i++){
        moveArray[ i % 8 ][ i / 8 ] = UNDEFINED_FIELD;
        bindArray[ i % 8 ][ i / 8 ] = INVALID_FIELD;
    }
    
}

bool chessPiece::setMarking(bool marking){
    bool temp = markingVar;
    markingVar = marking;
    return temp;
}

int chessPiece::getMoveCount() const{   //returns value corresponding to number of moves
    return moveCount;
}

int chessPiece::isCheck() const{        //cheks for check
    return kings[0]->isCheck();
}

int chessPiece::setCheck(){         //increments check value and sets 'Checking figure' state on field
    return kings[1]->setCheck();
}

int chessPiece::setCheck(sf::Vector2i pos){  //passes position from check is coming( used onli for pieces with linearmovement scheme)
    return kings[ 1 ]->setCheck(pos);
}

int chessPiece::unsetCheck(){       //decrements check value
    return kings[1]->unsetCheck();
}

sf::Vector2i chessPiece::getPosition() const{  //getter for position value, returns position of the piece
    return pos;
}

int chessPiece::getColour() const{  //getter for colour value, returns colour of the piece
    return colour;  
}

bool chessPiece::isBinded() const{
    return binded;
}

int chessPiece::bind(chessPiece* piece) const{
    piece->binded = true;
    return 0;
}

int chessPiece::unbind(){
    binded = false;
    return 0;
}

int chessPiece::linearMovement(sf::Vector2i shift, bool check){
    sf::Vector2i attack = getPosition() + shift;
    while(checkFieldForFigure(attack) < HOSTILE_PAWN){
        attackField(attack);
        attack += shift;
    }
    attackField(attack);
    if(checkFieldForFigure(attack) == HOSTILE_KING){    //if hostile king is under attack then sets check 
        //and sets POSSIBLE_BINDING state on all fields that can be covered
        attack = getPosition() + shift;
        while(checkFieldForFigure(attack) < HOSTILE_KING){
            setBindingOnField(attack);
            attack += shift;
        }
    }
        
    else if(checkFieldForFigure(attack) < HOSTILE_KING){
        attackField(attack);
        chessPiece* binded = getPiece(attack);
        attack += shift;
        while(checkFieldForFigure(attack) < HOSTILE_KING)
            attack += shift;
        if(checkFieldForFigure(attack) == HOSTILE_KING){
            attack = getPosition();
            bind(binded);
            while(checkFieldForFigure(attack) != HOSTILE_KING){
                bindField(binded, attack);
                attack += shift;
            }
        }
    }
    return 0;
}

int chessPiece::checkFieldForFigure( sf::Vector2i attackedField){   //analyzes field and returns proper integer identifier
    if( attackedField.x < 0 || attackedField.x > 7 || attackedField.y < 0 || attackedField.y > 7)
        return OUTSIDE_THE_CHESSBOARD_FIELD;
    chessPiece* piece = globalChessboard[ attackedField.x ][ attackedField.y ];
    if( globalBoard[ attackedField.x ][ attackedField.y ] == FREE)
        if(hostileGlobalMoveBoard[ attackedField.x ][ attackedField.y ] == ATTACKED_BY_HOSTILE_FIELD
                || hostileGlobalMoveBoard[ attackedField.x ][ attackedField.y ] == POSSIBLE_BINDING)
            return hostileGlobalMoveBoard[ attackedField.x ][ attackedField.y ];
        else
            return FREE_FIELD;
    else if( getColour() == 
                globalBoard[ attackedField.x ][ attackedField.y ] - piece->whatIs()){
        return FRIENDLY_BASE + piece->whatIs();
    }
    else{
        return HOSTILE_BASE + piece->whatIs();
    }
}

int chessPiece::clearMoveBoard(){   //sets all fields in moveArray to INVALID_FIELD
    for(int x = 0; x < 8; x++)
        for(int y = 0; y < 8; y++)
            moveArray[ x ][ y ] = INVALID_FIELD;
    return 0;
}

int chessPiece::clearBindArray(){
    for(int x = 0; x < 8; x++)
        for(int y = 0; y < 8; y++)
            bindArray[ x ][ y ] = INVALID_FIELD;
    return 0;
}


int chessPiece::movePiece(  //applies all action essential for doing move to engine
                            sf::Vector2i destination    //field to which piece is moving
                            ){
    if( globalBoard[ destination.x ][ destination.y ] > FREE)
        delete globalChessboard[ destination.x ][ destination.y ];
    globalChessboard[ destination.x ][ destination.y ] = globalChessboard[ pos.x ][ pos.y ];
    globalChessboard[ pos.x ][ pos.y ] = nullptr;
    globalBoard[ destination.x ][ destination.y ] = globalBoard[ pos.x ][ pos.y ];
    globalBoard[ pos.x ][ pos.y ] = FREE;
    pos = destination;
    binded = false;
    moveCount++;
    return 0;
}

chessPiece* chessPiece::getPiece(sf::Vector2i pos){ //returns pointer to piece located on pos field
    return globalChessboard[ pos.x ][ pos.y ];
} 

bool chessPiece::possibleMove(sf::Vector2i designatedField){    //processing related to possible move
    moveArray[ designatedField.x ][ designatedField.y ] = POSSIBLE_MOVE;
    return true;
}

/*bool chessPiece::attackField(sf::Vector2i attackedField){    //processing related to possible attack movement
    if(!isBinded() || bindArray[ attackedField.x ][ attackedField.y ] == BINDED)
        possibleMove(attackedField);
    if(markingVar){
        if( friendGlobalMoveBoard[ attackedField.x ][ attackedField.y ] != POSSIBLE_BINDING)
            friendGlobalMoveBoard[ attackedField.x ][ attackedField.y ] = ATTACKED_BY_HOSTILE_FIELD;
        if( checkFieldForFigure(attackedField) == HOSTILE_KING)
            setCheck(pos);
    }
    /////
    return true;
}*/


bool chessPiece::attackField(sf::Vector2i attackedField){
    if((!isBinded() || bindArray[ attackedField.x ][ attackedField.y ] == BINDED) &&
                (!isCheck() || checkFieldForFigure(attackedField) == POSSIBLE_BINDING || ((king*)kings[ 0 ])->getCheckingPiecePosition() == attackedField) &&
                 checkFieldForFigure(attackedField) < FRIENDLY_BASE)
        possibleMove(attackedField);
    markFieldAsAttacked(attackedField);
    return true;
}


bool chessPiece::markFieldAsAttacked(sf::Vector2i attackedField){
    if(checkFieldForFigure(attackedField) != OUTSIDE_THE_CHESSBOARD_FIELD){
        if(markingVar){
            if( friendGlobalMoveBoard[ attackedField.x ][ attackedField.y ] != POSSIBLE_BINDING)
                friendGlobalMoveBoard[ attackedField.x ][ attackedField.y ] = ATTACKED_BY_HOSTILE_FIELD;
            if( checkFieldForFigure(attackedField) == HOSTILE_KING)
                setCheck(pos);
        }
    }
    return true;
}

bool chessPiece::setBindingOnField(sf::Vector2i designatedField){   //sets POSSIBLE_BINDING on field, marking the field as to be covered
    if(markingVar)
        friendGlobalMoveBoard[ designatedField.x ][ designatedField.y ] = POSSIBLE_BINDING;
    return true;
}

int bindField(chessPiece* piece, sf::Vector2i field){
    piece->bindArray[ field.x ][ field.y ] = BINDED;
    return 0;
}

pawn::pawn( //pawn constructor
            int** globalMoveBoard,         //pointer to array on which all moves and pieces are saved
            int** hostileMoves,       //pointer to array on which hostile moves and bindings are saved
            int** friendMoves,          //pointer to array on which ally moves and bindings are saved
            chessPiece*** global_Chessboard,  //pointer to global chessboard array
            chessPiece** kingsArray,   //pointer to kings array
            int Xposition,                //xposition of the piece
            int Yposition,                //yposition of the piece
            int color,                  //colour of the piece     
            int Orientation        //orientation of the board
                                        //1 upside down
                                        //-1 normal
                    ) : chessPiece(globalMoveBoard, hostileMoves, friendMoves,  global_Chessboard,
                                 kingsArray, Xposition, Yposition, color), orientation(Orientation){}



int pawn::whatIs() const{   //returns integer identifier of piece
    return  PAWN;
}

int pawn::process(bool marking){    //proceses pawns move, marks fields on which it can step, sets cheks and bindings
    clearMoveBoard();
    setMarking(marking);
    switch(isCheck()){
        case NO_CHECK:{
            sf::Vector2i position = getPosition();
            position.y += orientation;
            
            if(checkFieldForFigure(position) < HOSTILE_BASE){
                possibleMove(position);
                if(getMoveCount() == 0){
                    sf::Vector2i position2 = getPosition();
                    position2.y += orientation * 2;
                    if(checkFieldForFigure(position2) < HOSTILE_BASE)
                        possibleMove(position2);
                }
            }
            position.x --;
            if(checkFieldForFigure(position) < FRIENDLY_BASE && checkFieldForFigure(position) >= HOSTILE_BASE)
                attackField(position);
            else if( checkFieldForFigure(position) != OUTSIDE_THE_CHESSBOARD_FIELD)
                markFieldAsAttacked(position);
            position.x += 2;
            if(checkFieldForFigure(position) < FRIENDLY_BASE && checkFieldForFigure(position) >= HOSTILE_BASE)
                attackField(position);
            else if( checkFieldForFigure(position) != OUTSIDE_THE_CHESSBOARD_FIELD)
                markFieldAsAttacked(position);
        }
        break;
        case CHECK:{
            sf::Vector2i position = getPosition();
            position.y += orientation;
            
            if(checkFieldForFigure(position) < HOSTILE_BASE){
                if(checkFieldForFigure(position) == POSSIBLE_BINDING)
                    possibleMove(position);
                if(getMoveCount() == 0){
                    sf::Vector2i position2 = getPosition();
                    position2.y += orientation * 2;
                    if(checkFieldForFigure(position2) == POSSIBLE_BINDING)
                        possibleMove(position2);
                }
            }

            if(((king*)kings[ 0 ])->getCheckingPiecePosition() == (position + sf::Vector2i(-1, 0)))
                attackField(position + sf::Vector2i(-1, 0));
            if(((king*)kings[ 0 ])->getCheckingPiecePosition() == (position + sf::Vector2i(1, 0)))
                attackField(position + sf::Vector2i(1, 0));
                
        }
        break;
        case DOUBLE_CHECK:

        break;
    }
    return 0;
}

rook::rook(         //rook constructor
            int** globalMoveBoard,         //pointer to array on which all moves and pieces are saved
            int** hostileMoves,       //pointer to array on which hostile moves and bindings are saved
            int** friendMoves,          //pointer to array on which ally moves and bindings are saved
            chessPiece*** global_Chessboard,  //pointer to global chessboard array
            chessPiece** kingsArray,   //pointer to kings array
            int Xposition,                //xposition of the piece
            int Yposition,                //yposition of the piece
            int color                  //colour of the piece   
            ) : chessPiece(globalMoveBoard, hostileMoves, friendMoves,  global_Chessboard,
                                 kingsArray, Xposition, Yposition, color),
                                 side(getPosition().x == 0 ? LEFT : getPosition().x == 7 ? RIGHT : SIDE_UNDEFINED){}

int rook::whatIs() const{   //returns integer identifier of piece
    return ROOK;
}

int rook::process(bool marking){      //proceses rooks move, marks fields on which it can step, sets cheks and bindings
    clearMoveBoard();
    setMarking(marking);
    switch(isCheck()){
        case NO_CHECK:
        case CHECK:
            linearMovement(sf::Vector2i(1, 0), isCheck());
            linearMovement(sf::Vector2i(-1, 0), isCheck());
            linearMovement(sf::Vector2i(0, 1), isCheck());
            linearMovement(sf::Vector2i(0, -1), isCheck());  
        break;
        case DOUBLE_CHECK:

        break;
    }
    return 0;
}

knight::knight(         //knight constructor
            int** globalMoveBoard,         //pointer to array on which all moves and pieces are saved
            int** hostileMoves,       //pointer to array on which hostile moves and bindings are saved
            int** friendMoves,          //pointer to array on which ally moves and bindings are saved
            chessPiece*** global_Chessboard,  //pointer to global chessboard array
            chessPiece** kingsArray,   //pointer to kings array
            int Xposition,                //xposition of the piece
            int Yposition,                //yposition of the piece
            int color                  //colour of the piece   
            ) : chessPiece(globalMoveBoard, hostileMoves, friendMoves,  global_Chessboard,
                                 kingsArray, Xposition, Yposition, color){}

bishop::bishop(         //bishop constructor
            int** globalMoveBoard,         //pointer to array on which all moves and pieces are saved
            int** hostileMoves,       //pointer to array on which hostile moves and bindings are saved
            int** friendMoves,          //pointer to array on which ally moves and bindings are saved
            chessPiece*** global_Chessboard,  //pointer to global chessboard array
            chessPiece** kingsArray,   //pointer to kings array
            int Xposition,                //xposition of the piece
            int Yposition,                //yposition of the piece
            int color                  //colour of the piece   
            ) : chessPiece(globalMoveBoard, hostileMoves, friendMoves,  global_Chessboard,
                                 kingsArray, Xposition, Yposition, color){}

queen::queen(         //queen constructor
            int** globalMoveBoard,         //pointer to array on which all moves and pieces are saved
            int** hostileMoves,       //pointer to array on which hostile moves and bindings are saved
            int** friendMoves,          //pointer to array on which ally moves and bindings are saved
            chessPiece*** global_Chessboard,  //pointer to global chessboard array
            chessPiece** kingsArray,   //pointer to kings array
            int Xposition,                //xposition of the piece
            int Yposition,                //yposition of the piece
            int color                  //colour of the piece   
            ) : chessPiece(globalMoveBoard, hostileMoves, friendMoves,  global_Chessboard,
                                 kingsArray, Xposition, Yposition, color){}

king::king(         //king constructor
            int** globalMoveBoard,         //pointer to array on which all moves and pieces are saved
            int** hostileMoves,       //pointer to array on which hostile moves and bindings are saved
            int** friendMoves,          //pointer to array on which ally moves and bindings are saved
            chessPiece*** global_Chessboard,  //pointer to global chessboard array
            chessPiece** kingsArray,   //pointer to kings array
            int Xposition,                //xposition of the piece
            int Yposition,                //yposition of the piece
            int color                  //colour of the piece   
            ) : chessPiece(globalMoveBoard, hostileMoves, friendMoves,  global_Chessboard,
                                 kingsArray, Xposition, Yposition, color){
    check = 0;
}

int king::setCheck(){
    return ++check;
}

int king::setCheck(sf::Vector2i pos){
    checkingPiece = pos;
    return ++check;
}

int king::unsetCheck(){
    return --check;
}

int king::isCheck() const{
    return check;
}

int king::whatIs() const{
    return KING;
}

sf::Vector2i king::getCheckingPiecePosition(){
    return checkingPiece;
}

int king::process(bool marking){
    sf::Vector2i position2 = getPosition();
    int result = 0;
    clearMoveBoard();
    setMarking(marking);
    switch(check){
        case NO_CHECK:
            if( getMoveCount() == 0 && 
                checkFieldForFigure(getPosition() - sf::Vector2i(4, 0)) == FRIENDLY_ROOK &&
                checkFieldForFigure(getPosition() - sf::Vector2i(3, 0)) == FREE_FIELD &&
                checkFieldForFigure(getPosition() - sf::Vector2i(2, 0)) == FREE_FIELD &&
                checkFieldForFigure(getPosition() - sf::Vector2i(1, 0)) == FREE_FIELD &&
                getPiece(getPosition() - sf::Vector2i(4, 0))->getMoveCount() == 0)
                    possibleCastling(LEFT);
            if( getMoveCount() == 0 &&
                checkFieldForFigure(getPosition() + sf::Vector2i(3, 0)) == FRIENDLY_ROOK &&
                checkFieldForFigure(getPosition() + sf::Vector2i(2, 0)) == FREE_FIELD &&
                checkFieldForFigure(getPosition() + sf::Vector2i(1, 0)) == FREE_FIELD &&
                getPiece(getPosition() + sf::Vector2i(3, 0))->getMoveCount() == 0)
                    possibleCastling(RIGHT);
            position2.x -= 1;
            result = checkFieldForFigure(position2);
            if(result == FREE_FIELD || (result >= HOSTILE_BASE && result < FRIENDLY_BASE))
                attackField(position2);
            position2.y += 1;
            result = checkFieldForFigure(position2);
            if(result == FREE_FIELD || (result >= HOSTILE_BASE && result < FRIENDLY_BASE))
                attackField(position2);
            position2.x += 1;
            result = checkFieldForFigure(position2);
            if(result == FREE_FIELD || (result >= HOSTILE_BASE && result < FRIENDLY_BASE))
                attackField(position2);
            position2.x += 1;
            result = checkFieldForFigure(position2);
            if(result == FREE_FIELD || (result >= HOSTILE_BASE && result < FRIENDLY_BASE))
                attackField(position2);
            position2.y -= 1;
            result = checkFieldForFigure(position2);
            if(result == FREE_FIELD || (result >= HOSTILE_BASE && result < FRIENDLY_BASE))
                attackField(position2);
            position2.y -= 1;
            result = checkFieldForFigure(position2);
            if(result == FREE_FIELD || (result >= HOSTILE_BASE && result < FRIENDLY_BASE))
                attackField(position2);
            position2.x -= 1;
            result = checkFieldForFigure(position2);
            if(result == FREE_FIELD || (result >= HOSTILE_BASE && result < FRIENDLY_BASE))
                attackField(position2);
            position2.x -= 1;
            result = checkFieldForFigure(position2);
            if(result == FREE_FIELD || (result >= HOSTILE_BASE && result < FRIENDLY_BASE))
                attackField(position2);

        break;
        case CHECK:

        break;
        case DOUBLE_CHECK:

        break;
    }
    return 0;
}

int king::possibleCastling(bool side){
    switch(side){
        case LEFT:
            moveArray[ getPosition().x - 2 ][ getPosition().y ] = POSSIBLE_CASTLING;
        break;
        case RIGHT:
            moveArray[ getPosition().x + 2 ][ getPosition().y ] = POSSIBLE_CASTLING;
        break;
    }
    return 0;
}