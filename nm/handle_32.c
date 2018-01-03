/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_32.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 15:50:59 by ademenet          #+#    #+#             */
/*   Updated: 2018/01/03 18:24:35 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/ft_nm.h"

void							get_symtab_sec_32(t_sym *symtab,
								struct segment_command *seg,
								struct section *sec, int *k)
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

void							get_symtab_32(t_sym *symtab,
								struct mach_header *header,
								struct load_command *lc)
{
	int							i;
	int							k;
	struct segment_command		*seg;
	struct section				*sec;

	i = -1;
	k = 0;
	while (++i < header->ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
		{
			seg = (struct segment_command *)lc;
			sec = (struct section *)((void *)seg +
				sizeof(struct segment_command_64));
			get_symtab_sec_32(symtab, seg, sec, &k);
		}
		lc = (void *)lc + lc->cmdsize;
	}
	return ;
}

void							print_output_32(struct symtab_command *sym,
								t_sym *symtab, char *ptr)
{
	int							i;
	char						*stringtable;
	struct nlist				*array;

	i = -1;
	stringtable = (void *)ptr + sym->stroff;
	array = (void *)ptr + sym->symoff;
	array = sort_32(stringtable, array, sym->nsyms);
	sort_value_32(stringtable, array, sym->nsyms);
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

void							handle_32(char *ptr)
{
	int							i;
	struct mach_header			*header;
	struct load_command			*lc;
	struct symtab_command		*sym;
	t_sym						symtab;

	i = -1;
	header = (struct mach_header *)ptr;
	lc = (void *)ptr + sizeof(*header);
	get_symtab_32(&symtab, header, lc);
	while (++i < header->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			print_output_32(sym, &symtab, ptr);
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
