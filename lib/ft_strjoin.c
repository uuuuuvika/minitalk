/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vshcherb <vshcherb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 18:18:56 by vshcherb          #+#    #+#             */
/*   Updated: 2023/05/21 00:37:15 by vshcherb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_length;
	size_t	s2_length;
	size_t	total_len;
	char	*join;

	if (!s1 || !s2)
		return (NULL);
	s1_length = ft_strlen(s1);
	s2_length = ft_strlen(s2);
	total_len = s1_length + s2_length;
	join = (char *)malloc((total_len + 1) * sizeof(char));
	if (!join)
		return (NULL);
	ft_memcpy(join, s1, s1_length);
	ft_memcpy(join + s1_length, s2, s2_length);
	join[total_len] = '\0';
	return (join);
}

// int main() {
//     char const *s1 = "Hello";
//     char const *s2 = " potato!";
//     char *joined = ft_strjoin(s1, s2);
//     printf("%s\n", joined);
//     return 0;
// }