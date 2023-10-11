/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: educlos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:49:58 by educlos           #+#    #+#             */
/*   Updated: 2022/11/15 15:36:57 by educlos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

    int isset(char c, char const *set)
    {
        int i;

        i = 0;
        while (set[i] != '\0')
        {
            if (set[i] == c)
                return (1);
            i++;
        }
        return (0);
    }

    char    *ft_strtrim(char const *s1, char const *set)
    {
        int i;
        int j;
        int len;
        char *tab;

        j = 0;
        len = 0;
        while (s1[len] != '\0')
            len++;     
        i = 0;
        while (isset(s1[i], set))
            i++;
        while (isset(s1[len - 1], set))
            len--;
        if ((len - i + 1) <= 0)
        {
            i = 1;
            len = 1;
        }   
        tab = malloc(sizeof(char) * (len - i + 1));
        if (!tab)
            return (NULL);
        while (i < len)
            tab[j++] = s1[i++];
        tab[j] = 0;
        return (tab);
    }