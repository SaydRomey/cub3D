
/* ************************************************************************** */

void	test_term_colors(void)
{
	int		i;
	int		j;
	int		code;

	i = 0;
	while (i < 16)
	{
		j = 0;
		while (j < 16)
		{
			code = i * 16 + j;
			printf("\033[38;5;%dm %4d", code, code);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("\033[0m\n");
}
