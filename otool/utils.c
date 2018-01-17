/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 15:44:47 by ademenet          #+#    #+#             */
/*   Updated: 2018/01/17 14:46:26 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/ft_otool.h"

int				check(void *ptr)
{
	if (ptr >= g_env.buff_addr && ptr <= (g_env.buff_addr + g_env.buff_size))
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int				error_display(char *error)
{
	ft_printf("ft_otool: %s: %s\n", g_env.file, error);
	return (-1);
}

int				usage(void)
{
	ft_printf("Usage: ./ft_otool [-d] [file ...]\n");
	return (EXIT_SUCCESS);
}

int				is_swap(uint32_t magic)
{
	if (magic == MH_CIGAM || magic == MH_CIGAM_64 || magic == FAT_CIGAM)
		return (1);
	return (0);
}

uint32_t		swap_bytes(uint32_t toswap)
{
	if (!g_env.endianness)
		return (toswap);
	return (((toswap & 0xff) << 24) | (((toswap >> 8) & 0xff) << 16) |
		((toswap >> 16) & 0xff) << 8 | ((toswap >> 24) & 0xff));
}
