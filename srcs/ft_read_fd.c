#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define BUF_SIZE 16

int		ft_strlen(const char *str)
{
	int i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strnew(size_t size)
{
	char *s;

	s = (char *)malloc(sizeof(char) * (size + 1));
	return (s);
}

char	*ft_strcpy(char *dst, const char *src)
{
	int i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strcat(char *s1, const char *s2)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	while (s2[j])
	{
		s1[i + j] = s2[j];
		j++;
	}
	s1[i + j] = '\0';
	return (s1);
}

char	*ft_strdup(const char *s1)
{
	char	*str;
	int		i;

	i = 0;
	if (s1 == NULL)
		return (NULL);
	str = ft_strnew(ft_strlen(s1));
	if (str == NULL)
		return (NULL);
	ft_strcpy(str, s1);
	return (str);
}

char	*ft_strjoin_del(char *s1, char const *s2)
{
	char	*p;

	if (s1 == NULL && s2 == NULL)
		return NULL;
	else if (s1 == NULL)
		return (ft_strdup(s2));
	else if (s2 == NULL)
		return (s1);
	else
	{
		p = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
		if (p == NULL)
			return (NULL);
		ft_strcpy(p, s1);
		ft_strcat(p, s2);
		free((void *)s1);
		return (p);
	}
}

char	*ft_read_fd(int fd)
{
	char	*buf;
	char	tmp[BUF_SIZE + 1];
	int		ret = 0;

	buf = NULL;
	while ((ret = read(fd, tmp, BUF_SIZE)) > 0)
	{
		buf = ft_strjoin_del(buf, tmp);
	}
	if (ret < 0)
	{
		//error during reading
		printf("is a directory\n");
		return NULL;
	}
	return (buf);
}

char	*ft_read_file(char *filename)
{
	char	*buf;
	int		fd;

	if ((fd = open(filename, O_RDONLY)) == -1)
	{
		//no such file or directory
		//TODO verifier si c'est un dossier
		printf("no such file or directory : %s\n", filename);
		return (NULL);
	}
	buf = ft_read_fd(fd);
	close(fd);
	return (buf);
}

int main(int ac, char **av)
{
	int i = 1;
	if (ac == 1)
	{
		printf("%s\n", ft_read_fd(STDIN_FILENO));
	}
	else
	{	
		while (i < ac)
		{
			printf("%s\n", ft_read_file(av[i]));
			i++;
		}
	}
	return 0;
}
