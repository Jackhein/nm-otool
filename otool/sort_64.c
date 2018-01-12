/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_64.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 17:05:59 by ademenet          #+#    #+#             */
/*   Updated: 2018/01/12 17:55:52 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/ft_otool.h"

static int					init_sort_64(struct nlist_64 *array, 
							struct nlist_64 **sort, int nsyms)
{
	int						i;

	i = -1;
	if (!((*sort) = (struct nlist_64 *)malloc(nsyms * sizeof(struct nlist_64))))
		return (EXIT_FAILURE);
	while (++i < nsyms)
	{
		if (check(&(array[i])))
			return (EXIT_FAILURE);
		(*sort)[i] = array[i];
	}
	return (EXIT_SUCCESS);
}

static void					swap_values_64(struct nlist_64 *sort_i,
							struct nlist_64 *sort_j)
{
	struct nlist_64			temp;

	temp = *sort_i;
	*sort_i = *sort_j;
	*sort_j = temp;
}

int							sort_value_64(char *stringtable,
							struct nlist_64 *sort, int nsyms)
{
	int						i;
	int						j;

	i = 0;
	while (i < nsyms - 1)
	{
		j = i + 1;
		if (check(stringtable + sort[i].n_un.n_strx) ||
			check(stringtable + sort[j].n_un.n_strx))
			return (EXIT_FAILURE);
		while (ft_strcmp(stringtable + sort[i].n_un.n_strx,
			stringtable + sort[j].n_un.n_strx) == 0)
		{
			if (sort[i].n_value > sort[j].n_value &&
				(sort[i].n_value != 0 || sort[j].n_value != 0))
				swap_values_64(&(sort[i]), &(sort[j]));
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int							sort_64(char *stringtable, struct nlist_64 **array,
							int nsyms)
{
	int						i;
	int						j;
	struct nlist_64			*sort;

	i = -1;
	if (init_sort_64((*array), &sort, nsyms))
		return (EXIT_FAILURE);
	while (++i < nsyms)
	{
		j = -1;
		while (++j < nsyms)
		{
			if (check(stringtable + sort[i].n_un.n_strx) ||
				check(stringtable + sort[j].n_un.n_strx))
				return (EXIT_FAILURE);
			if (ft_strcmp(stringtable + sort[i].n_un.n_strx,
				stringtable + sort[j].n_un.n_strx) < 0)
				swap_values_64(&(sort[i]), &(sort[j]));
		}
	}
	(*array) = sort;
	return (EXIT_SUCCESS);
}
