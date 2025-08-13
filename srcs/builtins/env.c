#include "../../inc/minishell.h"

int	ft_env(t_data *data, t_cmd *cmd)
{
	t_mini_list	*tmp;

	(void)cmd;
	tmp = data->env;
	while (tmp)
	{
		if (tmp->str && ft_strchr(tmp->str, '='))
			printf("%s\n", tmp->str);
		tmp = tmp->next;
	}
	return (0);
}
