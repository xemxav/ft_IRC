/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xem <xem@student.42lyon.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 15:38:23 by xem               #+#    #+#             */
/*   Updated: 2020/05/20 15:49:25 by xem              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_irc.h"

int		usage(char *prog_name, char *error)
{
	fprintf(stderr, "Usage :%s %s\n", prog_name, error);
	exit(ERROR);
}
