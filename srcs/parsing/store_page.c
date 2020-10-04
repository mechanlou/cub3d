#include "cub.h"

static char	**free_stuff(char *str1, char **str2)
{
	int i;

	i = 0;
	free(str1);
	while (str2[i])
		free(str2[i++]);
	free(str2);
	return (NULL);
}

static char	**free_map(char **str, int max)
{
	int i;

	i = 0;
	while (i < max)
		free(str[i++]);
	free(str);
	return (NULL);
}

char		**cub_store_line(char *line, char **map)
{
	int		i;
	char	**new_map;

	i = 0;
	while (map[i])
		i++;
	if (!(new_map = (char **)malloc(sizeof(char *) * (i + 2))))
	{
		free(new_map);
		return (free_map(map, i));
	}
	i = 0;
	while (map[i])
	{
		new_map[i] = map[i];
		i++;
	}
	free(map);
	if (!(new_map[i++] = ft_strdup(line)))
		return (free_map(new_map, i - 1));
	new_map[i] = NULL;
	return (new_map);
}

char		**cub_store_page(int fd)
{
	char	**page;
	char	*line;
	int		ret_gnl;

	if (!(page = (char **)malloc(sizeof(char *))))
		return (NULL);
	page[0] = NULL;
	while ((ret_gnl = get_next_line(fd, &line)) > 0)
	{
		if (!(page = cub_store_line(line, page)))
			return (NULL);
		free(line);
	}
	if (ret_gnl == -1)
		return (free_stuff(line, NULL));
	if (!(page = cub_store_line(line, page)))
		return (free_stuff(line, NULL));
	free(line);
	return (page);
}
