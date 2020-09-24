#include "cub.h"

static bool	check_word(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (true);
	while (str[i] == ' ')
		i++;
	if (!str[i])
		return (false);
	while (ft_isdigit(str[i]))
		i++;
	while (str[i] == ' ')
		i++;
	if (!str[i])
		return (true);
	return (false);
}

static bool conv_rgb_int(char **tab, int *final_rgb)
{
	int	i;
	int	j;
	int	k;
	int	number;

	i = 0;
	k = 23;
	while (tab[i])
	{
		number = ft_atoi(tab[i++]);
		if (number > 255 || !check_word(tab[i - 1]))
			return (false);
		j = 7;
		while (j >= 0)
		{
			*final_rgb += (number / (int)pow(2, j)) * pow(2, k--);
			number = number % (int)pow(2, j--);
		}
	}
	if (i != 3)
		return (false);
	return (true);
}

static int cpy_rgb(int *rgb, char *str)
{
	bool	ret;
	int		i;
	char  	**tab;

	tab = NULL;
	while (str[0] == ' ')
		str++;
	if (!(tab = ft_split(str, ',')))
		return (-1);
	ret = conv_rgb_int(tab, rgb);
	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
	return (ret);
}

bool		cub_store_rgb(char *word, char *line, t_params *params, t_pars_tool *tool)
{
	int	i;

	i = ft_strlen(word);
	if (!ft_strncmp(word, "F", 2))
	{
		if (tool->floor == true)
			return (false);
		tool->floor = true;
		return (cpy_rgb(&params->floor_rgb, line + i));
	}
	else if (!ft_strncmp(word, "C", 2))
	{
		if (tool->ceiling == true)
			return (false);
		tool->ceiling = true;
		return (cpy_rgb(&params->ceiling_rgb, line + i));
	}
	return (true);
}