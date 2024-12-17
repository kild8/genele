#include "get_next_line.h"

char *ft_strchr(char *s, int c)
{
    while (*s)
	{
		if (*s == (char)c)
			return (char *)s;
		s++;
	}
    return (c == '\0') ? (char *)s : NULL;
}

void *ft_memcpy(void *dest, const void *src, size_t n)
{
	if (!dest || !src)
		return NULL;
    for (int i = 0; i < n; i++)
        ((unsigned char*)dest)[i] = ((unsigned char*)src)[i];
    return dest;
}

int ft_strlen(const char *s)
{
    int ret = 0;
    while (s && s[ret])
    {
        ret++;
    }
    return (ret);
}

int str_append_mem(char **s1, const char *s2, size_t size2)
{
	if (!s1 || !s2)
		return 0;
    size_t size1 = ft_strlen(*s1);
    char *tmp = malloc(size2 + size1 + 1);
    if (!tmp)
	{
		free(*s1);
		return 0;
	}
	if (*s1)
	{
    	ft_memcpy(tmp, *s1, size1);
		free(*s1);
	}
    ft_memcpy(tmp + size1, s2, size2);
    tmp[size1 + size2] = 0;
    *s1 = tmp;
    return 1;
}

int str_append_str(char **s1, const char *s2)
{
    return str_append_mem(s1, s2, ft_strlen(s2));
}

void *ft_memmove(void *dest, void *src, size_t n)
{
	if (!dest || !src || dest == src)
		return dest;
    if (dest > src)
    {
		while (n-- > 0)
		{
			((unsigned char *)dest)[n] = ((unsigned char *)src)[n];
		}
	}
    else
    {
		for (int i = 0; i < n; i++)
        ((unsigned char*)dest)[i] = ((unsigned char*)src)[i];
    }
    return dest;
}

char *get_next_line(int fd)
{
    static char *b;
    char *ret = NULL;
    char *tmp;
	int read_ret;

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