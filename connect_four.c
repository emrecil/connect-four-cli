#include <stdio.h>

#include "game.h"

/*
 * Starts actual loop of a connectfour game.
 * 
 * No paramaters and no return values.
 *
 * Initializes and visualizes a game. In the loop: Asks the player to enter 
 * a column number, drops a checker at that column and visualizes the game again.
 * If there is a winner or a tie the loop breaks. Otherwise the current player
 * is toggled and the loop starts over.
 */
void run_game(void);

/*
 * Asks the player to restart the game.
 * 
 * No parameters.
 * 
 * Returns:
 * - int				1 if player wants to restart, else 0
 *
 * Diese Funktion bestimmt mit Hilfe der Regel von Conway's Game of Life
 * den Zustand einer Zelle in der naechsten Generation.
 */
int prompt_restart(void);

/*
* Entry point.
*/
int main(void)
{
	do
	{
		run_game();
	} while (prompt_restart());

	puts("Goodbye!");
	getchar();

	return 0;
}

void run_game(void)
{
	Game game;

	int column;

	initialize_game(&game, "");
	visualize_game(&game);

	do
	{
		column = get_player_move(&game);
		drop_at(&game, column);
		visualize_game(&game);
		if (check_win(&game, column))
		{
			printf("Player %d won!\n", (game.current_player == -1 ? 1 : 2));
			break;
		}
		else if (game.remaining == 0)
		{
			puts("Tie!");
			break;
		}
		else
		{
			toggle_player(&game);
		}

	} while (1);
}

int prompt_restart(void)
{
	int restart;
	printf("Press 1 to play again: ");
	scanf("%d", &restart);

	return (restart == 1 ? 1 : 0);
}