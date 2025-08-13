#include "../../inc/minishell.h"

int is_builtin(t_cmd *cmd)
{
    char *name = cmd->cmd_param[0];

    return (strcmp(name, "echo") == 0
         || strcmp(name, "pwd") == 0
         || strcmp(name, "env") == 0
         || strcmp(name, "cd") == 0
         || strcmp(name, "export") == 0
         || strcmp(name, "unset") == 0
         || strcmp(name, "exit") == 0);
}

int run_builtin(t_data *data, t_cmd *cmd)
{
    if (strcmp(cmd->cmd_param[0], "echo") == 0)
        return ft_echo(cmd);
    else if (strcmp(cmd->cmd_param[0], "pwd") == 0)
        return ft_pwd(cmd);
    else if (strcmp(cmd->cmd_param[0], "env") == 0)
        return ft_env(data, cmd);
    else if (strcmp(cmd->cmd_param[0], "cd") == 0)
        return ft_cd();
    else if (strcmp(cmd->cmd_param[0], "export") == 0)
        return ft_export();
    else if (strcmp(cmd->cmd_param[0], "unset") == 0)
        return ft_unset();
    else if (strcmp(cmd->cmd_param[0], "exit") == 0)
        return ft_exit();
    return (1);
}


