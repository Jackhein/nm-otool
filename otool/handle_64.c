/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 15:50:23 by ademenet          #+#    #+#             */
/*   Updated: 2018/01/16 12:40:00 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/ft_otool.h"

/*
static int						get_symtab_sec_64(t_sym *symtab,
								struct segment_command_64 *seg,
								struct section_64 *sec, int *k)
{
	uint32_t					j;

	j = -1;
	while (++j < seg->nsects)
	{
		if (ft_strcmp(sec->sectname, SECT_TEXT) == 0 &&
			ft_strcmp(sec->segname, SEG_TEXT) == 0)
			symtab->text = (*k) + 1;
		else if (ft_strcmp(sec->sectname, SECT_DATA) == 0 &&
			ft_strcmp(sec->segname, SEG_DATA) == 0)
			symtab->data = (*k) + 1;
		else if (ft_strcmp(sec->sectname, SECT_BSS) == 0 &&
			ft_strcmp(sec->segname, SEG_DATA) == 0)
			symtab->bss = (*k) + 1;
		sec = (void *)sec + sizeof(struct section_64);
		if (check(sec))
			return (EXIT_FAILURE);
		(*k)++;
	}
	return (EXIT_SUCCESS);
}
*/

/*
static int						output_64(t_sym *symtab,
								struct segment_command_64 *seg,
								struct section_64 *sec, int *k)
{
	uint32_t					j;

	j = -1;
	while (++j < seg->nsects)
	{
		if (ft_strcmp(sec->sectname, SECT_TEXT) == 0 &&
			ft_strcmp(sec->segname, SEG_TEXT) == 0)
			symtab->text = (*k) + 1;
		else if (ft_strcmp(sec->sectname, SECT_DATA) == 0 &&
			ft_strcmp(sec->segname, SEG_DATA) == 0)
			symtab->data = (*k) + 1;
		else if (ft_strcmp(sec->sectname, SECT_BSS) == 0 &&
			ft_strcmp(sec->segname, SEG_DATA) == 0)
			symtab->bss = (*k) + 1;
		sec = (void *)sec + sizeof(struct section_64);
		if (check(sec))
			return (EXIT_FAILURE);
		(*k)++;
	}
	return (EXIT_SUCCESS);
}
*/

/*
static int						get_symtab_64(t_sym *symtab,
								struct mach_header_64 *header,
								struct load_command *lc)
{
	uint32_t					i;
	int							k;
	struct segment_command_64	*seg;
	struct section_64			*sec;

	i = -1;
	k = 0;
	while (++i < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
		{
			seg = (struct segment_command_64 *)lc;
			sec = (struct section_64 *)((void *)seg +
				sizeof(struct segment_command_64));
			if (check(seg) || check(sec) ||
				get_symtab_sec_64(symtab, seg, sec, &k))
				return (EXIT_FAILURE);
		}
		lc = (void *)lc + lc->cmdsize;
		if (check(lc))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
*/

/*
int							display_64(struct symtab_command *sym,
							char *stringtable, struct nlist_64 *array,
							t_sym *symtab)
{
	uint32_t				i;
	char					type;

	i = -1;
	while (++i < sym->nsyms)
	{
		type = get_type(array[i].n_type, array[i].n_sect, array[i].n_value,
			symtab);
		if (ft_strcmp("radr://5614542", stringtable + array[i].n_un.n_strx)
			!= 0 && type != '-')
		{
			if (array[i].n_value == 0 && (type == 'U' || type == 'u'))
				ft_printf("%16c %c %s\n", ' ', type,
					stringtable + array[i].n_un.n_strx);
			else
				ft_printf("%016llx %c %s\n", array[i].n_value, type,
					stringtable + array[i].n_un.n_strx);
		}
	}
	return (EXIT_SUCCESS);
}
*/

static int						display_64(struct section_64 *sec)
{
	uint64_t					i;
	long unsigned int			addr;

	i = 0;
	addr = sec->addr;
	while (i < sec->size)
	{
		if (i == 0 || i % 16 == 0)
		{
			if (i != 0)
				addr += 16;
		}
		// display_bytes();
		i++;
	}
	if (i > 0)
		ft_putchar('\n');
	return (EXIT_SUCCESS);
}

static int						print_output_64(struct segment_command_64 *seg,
								struct section_64 *sec, struct mach_header_64
								*header, char show_filename)
{
	// char						*stringtable;
	// struct nlist_64				*array;

	// stringtable = (void *)ptr + sym->stroff;
	// array = (void *)ptr + sym->symoff;
	// if (check(stringtable) || check(array) || check(&(sym->nsyms)))
		// return (EXIT_FAILURE);
	// if (sort_64(stringtable, &array, sym->nsyms))
		// return (EXIT_FAILURE);
	// if (sort_value_64(stringtable, array, sym->nsyms))
		// return (EXIT_FAILURE);
	// if (display_64(sym, stringtable, array, symtab))
		// return (EXIT_FAILURE);
	// free(array);
	uint32_t					i;

	i = 0;
	if (show_filename)
		ft_printf("%s:\n", g_env.file);
	while (i < seg->nsects)
	{
		if (ft_strcmp(sec->sectname, SECT_TEXT) == 0 &&
			ft_strcmp(sec->segname, SEG_TEXT) == 0)
		{
			ft_printf("(char *)header + sect->offset = %s\n", (char *)header + sec->offset);
			ft_printf("%s\n", sec->sectname);
			display_64(sec);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int								handle_64(char *ptr, char show_filename)
{
	uint32_t					i;
	struct mach_header_64		*header;
	struct load_command			*lc;
	struct segment_command_64	*seg;
	struct section_64			*sec;

	i = -1;
	header = (struct mach_header_64 *)ptr;
	lc = (void *)ptr + sizeof(*header);
	while (++i < header->ncmds)
	{
		if (check(lc))
			return (EXIT_FAILURE);
		if (lc->cmd == LC_SEGMENT_64)
		{
			seg = (struct segment_command_64 *)lc;
			sec = (struct section_64 *)((void *)seg + sizeof(* seg));
			if (check(seg) || check(sec) ||
				print_output_64(seg, sec, header, show_filename))
				return (EXIT_FAILURE);
		}
		lc = (void *)lc + lc->cmdsize;
	}
	return (EXIT_SUCCESS);
}
