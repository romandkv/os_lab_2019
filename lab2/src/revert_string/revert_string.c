#include "revert_string.h"
#include <stdio.h>

static int	ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void RevertString(char *str)
{
	char	*res;
	int	size;
	int	i;
	
	i = 0;
	size = ft_strlen(str);
	res = (char *)malloc(sizeof(char) * (size + 1));
	size--;
	while (size > -1)
	{
		res[i] = str[size];
		i++;
		size--;	
	}
	res[i] = '\0';
	while (size < i)
	{
		str[size] = res[size];
		size++;
	}
}

