/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 15:31:11 by cchicote          #+#    #+#             */
/*   Updated: 2019/01/25 15:31:18 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void						add_arch_to_list(t_file *file, t_arch *arch)
{
	t_arch					*tmp;

	tmp = file->arch;
	arch->next = NULL;
	if (!tmp)
	{
		file->arch = arch;
		return ;
	}
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = arch;
}

t_symbol					*new_symbol(void)
{
	t_symbol				*new;

	new = (t_symbol*)ft_memalloc(sizeof(t_symbol));
	ft_bzero(new, sizeof(t_symbol));
	return (new);
}

int					cmp_null_values(char *a, char *b)
{
	if (!a && !b)
		return (0);
	else if (!a)
		return (-1);
	return (1);
}

t_symbol*			sorted_merge(t_symbol *a, t_symbol *b) 
{ 
	t_symbol		*result;
	int				ret;

	result = NULL;
	if (a == NULL)
		return(b);
	else if (b == NULL)
		return(a);
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

void					front_back_split(t_symbol *source, t_symbol **frontRef, t_symbol **backRef) 
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

void					merge_sort(t_symbol **headRef) 
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

void					sort_arch_symbols(t_file *file)
{
	t_arch				*tmp;

	tmp = file->arch;
	while (tmp)
	{
		merge_sort(&tmp->sym_head);
		tmp = tmp->next;
	}
}

void					sort_symbols_by_name(t_arch *arch)
{
	t_symbol			*iterator;
	t_symbol			*tmp_previous;
	t_symbol			*tmp;
	t_symbol			*tmp_next;
	
	iterator = arch->sym_head;
	tmp_previous = NULL;
	while (iterator)
	{
		if (iterator->next && ft_strcmp(iterator->name, iterator->next->name) > 0)
		{
			tmp = iterator;
			tmp_next = iterator->next;
			if (tmp_previous)
				tmp_previous->next = tmp_next;
			else
				arch->sym_head = tmp_next;
			tmp->next = tmp_next->next;
			tmp_next->next = tmp;
			iterator = arch->sym_head;
			tmp_previous = NULL;
		}
		else
		{
			tmp_previous = iterator;
			iterator = iterator->next;
		}
	}
}

void						add_symbol_to_list(t_symbol **sym_head, t_symbol *symbol)
{
	t_symbol				*tmp;

	tmp = *sym_head;
	symbol->next = NULL;
	if (!tmp)
	{
		*sym_head = symbol;
		return ;
	}
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = symbol;
}