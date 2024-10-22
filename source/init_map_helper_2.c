#include "../includes/cub3d.h"

int	setup_file(t_data *d, int *fd, char **line, char *argv)
{
	*fd = open(argv, O_RDONLY);
	if (*fd < 0)
		return (1);
	*line = get_next_line(*fd);
	if (!*line)
	{
		close (*fd);
		return (1);
	}
	if (d != NULL)
	{
		d->file_arr = (char **) ft_calloc((d->y_file + 1), sizeof(char *));
		if (!d->file_arr)
		{
			close (*fd);
			free (*line);
			return (1);
		}
	}
	return (0);
}

void	free_line(char *line, int fd)
{
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
}

int	create_file_array(t_data *d, char *argv)
{
	int		fd;
	int		i;
	char	*line;

	line = NULL;
	if (setup_file(d, &fd, &line, argv) == 1)
		return (free (line), 1);
	i = 0;
	while (line && i < d->y_file)
	{
		d->file_arr[i] = (char *) ft_calloc(ft_strlen(line) + 1, sizeof(char));
		if (!d->file_arr[i])
			return (free_line(line, fd), 1);
		ft_strlcpy(d->file_arr[i], line, ft_strlen(line) + 1);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	d->file_arr[i] = NULL;
	return (close (fd), 0);
}

int	get_dimensions_of_file(t_data *d, char *argv)
{
	int		fd;
	char	*line;
	int		max;
	int		count;

	count = 0;
	max = 0;
	line = NULL;
	if (setup_file(NULL, &fd, &line, argv) == 1)
		return (free(line), 1);
	max = ft_strlen(line);
	while (line != NULL)
	{
		count++;
		free(line);
		line = get_next_line(fd);
		if ((size_t) max < ft_strlen(line))
			max = ft_strlen(line);
	}
	if (max < 3 || count < 1)
		return (close (fd), 1);
	d->y_file = count;
	d->x_file = max;
	return (close(fd), 0);
}
