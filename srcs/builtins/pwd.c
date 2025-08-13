#include "../../inc/minishell.h"

int	ft_pwd(t_cmd *cmd)
{
	char	str[PATH_MAX];

	(void)cmd;
	if (getcwd(str, PATH_MAX))
		printf("%s\n", str);
	else
		perror("pwd");
	return (0);
}
