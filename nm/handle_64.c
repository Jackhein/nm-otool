/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 15:50:23 by ademenet          #+#    #+#             */
/*   Updated: 2017/12/29 15:18:42 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/ft_nm.h"

// TODO faire toutes les verifications d'erreur
// TODO faire une liste avec tous les elements a display

int						check_addr_error(struct load_command *lc)
{
	// To be implemented
	return (0);
}

void					sort_value_64(char *stringtable, struct nlist_64 *sort,
						int nsyms)
{
	int						i;
	int						flag;
	struct nlist_64			temp;

	while (++i < nsyms - 1)
	{
		i = -1;
		if (ft_strcmp(stringtable + sort[i].n_un.n_strx,
		stringtable + sort[i].n_un.n_strx) == 0 && 
		(sort[i].n_un.n_strx != 0 || sort[i + 1].n_un.n_strx != 0))
		{
			if (sort[i].n_un.n_strx > sort[i + 1].n_un.n_strx)
			{
				temp = sort[i + 1];
				sort[i + 1] = sort[i];
				sort[i] = temp;
			}
		}
	}
	return ;
}

static struct nlist_64	*init_sort_64(struct nlist_64 *array,
						int nsyms)
{
	int						i;
	struct nlist_64			*sort;
	
	i = -1;
	sort = (struct nlist_64 *)malloc(nsyms * sizeof(struct nlist_64));
	while (++i < nsyms)
		sort[i] = array[i];
	return (sort);
}

struct nlist_64			*sort_64(char *stringtable, struct nlist_64 *array, 
						int nsyms)
{
	int						i;
	int						j;
	struct nlist_64			temp;
	struct nlist_64			*sort;

	i = -1;
	sort = init_sort_64(array, nsyms);
	while (++i < nsyms)
	{
		j = -1;
		while (++j < nsyms)
		{
			if (ft_strcmp(stringtable + sort[i].n_un.n_strx,
			stringtable + sort[j].n_un.n_strx) < 0)
			{
				temp = sort[i];
				sort[i] = sort[j];
				sort[j] = temp;
			}
		}
	}
	return (sort);
}

void				get_symtab(t_sym *symtab, struct mach_header_64 *header,
					struct load_command *lc)
{
	int							i;
	int							j;
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
			j = -1;
			while (++j < seg->nsects)
			{
				if (ft_strcmp(sec->sectname, SECT_TEXT) == 0 && 
					ft_strcmp(sec->segname, SEG_TEXT) == 0)
					symtab->text = k + 1;
				else if (ft_strcmp(sec->sectname, SECT_DATA) == 0 && 
					ft_strcmp(sec->segname, SEG_DATA) == 0)
					symtab->data = k + 1;
				else if (ft_strcmp(sec->sectname, SECT_BSS) == 0 && 
					ft_strcmp(sec->segname, SEG_DATA) == 0)
					symtab->bss = k + 1;
				sec = (void *)sec + sizeof(struct section_64);
				k++;
			}
		}
		lc = (void *)lc + lc->cmdsize;
	}
	return ;
}

void				print_output_64(int nsyms, int symoff, int stroff, 
					t_sym *symtab, char *ptr)
{
	int						i;
    char                    type;
	char					*stringtable;
	struct nlist_64			*array;

	i = -1;
	stringtable = (void *)ptr + stroff;
    array = (void *)ptr + symoff;
	array = sort_64(stringtable, array, nsyms);
	sort_value_64(stringtable, array, nsyms);
    while (++i < nsyms)
	{
		if (array[i].n_value == 0)
			ft_printf("%16c ", ' ');
		else
			ft_printf("%016llx ", array[i].n_value);
        type = get_type(array[i].n_type, array[i].n_sect, array[i].n_value,
			symtab);
		ft_printf("%c ", type);
		ft_printf("%s\n", stringtable + array[i].n_un.n_strx);
	}
}

void					handle_64(char *ptr)
{
	int						i;
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct symtab_command	*sym;
	t_sym					symtab;

	i = -1;
	header = (struct mach_header_64 *)ptr;
	lc = (void *)ptr + sizeof(*header);
	get_symtab(&symtab, header, lc);
	while (++i < header->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			print_output_64(sym->nsyms, sym->symoff, sym->stroff, &symtab, ptr);
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
