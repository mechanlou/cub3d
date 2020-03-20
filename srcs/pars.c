#include "../includes/cub.h"

bool cub_extension(char *file)
{
	int i;

	i = 0;
	while (file[i] != '.')
	{
		if (file[i] == '\0')
			return (false);
		i++;
	}
	if (ft_strncmp(file + ++i, "cub", 4))
		return (false);
	return (true);	
}

bool cub_pars(char *file)
{
	if (!cub_extension(file))
	{
		dprintf(1, "extension cassée batard\n");
		return (false);
	}
	return (true);
}