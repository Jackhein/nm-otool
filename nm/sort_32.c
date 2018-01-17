/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_32.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 17:05:59 by ademenet          #+#    #+#             */
/*   Updated: 2018/01/17 12:27:48 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/ft_nm.h"

static int					init_sort_32(struct nlist *array,
							struct nlist **sort, int nsyms)
{
	int						i;

	i = -1;
	if (!((*sort) = (struct nlist *)malloc(nsyms * sizeof(struct nlist))))
		return (EXIT_FAILURE);
	while (++i < nsyms)
	{
		if (check(&(array[i])))
			return (EXIT_FAILURE);
		(*sort)[i] = array[i];
	}
	return (EXIT_SUCCESS);
}

static void					swap_values_32(struct nlist *sort_i,
							struct nlist *sort_j)
{
	struct nlist			temp;

	temp = *sort_i;
	*sort_i = *sort_j;
	*sort_j = temp;
}

int							sort_value_32(char *stringtable, struct nlist *sort,
							int nsyms)
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
				swap_values_32(&(sort[i]), &(sort[j]));
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int							sort_32(char *stringtable, struct nlist **array,
							int nsyms)
{
	int						i;
	int						j;
	struct nlist			*sort;

	i = -1;
	if (init_sort_32((*array), &sort, nsyms))
		return (EXIT_FAILURE);
	while (++i < nsyms)
	{
		if (g_env.bonus == 1)
			break ;
		j = -1;
		while (++j < nsyms)
		{
			if (check(stringtable + sort[i].n_un.n_strx) ||
				check(stringtable + sort[j].n_un.n_strx))
				return (EXIT_FAILURE);
			if (ft_strcmp(stringtable + sort[i].n_un.n_strx,
			stringtable + sort[j].n_un.n_strx) < 0)
				swap_values_32(&(sort[i]), &(sort[j]));
		}
	}
	(*array) = sort;
	return (EXIT_SUCCESS);
}
