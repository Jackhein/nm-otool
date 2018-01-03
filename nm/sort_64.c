/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_64.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 17:05:59 by ademenet          #+#    #+#             */
/*   Updated: 2018/01/03 17:47:42 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/ft_nm.h"

static struct nlist_64		*init_sort_64(struct nlist_64 *array, int nsyms)
{
	int						i;
	struct nlist_64			*sort;

	i = -1;
	sort = (struct nlist_64 *)malloc(nsyms * sizeof(struct nlist_64));
	while (++i < nsyms)
		sort[i] = array[i];
	return (sort);
}

void						sort_value_64(char *stringtable,
							struct nlist_64 *sort, int nsyms)
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

struct nlist_64				*sort_64(char *stringtable, struct nlist_64 *array,
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
