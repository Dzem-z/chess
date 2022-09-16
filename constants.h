#define CONSTANTS

//piece integer identifiers
#define PAWN 0
#define ROOK 1
#define KNIGHT 2
#define BISHOP 3
#define QUEEN 4
#define KING 5

#define LEFT 0
#define RIGHT 1
#define SIDE_UNDEFINED 2

//field integer identifiers for moveArray...
#define INVALID_FIELD 0
#define UNDEFINED_FIELD -1
#define POSSIBLE_MOVE 1
#define BINDED 2
#define POSSIBLE_CASTLING 3
//... and for friend/hostile arrays
//valid fields from to [1, 13)
//free fields from to [1, 7)
#define FREE_FIELD 1
#define FIELD_UNDER_ATTACK 2
#define ATTACKED_BY_ALLY_FIELD 3
#define ATTACKED_BY_HOSTILE_FIELD 4
#define POSSIBLE_BINDING 5
//field occupied by a hostile [7, 13)
#define HOSTILE_BASE 7
#define HOSTILE_PAWN HOSTILE_BASE + PAWN
#define HOSTILE_ROOK HOSTILE_BASE + ROOK
#define HOSTILE_KNIGHT HOSTILE_BASE + KNGIHT
#define HOSTILE_BISHOP HOSTILE_BASE + BISHOP
#define HOSTILE_QUEEN HOSTILE_BASE + QUEEN
#define HOSTILE_KING HOSTILE_BASE + KING
//invalid fields from to [13, 19)
//fields occupied by an allies [13, 18)
#define FRIENDLY_BASE 13
#define FRIENDLY_PAWN FRIENDLY_BASE + PAWN
#define FRIENDLY_ROOK FRIENDLY_BASE + ROOK
#define FRIENDLY_KNIGHT FRIENDLY_BASE + KNIGHT
#define FRIENDLY_BISHOP FRIENDLY_BASE + BISHOP
#define FRIENDLY_QUEEN FRIENDLY_BASE + QUEEN
#define FRIENDLY_KING FRIENDLY_BASE + KING
//fields outside of the chessboard [18]
#define OUTSIDE_THE_CHESSBOARD_FIELD 18
//check identifiers
#define NO_CHECK 0
#define CHECK 1
#define DOUBLE_CHECK 2

//colour integer identifiers( for globalBoard array)
#define FREE 0
#define BLACK 1
#define BLACK_PAWN BLACK + PAWN
#define BLACK_ROOK BLACK + ROOK
#define BLACK_KNIGHT BLACK + KNIGHT
#define BLACK_BISHOP BLACK + BISHOP
#define BLACK_QUEEN BLACK + QUEEN
#define BLACK_KING BLACK + KING
#define WHITE 8
#define WHITE_PAWN WHITE + PAWN
#define WHITE_ROOK WHITE + ROOK
#define WHITE_KNIGHT WHITE + KNIGHT
#define WHITE_BISHOP WHITE + BISHOP
#define WHITE_QUEEN WHITE + QUEEN
#define WHITE_KING WHITE + KING
//turn definitions and index
#define BLACK_TURN_I 1
#define WHITE_TURN_I 0
//orientation
#define UPSIDE_DOWN 1
#define NORMAL_ORIENTATION -1
//show hide flags
#define SHOW 1
#define HIDE 0
