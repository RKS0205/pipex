#include "../pipex.h"

size_t	ft_strlen(const char *s)
{
	int	n;

	n = 0;
	while (s[n] != 0)
		n++;
	return (n);
}
