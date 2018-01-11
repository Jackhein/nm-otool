/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_32.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 17:05:59 by ademenet          #+#    #+#             */
/*   Updated: 2018/01/09 17:04:32 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/ft_nm.h"

static int					*init_sort_32(struct nlist *array,
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
		sort[i] = array[i];
}
	return (EXIT_SUCCESS);
}

void						sort_value_32(char *stringtable, struct nlist *sort,
							int nsyms)
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
	return ;
}

struct nlist				*sort_32(char *stringtable, struct nlist *array,
							int nsyms)
{
	int						i;
	int						j;
	struct nlist			temp;
	struct nlist			*sort;

	i = -1;
	sort = init_sort_32(array, nsyms);
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
