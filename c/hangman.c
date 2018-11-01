#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// mtest

// This function takes a character to print, an integer n for the amount of times to print,
// and an integer space indicating if the user would like spaces between their characters.
// (0 for no, 1 for yes)
char print_char(char ch, int n, int space)
{
	int i;
	for (i = 0; i < n; i++)
	{
		if (space)
		{
			printf("%c ", ch);
		}
		else
		{
			printf("%c", ch);
		}
	}
	printf("\n");
}

// Function that takes an integer array, the length of the array, and an integer, and checks
// whether the integer appears within the array, returning 1 if found, returning 0 otherwise.
int value_is_in_array(int *index_arr, int length, int val)
{
	int i;

	for (i = 0; i < length; i++)
	{
		if (index_arr[i] == val)
		{
			return 1;
		}
	}
	return 0;
}

// Function that takes a string as its only parameter and mixes its characters, resulting
// in a scrambled string.
void scramble_string(char *str)
{
	int i, j = 0, length = strlen(str), rand_index, index_exceptions[100];
	char dest[100] = "";

	for (i = 0; i < length; i++)
	{
		index_exceptions[i] = -1;
	}

	while (j < length)
	{
		rand_index = rand() % length;

		if (!value_is_in_array(index_exceptions, length, rand_index))
		{
			dest[rand_index] = str[j];
			index_exceptions[j] = rand_index;
			j++;
		}
	}
	strcpy(str, dest);
}

// Function that takes an integer that represents the difficulty level (1-5) and starts the hangman
// game. The player can only make 5 or less incorrect guesses before he loses.
void hangman(int difficulty)
{
	int i, j, k;
	int field_width = 50;
	int num_guesses = 5;
	int guess_right = 0;
	int position = -1;
	int word_length;

	char guess;
	char source[100] = "";
	char dest[100] = "";
	char scrambled_str[100] = "";
	char word_list[5][100] = {"juicy", "puzzle", "abandon", "flapjack", "quizzical"};

	strcpy(source, word_list[difficulty - 1]);
	word_length = strlen(source);

	strcpy(scrambled_str, source);
	scramble_string(scrambled_str);

	// Initializes dest with all asterisks up to the length of the source string.
	for (i = 0; i < word_length; i++)
	{
		dest[i] = '*';
		//field_width++;
	}

	printf("\n\n%*s", field_width, "** Hangman **\n\n");
	printf("%36s", "");
	print_char('*', word_length * 2 - 1, 0);
	printf("%36s", "");
	print_char('.', word_length, 1);
	printf("\n");
	printf("%36s", "");
	print_char('_', word_length, 1);
	printf("%36s", "");
	print_char('.', word_length, 1);
	printf("%36s", "");
	print_char('*', word_length * 2 - 1, 0);
	//printf("%50s", "*************\n");
	//printf("%51s", ". . . . . . .\n\n");
	//printf("%36s", "");
	//printf("%50s", ". . . . . . .\n");
	//printf("%51s", "*************\n\n");

	while (strcmp(source, dest) != 0)
	{
		printf("scrambled word: %s\n\n", scrambled_str);
		printf("Enter a character. (Or enter 0 to quit)\n");
		scanf("%c", &guess);

		if (guess == '0' || position == 0)
		{
		  break;
		}

		while (getchar() != '\n');

		printf("Enter a position to place the character. (1 - %d) (Or enter 0 to quit)\n", word_length);
		scanf("%d", &position);

		if (guess == '0' || position == 0)
		{
			break;
		}

		while (getchar() != '\n');

		while (position < 0 || position > word_length)
		{
			printf("Enter a  valid position to place the character. (1 - %d) (Or enter 0 to quit)\n", word_length);
			scanf("%d", &position);
			while (getchar() != '\n');
		}

		//while (getchar() != '\n');

		if (guess == '0' || position == 0)
		{
			break;
		}

		for (j = 0; j < word_length; j++)
		{
		  if (guess == source[j])
		  {
			 dest[j] = source[j];
			 guess_right = 1;
			 //printf("%s\n", dest);
		  }
		}

		if (guess_right == 0)
		{
		  num_guesses--;
		  if (num_guesses == 0)
		  {
			 printf("You are out of guesses!\nGAME OVER\n");
			 break;
		  }
		  printf("You guessed wrong! You have %d guesses left!\n", num_guesses);
		}
		else
		{
		  printf("You guessed a character correctly!\n");
		  printf("\n\n%50s", "** Hangman **\n");
		  printf("%36s", "");
		  print_char('*', word_length * 2 - 1, 0);
		  printf("%36s", "");
		  print_char('.', word_length, 1);
		  printf("\n%36s", "");

		  for (k = 0; k < word_length; k++)
		  {
			 printf("%c ", dest[k]);
		  }

		  printf("\n%36s", "");
		  print_char('_', word_length, 1);
		  printf("%36s", "");
		  print_char('.', word_length, 1);
		  printf("%36s", "");
		  print_char('*', word_length * 2 - 1, 0);

		  if (strcmp(source, dest) == 0)
		  {
			 printf("Congratulations! You Won!!!!!\n");
		  }
		  guess_right = 0;
		}
	}
	return;
}

int main(void)
{
	srand(time(NULL));
	int difficulty;

	printf("Please enter a difficulty level 1-5.\n");
	scanf("%d", &difficulty);

	while (difficulty < 1 || difficulty > 5)
	{
		printf("Please enter a valid difficulty level (1-5).\n");
		scanf("%d", &difficulty);
	}

	while (getchar() != '\n');

	hangman(difficulty);
	return 0;
}
