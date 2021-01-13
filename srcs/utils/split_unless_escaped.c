/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split_unless_escaped.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jsaariko <jsaariko@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/17 14:15:10 by jsaariko      #+#    #+#                 */
/*   Updated: 2021/01/13 19:30:27 by jsaariko      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "execute.h"

static int	quotes(int *quote, int *d_quote, char c)
{
	if (c == '"')
	{
		if (*quote % 2 == 0)
			(*d_quote)++;
		else
			(*d_quote)--;
	}
	else if (c == '\'')
	{
		if (*d_quote % 2 == 0)
			(*quote)++;
		else
			(*quote)--;
	}
	if (*d_quote % 2 == 0 && *quote % 2 == 0)
		return (0);
	else
		return (1);
}

static int	find_split(char const *s, char c, int end, int bool)
{
	int i;
	int quote;
	int d_quote;
	int within;

	i = end;
	quote = 0;
	d_quote = 0;
	if (bool == 0)
	{
		while (s[i] == c && s[i] != '\0')
			i++;
	}
	else if (bool == 1)
	{
		while (s[i] != '\0')
		{
			within = quotes(&quote, &d_quote, s[i]);
			if (s[i] == c && within == 0 && i - 1 >= 0 && s[i - 1] != '\\')
				return (i);
			i++;
		}
	}
	return (i);
}

static int	str_amt(char const *s, char c)
{
	int i;
	int amt;

	i = 0;
	amt = 0;
	while (s[i] != '\0')
	{
		if (s[i + 1] == c || s[i + 1] == '\0')
		{
			amt++;
		}
		i++;
	}
	return (amt);
}

static char	**allocate_arr(char const *s, char c, int amt, char **arr)
{
	int start;
	int end;
	int i;

	start = 0;
	end = 0;
	i = 0;
	while (i < amt)
	{
		start = find_split(s, c, end, 0);
		end = find_split(s, c, start, 1);
		arr[i] = ft_substr(s, start, (end + 1 - start));
		if (arr[i] == NULL)
		{
			free_matrix(arr);
			return (NULL);
		}
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

char		**split_unless_quote(char const *s, char c)
{
	char	**arr;
	int		amt;

	if (!s)
		return (NULL);
	amt = str_amt(s, c);
	arr = (char **)malloc(((amt + 1) * sizeof(char *)));
	if (arr == NULL)
		return (NULL);
	return (allocate_arr(s, c, amt, arr));
}
