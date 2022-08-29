#include "../includes/minishell.h"
#include <stdlib.h>

int	check_one_word(t_cmd *cmd, char *target)
{
	char		*word;
	t_word_data	*data;
	int			return_value;

	data = cmd->content.simple.words->tail->data;
	word = data->word;
	return_value = ft_strncmp(target, word, 2);
	return (return_value);
}

static int	bind_pwd_free_pwdvar(t_cmd *cmd, char *pwdvar, char *key)
{
	int	return_value;

	return_value = EXECUTION_SUCCESS
	if (pwdvar != NULL)
	{
		if (bind_variable(cmd, pwdvar, key) == 0)
		{
			return_value = EXECUTION_FAILURE;
		}
	}
	else if (pwdvar == NULL)
	{
		return_value = 2;
	}
	free(pwdvar);
	return (return_value);
}

static char	*get_cwd_fallback_envlist(char *buf, size_t size, t_cmd *cmd)
{
	char	*pwd;

	pwd = getcwd(buf, size);
	if (pwd == NULL)
	{
		pwd = ft_strdup(ft_find_variable(cmd->env, "PWD"));
	}
	return (pwd);
}

int	bind_cwd_to(char *target, t_cmd *cmd)
{
	int		return_value;
	char	*pwdvar;

	pwdvar = get_cwd_fallback_envlist(NULL, 0, cmd);
	return_value = bind_pwd_free_pwdvar(cmd, pwdvar, target);
	return (return_value);
}
