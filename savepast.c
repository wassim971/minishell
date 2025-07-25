// t_cmd	tokenisation(t_mini base)
// {

// }

void	replace(t_mini *base, int start, int end, char *expend)
{
	char	*new_input;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_input = malloc(sizeof(char) * (ft_strlen(base->input) - (end - start
					- 1) + ft_strlen(expend)));
	while (i != start - 1)
	{
		new_input[i] = base->input[i];
		i++;
	}
	while (expend && expend[j] != '\0')
	{
		new_input[i] = expend[j];
		i++;
		j++;
	}
	base->index = i;
	j = end;
	while (base->input[j])
	{
		new_input[i] = base->input[j];
		i++;
		j++;
	}
	new_input[i] = '\0';
	free(base->input);
	base->input = new_input;
}

char	*get_exp(char *cmd, t_mini base, int len)
{
	char	*expend;
	int		i;

	i = 0;
	if (!cmd)
		return (NULL);
	while (base.env[i] && ft_strnstr(base.env[i], cmd, len) == 0)
		i++;
	if (!base.env[i])
		return (NULL);
	expend = ft_strdup(base.env[i] + (len + 1));
	free(cmd);
	return (expend);
}

char	*ft_strndup_range(const char *s, int start, int end)
{
	int		len;
	char	*sub;
	int		i;

	if (!s || start < 0 || end < start)
		return (NULL);
	len = end - start;
	sub = malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	i = 0;
	while (start < end && s[start])
		sub[i++] = s[start++];
	sub[i] = '\0';
	return (sub);
}

int	parsexp(t_mini *base, int i)
{
	int		start;
	char	*expend;

	start = i;
	if (base->input[i] == '\'')
		return (i - 1);
	while (ft_isalnum(base->input[i]) || base->input[i] == '_')
		i++;
	if (start == i)
		return (i - 1);
	expend = NULL; // ft_strndup_range(base->input, start, i);
	expend = get_exp(expend, *base, (i - start));
	replace(base, start, i, expend);
	i = base->index - 1;
	return (i);
}

int	parsdq(t_mini *base, int i)
{
	while (base->input[i] && base->input[i] != '"')
	{
		if (base->input[i] == '$')
			i = parsexp(base, ++i);
		i++;
	}
	if (base->input[i] == '\0')
		return (0);
	return (i);
}
int	parsq(t_mini *base, int i)
{
	while (base->input[i] && base->input[i] != '\'')
		i++;
	if (base->input[i] == '\0')
		return (0);
	return (i);
}

void	parsing(t_mini *base)
{
	int i;

	i = 0;
	while (base->input[i])
	{
		if (base->input[i] == '"')
		{
			i = parsdq(base, ++i);
			if (i == 0)
			{
				printf("quote non fermer\n");
				return ;
			}
		}
		if (base->input[i] == '\'')
		{
			i = parsq(base, ++i);
			if (i == 0)
			{
				printf("quote non fermer\n");
				return ;
			}
		}
		if (base->input[i] == '$')
			i = parsexp(base, ++i);
		i++;
	}
	// tokenisation(base);
	printf("%s\n", base->input);
}