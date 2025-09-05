/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ainthana <ainthana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 16:27:00 by ainthana          #+#    #+#             */
/*   Updated: 2025/09/05 16:29:55 by ainthana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void handle_sigpipe(int sig)
{
    t_data *data;
    (void)sig;
    data = get_data(NULL);
    free_all(data, NULL, 0);
    exit(1);
}
