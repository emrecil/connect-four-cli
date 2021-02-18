#ifndef GAME_H
#define GAME_H

/* Size of board */
#define ROWS 6
#define COLUMNS 7

typedef struct
{
	/* 
	* Current player.
	* Player 1: -1
	* Player 2:  1
	*/
	int current_player;

	/*  Number of remaining checkers. */
	int remaining;
	
	/* 
	* Keeps count of checkers at every column.
	* Example: 	Player 1 drops a checker in (empty) column 3.
	*			-> column_height[3] = 1
	*/
	int column_height[COLUMNS];

	/* 
	* Stores current_player at dropped checker positions.
	* Example: 	See above
	*			-> board[0][3] = -1
	*/
	int board[ROWS][COLUMNS];
} Game;

/*
 * Initializes the game.
 * 
 * Parameters:
 * - Game *game 		Game to initialize
 * - char *initializer 	A sequence of numbers where checkers will be dropped
 * 
 * No return value.
 *
 * Initializes board[][], column_height with zeros, current_player with -1 and 
 * remaining with COLUMNS * ROWS. If initializer isn't empty
 * a checker will be dropped at column number in the initializer.
 * 
 * Valid parameter values are
 * - game   			Valid pointer to a game struct
 * - initializer		Null terminated string of length < remaining
 * 						Empty or filled with numbers (1 <= number <= COLUMNS)
 */
void initialize_game(Game *game, char *initializer);

/*
 * Writes a visualization of the board to stdout.
 * 
 * Parameters:
 * - Game *game 		Game to visualize
 *  
 * No return value.
 *
 * Prints current state of the board in a "visually pleasing" way.
 * 
 * Valid parameter values are
 * - game 				Valid pointer to a game struct
 */
void visualize_game(Game *game);

/*
 * Drops a checker at given column.
 * 
 * Parameters:
 * - Game *game 		Game to drop a checker
 * - int column 		Column the checker will be dropped at
 * 
 * No return value.
 *
 * Drops a checker at the first empty row at given column, increments 
 * game->column_height and decrements game->remaining. It does NOT toggle 
 * the current player!
 * 
 * Valid parameter values are
 * - game   			Valid pointer to a game struct
 * - column				0 <= column < COLUMNS
 */
void drop_at(Game *game, int column);

/*
 * Toggles the current player.
 * 
 * Parameters:
 * - Game *game 		Game to toggle current player
 *  
 * No return value.
 *
 * Toggles game->current_player between player 1 and player 2 depending on whose
 * turn it is.
 * 
 * Valid parameter values are
 * - game 				Valid pointer to a game struct
 */
void toggle_player(Game *game);

/*
 * Asks current player for the next move.
 * 
 * Parameters:
 * - Game *game 		Game to ask for the next move
 * 
 * Returns:
 * - int				Column with value: 0 <= column < COLUMNS
 *
 * Asks the player to enter a column with value: 1 <= input <= COLUMNS.
 * If the number entered by the player is invalid or the column is full
 * a warning will be displayed and the user is asked again to enter a number.
 * 
 * Valid parameter values are
 * - game 				Valid pointer to a game struct
 */
int get_player_move(Game *game);

/*
 * Asks current player for the next move.
 * 
 * Parameters:
 * - Game *game 		Game to ask for the next move
 * - int last_column	Column the last checker has been dropped at
 * 
 * Returns:
 * - int				game->current_player if won, else 0
 * 
 * Looks for four checkers in row horizontally, vertically and diagonally
 * starting from the position of the last dropped checker at last_column. 
 * 
 * Valid parameter values are
 * - game 				Valid pointer to a game struct
 */
int check_win(Game *game, int last_column);

#endif // GAME_H
