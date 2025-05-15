/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoldber <agoldber@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:31:43 by agoldber          #+#    #+#             */
/*   Updated: 2025/05/15 21:31:03 by agoldber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isspace(char *str)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str == ' ' || *str == '\n' || *str == '\t')
			count++;
		else
			return (0);
		str++;
	}
	return (count);
}
