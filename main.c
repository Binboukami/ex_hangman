#include <stdbool.h>

#include "hangman.h"

int main(void)
{
	bool is_running = true;

	while (is_running) {
		draw_boneco();
		process();
	}
}