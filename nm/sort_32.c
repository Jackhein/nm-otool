/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_32.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 17:05:59 by ademenet          #+#    #+#             */
/*   Updated: 2018/01/10 16:57:54 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/ft_nm.h"

static int					init_sort_32(struct nlist *array,
							struct nlist *sort, int nsyms)
{
	int						i;

	i = -1;
	sort = (struct nlist *)malloc(nsyms * sizeof(struct nlist));
	while (++i < nsyms)
	{
		if (check(&array[i]))
			return (set_type_error("7 File truncated or someway invalid."));
		sort[i] = array[i];
	}
	return (EXIT_SUCCESS);
}

static void					do_sorting_32(char *stringtable,
							struct nlist sort_i, struct nlist sort_j)
{
	struct nlist			temp;

	if (ft_strcmp(stringtable + sort_i.n_un.n_strx,
	stringtable + sort_j.n_un.n_strx) < 0)
	{
		temp = sort_i;
		sort_i = sort_j;
		sort_j = temp;
	}
	return ;
}

int							sort_value_32(char *stringtable,
							struct nlist *sort, int nsyms)
{
	int						i;
	int						j;
	struct nlist			temp;

	i = 0;
	while (i < nsyms - 1)
	{
		j = i + 1;
		while (ft_strcmp(stringtable + sort[i].n_un.n_strx,
			stringtable + sort[j].n_un.n_strx) == 0)
		{
			if (sort[i].n_value > sort[j].n_value &&
				(sort[i].n_value != 0 || sort[j].n_value != 0))
			{
				temp = sort[j];
				sort[j] = sort[i];
				sort[i] = temp;
			}
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int							sort_32(char *stringtable, struct nlist *array,
							int nsyms)
{
	int						i;
	int						j;
	struct nlist			*sort;

	i = -1;
	sort = NULL;
	if (init_sort_32(array, sort, nsyms) || check(stringtable))
		return (set_type_error("8 File truncated or someway invalid."));
	while (++i < nsyms)
	{
		j = -1;
		while (++j < nsyms)
		{
			if (!check(&sort[i]) && !check(&sort[j]) && !check(&sort[i].n_un) &&
				!check(&sort[j].n_un) && !check(&sort[i].n_un.n_strx) &&
				!check(&sort[j].n_un.n_strx) &&
				!check(stringtable + sort[i].n_un.n_strx) &&
				!check(stringtable + sort[j].n_un.n_strx))
				do_sorting_32(stringtable, sort[i], sort[j]);
			else
				return (set_type_error("9 File truncated or someway invalid."));
		}
	}
	return (EXIT_SUCCESS);
}
