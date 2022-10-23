/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nali <nali@42abudhabi.ae>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 12:33:11 by nali              #+#    #+#             */
/*   Updated: 2022/04/18 09:32:50 by nali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static const char	*ft_checksign(const char *nptr, int *sign, int *start)
{
	if (*nptr == '-')
		*sign = -1;
	*start = 1;
	nptr++;
	return (nptr);
}

static const char	*ft_number(const char *nptr, long int *result, int *start)
{
	*result = (*result * 10) + (*nptr - '0');
	*start = 1;
	nptr++;
	return (nptr);
}

static int	check_limit(long long result, const char *nptr, int sign)
{
	long long	limit_min;
	long long	limit_max;

	limit_min = ((result * 10) + (*nptr - '0')) * sign;
	if (limit_min < -2147483648)
		return (0);
	limit_max = ((result * 10) + (*nptr - '0')) * sign;
	if (limit_max > 2147483647)
		return (-1);
	return (1);
}

int	ft_atoi(const char *nptr)
{
	int			sign;
	long int	result;
	int			start;
	int			limit_test;

	sign = 1;
	result = 0;
	start = 0;
	while (*nptr)
	{
		if (((*nptr >= 9 && *nptr <= 13) || *nptr == ' ') && start == 0)
			nptr++;
		else if ((*nptr == '-' || *nptr == '+') && start == 0)
			nptr = ft_checksign(nptr, &sign, &start);
		else if (*nptr >= 48 && *nptr <= 57)
		{
			limit_test = check_limit(result, nptr, sign);
			if (limit_test == 0 || limit_test == -1)
				return (limit_test);
			nptr = ft_number(nptr, &result, &start);
		}
		else
			return (0);
	}
	return (sign * result);
}
