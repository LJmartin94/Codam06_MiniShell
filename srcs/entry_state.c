#include "fsm.h"

void entry_state(const char *input)
{
	if (input[0] == ' ')
	{
		return (padding);
	}
	else
		validate_command(input);
}