#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_all_data	all_data;

	check_arguments(argc, argv);
	init_all(&all_data, envp);
	prompt_loop(&all_data);
	return (0);
}
