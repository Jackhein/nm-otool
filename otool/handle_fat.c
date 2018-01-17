/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/28 12:23:40 by ademenet          #+#    #+#             */
/*   Updated: 2018/01/17 14:50:29 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/ft_otool.h"

static int					handle_fat_bis(struct mach_header_64 **header,
							char *ptr, int offset)
{
	(*header) = (void *)ptr + offset;
	g_env.start = *header;
	if (check(*header))
		return (EXIT_FAILURE);
	otool((char *)(*header));
	return (EXIT_SUCCESS);
}

int							handle_fat(char *ptr)
{
	struct fat_header		*f_header;
	struct fat_arch			*f_arch;
	struct mach_header_64	*header;
	int						offset;
	uint32_t				i;

	f_header = (struct fat_header *)ptr;
	f_arch = (void *)ptr + sizeof(struct fat_header);
	if (check(f_header) || check(f_arch) || check(&(f_arch->offset)))
		return (EXIT_FAILURE);
	offset = swap_bytes(f_arch->offset);
	i = -1;
	while (++i < swap_bytes(f_header->nfat_arch))
	{
		offset = swap_bytes(f_arch->offset);
		header = (struct mach_header_64 *)((void *)ptr + offset);
		if (swap_bytes(f_arch->cputype) == CPU_TYPE_X86_64)
			break ;
		f_arch = (void *)f_arch + sizeof(struct fat_arch);
		if (check(f_arch) || check(f_header))
			return (EXIT_FAILURE);
	}
	return (handle_fat_bis(&header, ptr, offset));
}
