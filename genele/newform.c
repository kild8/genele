char *get_next_line(int fd)
{
	static char *b;
	char *ret = NULL;
	int read_ret;
	char *tmp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return NULL;

	if (!b)
	{
		b = malloc(BUFFER_SIZE + 1);
		if (!b)
			return NULL;
		b[0] = '\0';
	}
	while (1)
	{
		if ((tmp = ft_strchr(b, '\n')))
		{
			if (!str_append_mem(&ret, b, tmp - b + 1))
			{
				free(b);
				free(ret);
				return NULL;
			}
			ft_memmove(b, tmp + 1, ft_strlen(tmp + 1) + 1);
			return ret;
		}
		if (!str_append_str(&ret, b))
		{
			free(b);
			return NULL;
		}
		read_ret = read(fd, b, BUFFER_SIZE);
		if (read_ret <= 0)
		{
			free(b);
			b = NULL;
			if (!ret || !*ret)
			{
				free(ret);
				return NULL;
			}
			return ret;
		}
		b[read_ret] = '\0';
	}
}