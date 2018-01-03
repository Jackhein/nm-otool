/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_32.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademenet <ademenet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 17:05:59 by ademenet          #+#    #+#             */
/*   Updated: 2018/01/03 18:21:43 by ademenet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/ft_nm.h"

static struct nlist			*init_sort_32(struct nlist *array, int nsyms)
{
	int						i;
	struct nlist			*sort;

	i = -1;
	sort = (struct nlist *)malloc(nsyms * sizeof(struct nlist));
	while (++i < nsyms)
		sort[i] = array[i];
	return (sort);
}

void						sort_value_32(char *stringtable, struct nlist *sort,
							int nsyms)
{
	int						i;
	int						flag;
	struct nlist			temp;

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
