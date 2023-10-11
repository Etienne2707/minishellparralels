#include "libft.h"

size_t ft_strlen(char const *str)
{
    int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char *ft_strjoin(char const *s1, char const *s2)
{
    size_t i;
    size_t k;
    char *str;

    i = ft_strlen(s1);
    k = ft_strlen(s2);
    str = malloc(sizeof(char) * i + k + 1);
    if (!str)
        return (NULL);
    i = 0;
    k = 0;
    while (s1[i] != '\0')
    {
        str[i] = s1[i];
        i++;

    }
    while (s2[k] != '\0')
    {
        str[i] = s2[k];
        i++;
        k++;
    }
    str[i] = 0;
    return (str);
}