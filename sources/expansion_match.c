#include "../includes/minishell.h"

static int	maybe_match(char *name, char c, t_glob_index *idx)
{
	if (c == '\001')
	{
		idx->pattern_fallback = idx->pattern_idx;
		idx->name_fallback = idx->name_idx + 1;
		idx->pattern_idx++;
		return (1);
	}
	else
	{
		if (idx->name_idx < ft_strlen(name)
			&& (c == '?' || name[idx->name_idx] == c))
		{
			idx->pattern_idx++;
			(idx->name_idx)++;
			return (1);
		}
	}
	return (0);
}

static void	init_idx(t_glob_index *idx)
{
	idx->name_idx = 0;
	idx->pattern_idx = 0;
	idx->name_fallback = 0;
	idx->pattern_fallback = 0;
}

int	match(char *pattern, char *name)
{
	char			c;
	t_glob_index	idx;

	init_idx(&idx);
	if (pattern)
	{
		while (idx.pattern_idx < ft_strlen(pattern) || \
				idx.name_idx < ft_strlen(name))
		{
			if (idx.pattern_idx < ft_strlen(pattern))
			{ // *이나 ?일경우 뭔가 함
				c = pattern[idx.pattern_idx];
				if (maybe_match(name, c, &idx) == 1)
					continue ;
			}
			if (0 < idx.name_fallback && idx.name_fallback <= ft_strlen(name))
			{ // 평범한애들
				idx.pattern_idx = idx.pattern_fallback;
				idx.name_idx = idx.name_fallback;
				continue ;
			}
			return (0);
		}
	}
	return (1);
}
