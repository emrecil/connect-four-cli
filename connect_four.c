#include <stdio.h>

#include "game.h"
#include "negamax.h"

/*
 * Starts actual loop of a connectfour game.
 * 
 * Parameters:
 *  - int mode			Sets players, see value meanings in documentation of 
 * 						prompt_mode()
 * 
 * No paramaters and no return values.
 *
 * Initializes and visualizes a game. In the loop: Asks the player to enter 
 * a column number, drops a checker at that column and visualizes the game again.
 * If there is a winner or a tie the loop breaks. Otherwise the current player
 * is toggled and the loop starts over.
 */
void run_game(int mode);

/*
 * Asks the player to choose the mode.
 * 
 * No parameters.
 * 
 * Returns:
 * - int				Value, 	Mode:
 * 						 - 0,	Human vs Human
 * 						 - 1,	Human vs AI
 * 						 - 2,	AI vs AI
 */
int prompt_mode(void);

/*
 * Asks the player to restart the game.
 * 
 * No parameters.
 * 
 * Returns:
 * - int				1 if player wants to restart, else 0
 */
int prompt_restart(void);

/*
 * Entry point.
 */
int main(void)
{
	do
	{
		run_game(prompt_mode());
	} while (prompt_restart());

	puts("Goodbye!");
	getchar();

	return 0;
}

void run_game(int mode)
{
	Game game;

	int column;

	initialize_game(&game, "");
	visualize_game(&game);

	do
	{
		printf("Current Player: %d\n", (game.current_player == -1 ? 1 : 2));

		if (mode == 3 || (game.current_player == 1 && mode == 2))
		{
			column = get_ai_move(&game);
			printf("AI chose column: %d\n", column + 1);
		}
		else
		{
			column = get_player_move(&game);
		}
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

int prompt_mode(void)
{
	int mode;
	puts("Choose players!");
	puts("[1] Human vs Human");
	puts("[2] Human vs AI");
	puts("[3] AI vs AI");

	printf("Enter your choice: ");
	scanf("%d", &mode);

	while (mode < 1 || mode > 3)
	{
		puts("Choice is invalid!");
		printf("Enter your choice: ");
		scanf("%d", &mode);
	}

	return mode;
}

int prompt_restart(void)
{
	int restart;
	printf("Press 1 to play again: ");
	scanf("%d", &restart);

	return (restart == 1 ? 1 : 0);
}
