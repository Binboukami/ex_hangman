#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <conio.h>

/** WORD: AMENDOIM  */
#define WORD_SZ 8
#define MAX_ATTEMPTS 6

/** KEYBINDS **/
#define KEY_ESC 27
// #define KEY_A 65
// #define KEY_Q 81

#define U_CHAR_SZ 9	/** Size of Unicode character strings in bits */

#define U_VPOLE "\U0001F488"
#define U_HPOLE "\U00002796"
#define U_ROPE "\U0001FA9D"

#define U_CHAR_HEAD "\U0001F920"
#define U_CHAR_LHAND "\U0001FAF5"
#define U_CHAR_TORSO "\U0001F454"
#define U_CHAR_RHAND "\U0001F595"
#define U_CHAR_LEGS "\U0001F456"
#define U_CHAR_LFOOT "\U0001F45E"
#define U_CHAR_RFOOT "\U0001F45E"

char word[WORD_SZ];
char mask[WORD_SZ + 1]; // Account for null terminator \0
char input_history[WORD_SZ];

typedef struct {
	bool head;
	bool hand_l;
	bool torso;
	bool hand_r;
	bool foot_l;
	bool foot_r;
} t_character;

int main(void)
{
	/** Config */
	SetConsoleOutputCP(65001); // Set console to UTF-8

	/** Initialize */
	bool game_is_over = false;
	bool has_won = false;
	int input_history_count = 0;
	int num_errors = 0;
	int input_char = 10;
	char upper_char;
	t_character character;

	/** debug: initialize to 1 */
	memcpy(word, "AMENDOIM", sizeof(char) * WORD_SZ);
	memset(&mask, '_', (sizeof(char)) * WORD_SZ);
	mask[WORD_SZ + 1] = '\0';
	memset(&input_history, ' ', WORD_SZ);
	memset(&character, 0, sizeof(t_character));

	bool is_running = true;

	system("cls");
	while (is_running) {

		/** DRAW */
		printf("      FORCA \n    %s\n", mask);

		printf("%s", U_VPOLE);
		printf("%s%s", U_HPOLE, U_HPOLE, U_HPOLE);
		printf("%s\n", U_VPOLE);

		printf("%s", U_VPOLE);
		printf("    %s\n", U_ROPE);

		printf("%s", U_VPOLE);
		printf("    %s\n", character.head ? U_CHAR_HEAD : "");

		printf("%s", U_VPOLE);
		/** Opt for multi-string format due to being the simplest way to keep the characters aligned in a single line */
		printf("  %s%s%s\n", (character.hand_l ? U_CHAR_LHAND : ""), (character.torso ? U_CHAR_TORSO : ""), (character.hand_r ? U_CHAR_RHAND : ""));

		printf("%s", U_VPOLE);
		printf("    %s\n", (character.foot_l || character.foot_r) ? U_CHAR_LEGS : "");

		printf("%s", U_VPOLE);
		printf("   %s%s\n", (character.foot_l ? U_CHAR_LFOOT : ""), character.foot_r ? U_CHAR_RFOOT : "");

		/** UPDATE  */

		printf("%s\n", "______________________________");

		printf("HISTORICO:  ", input_history);
		for (int i = 0; i < input_history_count; i++) {
			printf(" %c", input_history[i]);
		}
		printf("\n", input_history);

		printf("ERROS: %i/6\n", num_errors);

		if (game_is_over){
			printf("%s\n", "______________________________");
			// TODO: Draw cake from Portal
			if (has_won) {
				printf("PARABENS!!\n");
			}
			else {
				printf("VOCE MATOU O COWBOY!!\n");
			}

			printf("Pressione qualquer tecla para sair...\n");
			getch();
			is_running = false;
		}

		/** Processing and update */
		printf("Insira uma letra: ");

		/** TODO: Add guard to catch multiple char inputs */
		input_char = getchar();
		upper_char = (char)toupper(input_char);

		/** INPUT PROCESSING */
		// if(upper_char == KEY_ESC)
		// 	is_running = false;

		if (upper_char != 10) {
			input_history[input_history_count] = upper_char;
			input_history_count++;

			int char_index = -1;
			for (size_t i = 0; i < WORD_SZ; i++)
			{
				if(word[i] == upper_char)
				{
					char_index = i;
					mask[char_index] = upper_char;
				}
			}

			char remaining_count = 0;
			for (size_t i = 0; i < WORD_SZ; i++)
			{
				if(mask[i] == '_')
					remaining_count++;
			}

			if (remaining_count == 0)
				has_won = true;

			// No match found
			if(char_index == -1)
				num_errors++;

			if (has_won || (num_errors >= MAX_ATTEMPTS))
					game_is_over = true;
		}

		character.head = (num_errors >= 1);

		character.hand_l = (num_errors >= 2);
		character.torso = (num_errors >= 3);
		character.hand_r = (num_errors >= 4);

		character.foot_l = (num_errors >= 5);
		character.foot_r = (num_errors >= 6);

		system("cls");
	}
}