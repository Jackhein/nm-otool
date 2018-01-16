/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_32.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 15:50:59 by ademenet          #+#    #+#             */
/*   Updated: 2018/01/16 15:46:09 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/ft_otool.h"

static int						display_32(struct section *sec)
{
	uint8_t						*byte;
	uint64_t					i;
	long unsigned int			addr;

	byte = (uint8_t *)(g_env.buff_addr + sec->offset);
	i = 0;
	addr = sec->addr;
	while (i < sec->size)
	{
		if (i == 0 || i % 16 == 0)
		{
			if (i != 0)
				addr += 16;
			ft_printf("%08llx\t", addr);
		}
		display_bytes(*byte);
		if ((++i % 16) == 0 && i < sec->size)
			ft_putstr(" \n");
		else
			ft_putchar(' ');
		byte++;
	}
	if (i > 0)
		ft_putchar('\n');
	return (EXIT_SUCCESS);
}

static int						print_output_32(struct segment_command *seg,
								struct section *sec)
{
	uint32_t					i;

	i = 0;
	while (i < seg->nsects)
	{
		if (ft_strcmp(sec->sectname, SECT_TEXT) == 0 &&
			ft_strcmp(sec->segname, SEG_TEXT) == 0)
		{
			display_sectname(sec->sectname);
			display_32(sec);
		}
		sec = (void *)sec + sizeof(*sec);
		i++;
	}
	return (EXIT_SUCCESS);
}

int								handle_32(char *ptr)
{
	uint32_t					i;
	struct mach_header			*header;
	struct load_command			*lc;
	struct segment_command		*seg;
	struct section				*sec;

	i = -1;
	header = (struct mach_header *)ptr;
	lc = (void *)ptr + sizeof(*header);
	while (++i < header->ncmds)
	{
		if (check(lc))
			return (EXIT_FAILURE);
		if (lc->cmd == LC_SEGMENT)
		{
			seg = (struct segment_command *)lc;
			sec = (struct section *)((void *)seg + sizeof(* seg));
			if (check(seg) || check(sec) ||
				print_output_32(seg, sec))
				return (EXIT_FAILURE);
		}
		lc = (void *)lc + lc->cmdsize;
	}
	return (EXIT_SUCCESS);
}
