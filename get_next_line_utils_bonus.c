#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	if (!str)
		return (0);
	len = 0;
	while (str && str[len])
		len++;
	return (len);
}

char	*ft_strchr(const char *s, int c)
{
	while (s && *s)
	{
		if (*s == (char) c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

/*void	*ft_memchr(const void *s, int c, size_t n)
{
	const char	*aux;
	size_t	i;

	i = 0;
	aux = (const char *)s;
	while (aux[i] && i < n)
	{
		if (aux[i] == (unsigned char) c)
			return ((void *)&aux[i]);
		i++;
	}
	return(NULL);
}*/

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	const char	*aux1 = (const char *)src;
	char		*aux2;

	aux2 = (char *) dest;
	i = 0;
	while (i < n && aux1[i])
	{
		aux2[i] = aux1[i];
		i++;
	}
	return ((void *)aux2);
}

char	*ft_strdup(const char *s)
{
	char	*result;
	size_t	a;

	a = 0;
	if (!s)
		return (NULL);
	result = (char *) malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!result)
		return (NULL);
	while (s[a])
	{
		result[a] = s[a];
		a++;
	}
	result[a] = '\0';
	return (result);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*result;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	result = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!result)
		return (NULL);
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	while (s2[j])
		result[i++] = s2[j++];
	result[i] = '\0';
	return (result);
}
