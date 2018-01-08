/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 12:23:40 by ademenet          #+#    #+#             */
/*   Updated: 2018/01/08 10:55:14 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/ft_nm.h"

uint32_t		swap_bytes(uint32_t toswap)
{
	return (((toswap & 0xff) << 24) | (((toswap >> 8) & 0xff) << 16) |
		((toswap >> 16) & 0xff) << 8 | ((toswap >> 24) & 0xff));
}

void			handle_fat(char *ptr)
{
	struct fat_header		*f_header;
	struct fat_arch			*f_arch;
	struct mach_header_64	*header;
	int						i;

	f_header = (struct fat_header *)ptr;
	f_arch = (void *)ptr + sizeof(struct fat_header);
	i = -1;
	while (++i < swap_bytes(f_header->nfat_arch))
	{
		header = (struct mach_header_64 *)((void *)ptr +
			swap_bytes(f_arch->offset));
		if (swap_bytes(f_arch->cputype) == CPU_TYPE_X86_64)
			break ;
		f_arch = (void *)f_arch + sizeof(struct fat_arch);
	}
	header = (void *)ptr + swap_bytes(f_arch->offset);
	nm((char *)header);
	return ;
}
