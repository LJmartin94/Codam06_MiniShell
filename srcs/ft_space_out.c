/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_space_out.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: limartin <limartin@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/23 16:43:32 by limartin      #+#    #+#                 */
/*   Updated: 2020/10/23 18:55:26 by limartin      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

static	int	ft_is_pad(char const c)
{
	if (c == ' ' || c == '\n' || c == '\r' || \
		c == '\t' || c == '\f' || c == '\v')
		return (1);
	return (0);
}

static	char	**ft_filler(char **res, char const *s, int str_num)
{
	int i;
	int l;

	i = 0;
	str_num = 0;
	l = 0;
	while (s[i] != '\0')
	{
		if (i > 0 && (ft_is_pad(s[i]) != ft_is_pad(s[i - 1])))
		{
			res[str_num][l] = '\0';
			str_num++;
			l = 0;
		}
		res[str_num][l] = s[i];
		i++;
		l++;
	}
	res[str_num] = NULL;
	return (res);
}

static	char	**ft_allocator(char **res, char const *s, int str_num)
{
	int i;
	int l;

	i = 0;
	str_num = 0;
	l = 0;
	while (s[i] != '\0')
	{
		if (i > 0 && (ft_is_pad(s[i]) != ft_is_pad(s[i - 1])))
		{
			res[str_num] = (char *)malloc(sizeof(char) * (l + 1));
			str_num++;
			l = 0;
		}
		i++;
		l++;
	}
	return (res);
}

static	int	ft_strcounter(char const *s)
{
	int i;
	int res;
	int pad;

	i = 0;
	res = 0;
	while (s[i] != '\0')
	{
		pad = ft_is_pad(s[i]);
		if (pad == 1 && s[i] != '\0')
		{
			res++;
			while (ft_is_pad(s[i]) == 1 && s[i] != '\0')
				i++;
		}
		else if (pad == 0 && s[i] != '\0')
		{
			res++;
			while (ft_is_pad(s[i]) == 0 && s[i] != '\0')
				i++;
		}
	}
	return (res);
}

char			**ft_space_out(char const *s)
{
	char	**res;
	int		str_num;

	if (!s)
		return (NULL);
	str_num = ft_strcounter(s);
	res = (char **)malloc(sizeof(char *) * (str_num + 1));
	if (res == NULL)
		return (NULL);
	res = ft_allocator(res, s, str_num);
	res = ft_filler(res, s, str_num);
	return (res);
}

int				main(int argc, char **argv)
{
	if (argc != 2)
		return (0);
	ft_space_out(argv[1]);
	return (0);
}
