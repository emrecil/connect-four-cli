#ifndef CONNECT_FOUR_NEGAMAX_H
#define CONNECT_FOUR_NEGAMAX_H

#include "game.h"

/* Maximum search depth. */
#define MAX_DEPTH 8

/* Needed for recursive call of negamax(). */
typedef struct
{
    /* Weight of this move */
    int weight;
    /* Column of this move */
    int column;
} ComputerMove;

/*
 * Asks current player for the next move.
 * 
 * Parameters:
 * - Game *game 		Game to compute the next move for
 * 
 * Returns:
 * - int				Column with value: 0 <= column < COLUMNS
 *
 * Calls the function negamax with necessary start parameters.
 * 
 * Valid parameter values are
 * - game 				Valid pointer to a game struct
 */
int get_ai_move(Game *game);

/*
 * Implementation of the negamax algorithm.
 *
 * Parameters:
 * - Game *game 		Game to compute the next move for
 * - int depth          Current depth of computed move
*/
ComputerMove negamax(Game *game, int depth);

#endif // CONNECT_FOUR_NEGAMAX_H
