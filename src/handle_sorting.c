/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sorting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 18:14:24 by cchicote          #+#    #+#             */
/*   Updated: 2019/02/16 18:14:30 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

int							cmp_null_values(char *a, char *b)
{
	if (!a && !b)
		return (0);
	else if (!a)
		return (-1);
	return (1);
}

t_symbol*					sorted_merge(t_symbol *a, t_symbol *b)
{
	t_symbol		*result;
	int				ret;

	result = NULL;
	if (!a)
		return (b);
	else if (!b)
		return (a);
	if (!a->name || !b->name)
		ret = cmp_null_values(a->name, b->name);
	else
		ret = ft_strcmp(b->name, a->name);
	if (ret > 0 || (ret == 0 && b->value > a->value))
	{
		result = a;
		result->next = sorted_merge(a->next, b);
	}
	else
	{
		result = b;
		result->next = sorted_merge(a, b->next);
	}
	return(result);
} 

void						front_back_split(t_symbol *source, t_symbol **frontRef, t_symbol **backRef)
{
	t_symbol		*fast;
	t_symbol		*slow;

	slow = source;
	fast = source->next;
	while (fast != NULL)
	{
		fast = fast->next;
		if (fast != NULL)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*frontRef = source;
	*backRef = slow->next;
	slow->next = NULL;
}

void						merge_sort(t_symbol **headRef)
{
	t_symbol		*head;
	t_symbol		*a;
	t_symbol		*b;

	head = *headRef;
	if (!head || !head->next)
		return ;
	front_back_split(head, &a, &b);
	merge_sort(&a);
	merge_sort(&b);
	*headRef = sorted_merge(a, b);
}

void						sort_arch_symbols(t_file *file)
{
	t_arch				*tmp;

	tmp = file->arch;
	while (tmp)
	{
		merge_sort(&tmp->sym_head);
		tmp = tmp->next;
	}
}
