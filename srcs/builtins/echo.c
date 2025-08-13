#include "../../inc/minishell.h"

int	ft_echo(t_cmd *cmd)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (cmd->cmd_param[i] && cmd->cmd_param[i][0] == '-' &&
		cmd->cmd_param[i][1] == 'n')
	{
		int j;
		while (cmd->cmd_param[i])
		{
			j = 1;
			while (cmd->cmd_param[i][j] == 'n')
				j++;
			if (cmd->cmd_param[i][j] != '\0')
				break;
			newline = 0;
			i++;
		}
	}
	while (cmd->cmd_param[i])
	{
		printf("%s", cmd->cmd_param[i]);
		if (cmd->cmd_param[i + 1])
			printf(" ");
		i++;
	}

	if (newline)
		printf("\n");
	return (0);
}
