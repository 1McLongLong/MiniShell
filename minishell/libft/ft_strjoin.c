/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: touahman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 18:20:50 by touahman          #+#    #+#             */
/*   Updated: 2023/11/04 18:20:58 by touahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	t_len;

	if (!s1 || !s2)
		return (NULL);
	t_len = 1 + ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(t_len * sizeof(char));
	if (str == NULL)
		return (NULL);
	*str = '\0';
	ft_strlcat(str, (char *)s1, t_len);
	ft_strlcat(str, (char *)s2, t_len);
	return (str);
}
*/
char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	t_len;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	t_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = (char *)malloc(t_len * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
		str[i++] = s1[j++];
	j = 0;
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}
