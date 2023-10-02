#include "minishell.h"

int is_in_string(char *str, char c, char pos, int k)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		
		if (str[i] == 39)
		{
			
			i++;
			while (str[i] != 39 && str[i] != '\0')
			{
				if (pos == c && i == k)
					return (1);
				i++;
			}
		}
		else if (str[i] == 34)
		{
			
			i++;
			while (str[i] != 34 && str[i] != '\0')
			{
				if (pos == c && i == k)
					return (1);
				i++;
			}
		}
		i++;
	}
	return (0);
}

int	charset_verif(char *str, char c, char d, int i)
{
	if (c == d)
	{
		if (is_in_string(str, c, d, i) != 1)
		{
			return (1);
		}
		else
			return (0);
	}
	return (0);
}

int	wordcount(char *str, char d)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && (charset_verif(str, str[i], d, i) == 1))
			i++;
		if (str[i] != '\0' && charset_verif(str, str[i], d , i)  == 0)
			c++;
		while (str[i] != '\0' && charset_verif(str, str[i], d , i) == 0)
			i++;
	}
	return (c + 1);
}

void	makelengthmalloc(char *str, char **dest, char c)
{
	int	i;
	int	k;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		k = 0;
		while (str[i] != '\0' && charset_verif(str, str[i], c , i) == 1)
			i++;
		while (str[i] != '\0' && charset_verif(str, str[i], c , i) == 0)
		{
			i++;
			k++;
		}
		if (k != 0)
		{
			dest[j] = malloc (sizeof(char) * (k + 1));
			if (!dest[j])
				return ;
		}
		j++;
	}
}

void	wordinput(char *str, char **dest, char c)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && charset_verif(str, str[i], c, i) == 1)
			i++;
		k = 0;
		while (str[i] != '\0' && charset_verif(str, str[i], c, i) == 0)
		{
			dest[j][k] = str[i];
			i++;
			k++;
		}
		if (k != 0)
		{
			dest[j][k] = '\0';
			j++;
		}
	}
	dest[j] = 0;
}

char	**ft_split(const char *s, char c)
{
	char	**dest;
	char *str;
	int i;
	
	str = (char *)s;
	i = 0;
	if (str == 0 && str[0] == '\0')
		return (NULL);
	dest = malloc(sizeof(char *) * wordcount(str,c));
	if (!dest)
		return (NULL);
	makelengthmalloc(str, dest, c);
	wordinput(str, dest, c);
/*	while (dest[i] != 0)
	{
		printf("%s\n", dest[i]);
		i++;
	}*/
	return (dest);
}