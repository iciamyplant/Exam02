#include <unistd.h>

int		main(int argc, char **argv)
{
	int i = 0;
	int tab[255];
	while (i < 255)
		tab[i++] = 0;
	i = 0;
	if (argc == 3)
	{
		while (argv[2][i])
		{
			tab[(unsigned char)argv[2][i]] = 1;
			i++;
		}
		i = 0;
		while (argv[1][i])
		{
			if (tab[(unsigned char)argv[1][i]] == 1)
			{
				tab[(unsigned char)argv[1][i]] = 2;
				write(1, &argv[1][i], 1);
			}
			i++;
		}
	}
	write(1, "\n", 1);
}

