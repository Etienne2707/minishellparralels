#include "minishell.h"

int ft_compare(char *str, char *str2, int size)
{
    int i = 0;
    if (!str)
    {
        return (-1);
    }
    while (str[i] == str2[i] && i < size -1 && str2[i] != '\0' && str[i] != '\0')
            i++;
   // printf("voici str = %d je suis la valeur avant %c apres %c\n", size,str2[i ],  str2[i + 1]);
    if (str2[i + 1] != '=')
        return (-1);
    else
        return (str[i] - str2[i]);
}

char*	ft_strlcpy(char *dest, char *src, unsigned int size)
{
	unsigned int	i;
	unsigned int	l;

	i = 0;
	l = ft_strlen(src);
	while (size != 0 && i < size - 1 && src[i] != 0)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < size)
		dest[i] = '\0';
	return (dest);
}

char *ft_strjoin(char  *s1, char  *s2)
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

char *ft_strnjoin(char  *s1, char  *s2, int c)
{
    size_t i;
    size_t k;
    char *str;

    i = ft_strlen(s1);
    k = ft_strlen(s2) - c;
    str = malloc(sizeof(char) * i + k + 1);
    if (!str)
        return (NULL);
    i = 0;
    k = c;
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


char    *add_space(char *str)
{
    int i;
    int c;
    char *dest;

    i = 0;
    c = 0;
    while (str[i])
    {

        //printf("je suis %d\n", check_in_quote(str, i));
        if ((str[i] == '>' || str[i] == '<') && (check_in_quote(str, i)  == -1))
        {
            i++;
            c++;
        }
        if (str[i] == '>' || str[i] == '<')
            i++;
        i++;
    }

    c *= 2;
    //printf("je suis %d\n",ft_strlen(str) + c + 1 );
    dest = malloc(sizeof(char ) * ft_strlen(str) + c + 1);
    if (!dest)
        return (NULL);
    i = 0;
    c = 0;
    while (str[i] != '\0')
    {
     //    printf("valeur retour %d\n", check_in_quote(str, i));

        if ((str[i] == '<' || str[i] == '>') && (check_in_quote(str, i)  == -1))
            dest[c++] = 32;
        dest[c] = str[i] ;
        if ((str[i] == '<' || str[i] == '>') && str[i + 1] != '>' && str[i + 1] != '>' && (check_in_quote(str, i) == -1))
        {
     //       printf("valeur de retour de check ; %d",check_in_quote(str, str[i]));
            dest[++c] = 32;
        }
        i++;
        c++;
    }
    dest[c] = '\0';
    return (dest);
}