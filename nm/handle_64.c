/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 15:50:23 by ademenet          #+#    #+#             */
/*   Updated: 2018/01/03 17:45:27 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/ft_nm.h"

int								check_addr_error(struct load_command *lc)
{
	return (0);
}

void							get_symtab_sec(t_sym *symtab,
								struct segment_command_64 *seg,
								struct section_64 *sec, int *k)
{
	int							j;

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
		(*k)++;
	}
	return ;
}

void							get_symtab(t_sym *symtab,
								struct mach_header_64 *header,
								struct load_command *lc)
{
	int							i;
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
			get_symtab_sec(symtab, seg, sec, &k);
		}
		lc = (void *)lc + lc->cmdsize;
	}
	return ;
}

void							print_output_64(struct symtab_command *sym,
								t_sym *symtab, char *ptr)
{
	int							i;
	char						*stringtable;
	struct nlist_64				*array;

	i = -1;
	stringtable = (void *)ptr + sym->stroff;
	array = (void *)ptr + sym->symoff;
	array = sort_64(stringtable, array, sym->nsyms);
	sort_value_64(stringtable, array, sym->nsyms);
	while (++i < sym->nsyms)
	{
		if (array[i].n_value == 0)
			ft_printf("%16c ", ' ');
		else
			ft_printf("%016llx ", array[i].n_value);
		ft_printf("%c ", get_type(array[i].n_type, array[i].n_sect,
			array[i].n_value, symtab));
		ft_printf("%s\n", stringtable + array[i].n_un.n_strx);
	}
}

void							handle_64(char *ptr)
{
	int							i;
	struct mach_header_64		*header;
	struct load_command			*lc;
	struct symtab_command		*sym;
	t_sym						symtab;

	i = -1;
	header = (struct mach_header_64 *)ptr;
	lc = (void *)ptr + sizeof(*header);
	get_symtab(&symtab, header, lc);
	while (++i < header->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			print_output_64(sym, &symtab, ptr);
			break ;
		}
		lc = (void *)lc + lc->cmdsize;
		if (check_addr_error(lc))
		{
			error_display("Invalid file.");
			return ;
		}
	}
}
