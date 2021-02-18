#include <stdio.h>
#include <stdlib.h>

#include "game.h"

void initialize_game(Game *game, char *initializer)
{
	// Player 1 starts
	game->current_player = -1;
	game->remaining = ROWS * COLUMNS;

	int row, column;

	// initialize arrays with zeros
	for (row = 0; row < ROWS; ++row)
	{
		for (column = 0; column < COLUMNS; ++column)
		{
			game->board[row][column] = 0;
			game->column_height[column] = 0;
		}
	}

	if (initializer != 0)
	{
		char *action = initializer;
		int column;

		while (*action != '\0')
		{
			column = *action - 49;
			drop_at(game, column);
			if (check_win(game, column) == 0) {
				fprintf(stderr, "Error: Initializer results in win! Aborting.\n");
				abort();
			}
			toggle_player(game);
			++action;
		}
	}
}

void visualize_game(Game *game)
{
	int row, column, i;

	// header
	printf("\u250C");
	for (column = 0; column < COLUMNS; ++column)
	{
		printf("\u2500\u2500\u2500\u2500");
		if (column == COLUMNS - 1)
			printf("\u2510");
		else
			printf("\u252C");
	}
	printf("\n");

	for (row = ROWS - 1; row >= 0; --row)
	{
		// rows with checkers
		printf("\u2502");
		for (column = 0; column < COLUMNS; ++column)
		{
			switch (game->board[row][column])
			{
			case -1:
				printf(" \u2588\u2588 ");
				break;
			case 1:
				printf(" \u2592\u2592 ");
				break;
			default:
				printf("    ");
			}
			printf("\u2502");
		}
		printf("\n");

		// row divider
		if (row > 0)
		{
			printf("\u251c");
			for (i = 0; i < column; i++)
			{
				printf("\u2500\u2500\u2500\u2500");
				if (i == column - 1)
					printf("\u2524");
				else
					printf("\u253c");
			}
			printf("\n");
		}
	}

	// footer
	printf("\u2514");
	for (column = 0; column < COLUMNS; column++)
	{
		printf("\u2500\u2500\u2500\u2500");
		if (column == COLUMNS - 1)
			printf("\u2518");
		else
			printf("\u2534");
	}
	printf("\n");

	// column numeration
	printf("  ");
	for (column = 1; column <= COLUMNS; column++)
	{
		printf("%d    ", column);
	}

	printf("\n");
}

void drop_at(Game *game, int column)
{
	int row = game->column_height[column];
	game->board[row][column] = game->current_player;
	game->column_height[column] += 1;
	game->remaining -= 1;
}

int get_player_move(Game *game)
{
	/*
	 * TODO: Solve issue: User inputs nondigit
	 */
	int column, valid;

	valid = 0;

	printf("Current Player: %d\n", (game->current_player == -1 ? 1 : 2));

	while (!valid)
	{
		printf("Enter Column: ");
		scanf("%d", &column);

		if (column > 0 && column <= COLUMNS)
		{
			if (game->column_height[column - 1] == ROWS)
				puts("Column full! Please choose another column!");
			else
				valid = 1;
		}

		else
			printf("Please enter a number between 1 and %d!\n", COLUMNS);
	}

	return column - 1;
}

void toggle_player(Game *game)
{
	game->current_player = 0 - game->current_player;
}

int check_win(Game *game, int last_column)
{
	int last_row, count, i;

	last_row = game->column_height[last_column] - 1;

	// horizontal
	count = 0;
	for (i = last_column; i < COLUMNS && game->board[last_row][i] == game->current_player; ++i)
	{
		++count;
	}
	for (i = last_column - 1; i >= 0 && game->board[last_row][i] == game->current_player; --i)
	{
		++count;
	}

	if (count >= 4)
		return game->current_player;

	// vertical
	count = 0;
	for (i = last_row; i < ROWS && game->board[i][last_column] == game->current_player; ++i)
	{
		++count;
	}
	for (i = last_row - 1; i >= 0 && game->board[i][last_column] == game->current_player; --i)
	{
		++count;
	}

	if (count >= 4)
		return game->current_player;

	int j;
	// diagonal "/"
	count = 0;
	for (i = last_row, j = last_column; i < ROWS && j < COLUMNS; ++i, ++j)
	{
		if (game->board[i][j] != game->current_player)
			break;
		++count;
	}
	for (i = last_row - 1, j = last_column - 1; i >= 0 && j >= 0; --i, --j)
	{
		if (game->board[i][j] != game->current_player)
			break;
		++count;
	}

	if (count >= 4)
		return game->current_player;

	// diagonal "\"
	count = 0;
	for (i = last_row, j = last_column; i < ROWS && j >= 0; ++i, --j)
	{
		if (game->board[i][j] != game->current_player)
			break;
		++count;
	}
	for (i = last_row - 1, j = last_column + 1; i >= 0 && j < COLUMNS; --i, ++j) {
		if (game->board[i][j] != game->current_player)
			break;
		++count;
	}
	
	if (count >= 4)
			return game->current_player;
	return 0;
}
