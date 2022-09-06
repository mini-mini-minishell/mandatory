#include "../includes/minishell.h"

int	isname(char *target)
{
	int		isname;
	size_t	i;

	isname = 0;
	if (target)
	{
		isname = (ft_isalpha(target[0]) || (target[0] == '_'));
		i = 0;
		while (target[i] && target[i] != '=' && isname)
		{
			isname = (ft_isalnum(target[i]) || target[i] == '_');
			++i;
		}
	}
	return (isname);
} // 이름이 될수있는지? 알파벳혹은 언더바로 시작해야하며 '='가 안들어가있는지?
// 첫글자는 알파벳이나 언더바, 그다음부터는 숫자, 알파벳, 언더바 모두 가능.
// '='전까지만 검사하고 =이후에는 알파벳, 숫자, 언더바가 안와도 되므로 끝.

size_t	isname_get_length(char *target)
{
	int		isname;
	size_t	i;

	isname = 0;
	if (target)
	{
		isname = (ft_isalpha(target[0]) || (target[0] == '_'));
		i = 0;
		while (target[i] && target[i] != '=' && isname)
		{
			++i;
			isname = (ft_isalnum(target[i]) || target[i] == '_');
		}
	}
	return (i);
} // 리턴이 0이면 타겟이 네임이 될수없으며 네임이라면 길이를 리턴해줌.
