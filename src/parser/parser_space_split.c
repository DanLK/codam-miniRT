/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   parser_split.c                                      :+:    :+:           */
/*                                                      +:+                   */
/*   By: hogu <hogu@student.codam.nl>                  +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/08/13 11:24:50 by hogu           #+#    #+#                */
/*   Updated: 2025/08/13 11:24:51 by hogu           ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static int	count_words(char const *s)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && ft_isspace(s[i]))
			i++;
		if (s[i])
		{
			count++;
			while (s[i] && !ft_isspace(s[i]))
				i++;
		}
	}
	return (count);
}

static	int	word_len(char const *s)
{
	int	current_len;

	current_len = 0;
	while (*(s + current_len) && !ft_isspace(*(s + current_len)))
		current_len++;
	return (current_len);
}

static char	*allocate_and_copy(char const *s, int len)
{
	char	*word;
	int		i;

	i = 0;
	word = (char *)malloc((len + 1) * sizeof(char));
	if (!word)
		return (word);
	while (len > 0)
	{
		word[i] = *(s + i);
		i++;
		len--;
	}
	word[i] = '\0';
	return (word);
}

char	**space_split(char const *s)
{
	char	**result;
	int		index_word;
	int		current_len;

	if (!s)
		return (NULL);
	result = (char **)malloc((count_words(s) + 1) * sizeof(char *));
	if (!result)
		return (result);
	index_word = 0;
	while (*s)
	{
		while (ft_isspace(*s))
			s++;
		if (!*s)
			break ;
		current_len = word_len(s);
		result[index_word] = allocate_and_copy(s, current_len);
		if (!result[index_word])
			return (free_split(result), NULL);
		s += current_len;
		index_word++;
	}
	result[index_word] = NULL;
	return (result);
}
