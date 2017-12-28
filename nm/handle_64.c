/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 15:50:23 by ademenet          #+#    #+#             */
/*   Updated: 2017/12/28 14:54:10 by ademenet         ###   ########.fr       */
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

void					handle_64(char *ptr)
{
	int						i;
	int						ncmds; // je pourrais supprimer cette var
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct symtab_command	*sym;

	i = 0;
	header = (struct mach_header_64 *)ptr;
	ncmds = header->ncmds;
	lc = (void *)ptr + sizeof(*header);
	while (++i < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			print_output_64(sym->nsyms, sym->symoff, sym->stroff, ptr);
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
