/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 11:57:44 by psimarro          #+#    #+#             */
/*   Updated: 2023/10/15 12:06:37 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	ft_error(char *s, t_mshell *mshell, int exit_code)
{
	mshell->error = 1;
	if (mshell)
		mshell->exit_status = exit_code;
	if (s)
		ft_putstr_fd(s, 1);
}

int	check_comillas(char c, const char *s, int i)
{
	int	j;

	if (s[i] != c)
		return (0);
	j = i + 1;
	while (s[j] && s[j] != c)
		j++;
	if (s[j] == c)
		return (j - i);
	return (0);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*joinstr;
	int		len;

	len = ft_strlen(s1) + ft_strlen(s2);
	if (len == 0)
		return (NULL);
	joinstr = ft_calloc(sizeof(char), len + 1);
	if (!joinstr)
		return (0);
	ft_strlcpy(joinstr, s1, ft_strlen(s1) + 1);
	if (s2)
	{
		ft_strlcat(joinstr, s2, len + 1);
		free(s2);
	}
	if (s1)
		free(s1);
	return (joinstr);
}
