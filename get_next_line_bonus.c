#include "get_next_line_bonus.h"
#include <unistd.h>

char	*ft_read_to_static(int fd, char *static_str)
{
	char	*buff;
	int		rd_bytes;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	rd_bytes = 1;
	while (!ft_strchr(static_str, '\n') && rd_bytes != 0)
	{
		rd_bytes = read(fd, buff, BUFFER_SIZE);
		if (rd_bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[rd_bytes] = '\0';
		static_str = ft_strjoin(static_str, buff);
	}
	free(buff);
	return (static_str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*static_str[4096];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	static_str[fd] = ft_read_to_static(fd, static_str[fd]);
	if (!static_str[fd])
		return (NULL);
	line = ft_get_line(static_str[fd]);
	static_str[fd] = ft_new_left_str(static_str[fd]);
	return (line);
}
