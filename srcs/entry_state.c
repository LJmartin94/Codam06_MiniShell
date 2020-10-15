#include "fsm.h"

t_transition_code entry_state(const char *input)
{
	if (input[0] == ' ')
	{
		return (padding);
	}
	else
		return (validate_command(input));
	return (error);
}