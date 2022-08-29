
#include "../includes/minishell.h"

int ft_env(t_all_data *all_data)
{
    print_envp(all_data);
    return (EXECUTION_SUCCESS);
}