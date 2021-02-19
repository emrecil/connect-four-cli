#include "negamax.h"

int get_ai_move(Game *game)
{
    return negamax(game, 0).column;
}

ComputerMove negamax(Game *game, int depth)
{
    ComputerMove best_move;
    ComputerMove current_move;
    Game tmp_game;

    // Setting worst possible values
    best_move.weight = -2 * ROWS * COLUMNS;
    best_move.column = -1;

    /* 
     * Base conditions:
     *  - no checkers left
     *  - MAX_DEPTH reached
    */
    if (game->remaining == 0 || depth == MAX_DEPTH)
    {
        best_move.weight = 0;
        return best_move;
    }

    int column;
    // Checking every column for best move
    for (column = 0; column < COLUMNS; ++column)
    {

        // Move is possible
        if (game->column_height[column] < ROWS)
        {
            tmp_game = *game;
            drop_at(&tmp_game, column);

            // Dropping checker at column results in win
            if (check_win(&tmp_game, column) != 0)
            {
                best_move.weight = ROWS * COLUMNS - depth;
                best_move.column = column;
                return best_move;
            }

            toggle_player(&tmp_game);

            current_move = negamax(&tmp_game, depth + 1);

            current_move.weight *= -1;

            // Dropping checker at column is better than best_move
            if (current_move.weight > best_move.weight)
            {
                // Updating best move
                best_move.weight = current_move.weight;
                best_move.column = column;
            }
        }
    }

    return best_move;
}