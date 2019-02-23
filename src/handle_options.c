/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_options.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchicote <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 16:17:46 by cchicote          #+#    #+#             */
/*   Updated: 2019/02/23 16:17:52 by cchicote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

char						*init_options(void)
{
	char					*options;
	int						i;

	i = -1;
	options = (char*)ft_memalloc(sizeof(char) * 7);
	if (!options)
		return (NULL);
	while (++i < 6)
		options[i] = 0;
	options[i] = '\0';
	return (options);
}

void						perror_wrong_option(char *option)
{
	ft_putstr("ft_nm: nm: Unknown command line argument '");
	ft_putstr(option);
	ft_putendl("'.");
}

int							parse_options(char *options, char *str)
{
	size_t					i;

	i = 0;
	while (++i < ft_strlen(str))
	{
		if (str[i] == 'g')
			options[LCG] = 1;
		else if (str[i] == 'p')
			options[LCP] = 1;
		else if (str[i] == 'r')
			options[LCR] = 1;
		else if (str[i] == 'u')
			options[LCU] = 1;
		else if (str[i] == 'j')
			options[LCJ] = 1;
		else if (str[i] == 'U')
			options[UCU] = 1;
		else
		{
			printf("[%c]\n", str[i]);
			perror_wrong_option(str);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}