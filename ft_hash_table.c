/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flhember <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 14:18:15 by flhember          #+#    #+#             */
/*   Updated: 2019/11/15 14:43:01 by flhember         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strlen(char *str)
{
	while (str[i])
		i++;
	return (i);
}

void	ft_hach_table(char *str, int **tab)
{
	int		s;
	int		keys;

	keys = 0;
	s = ft_strlen(str);
	keys = str[s - 1];
	keys += str[s - 2];
	printf();
}

int		main()
{
	char 	*str1 = "ok";
	char 	*str2 = "ko";
	char 	*str3 = "ook";
	char 	*str4 = "koo";
	int		size_tab = 4;
	int		*tab[size_tab];
	int		i;

	i = 0;
	ft_hach_table(str1, tab);
	ft_hach_table(str2, tab);
	ft_hach_table(str3, tab);
	ft_hach_table(str4, tab);

	return (0);
}
