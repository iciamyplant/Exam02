#include "get_next_line.h"

static int		ft_get_that_line(char **line, char *buff, int fctr, int len)
{
	int		i;
	int		j;
	char	*tmp;

	tmp = *line;
	i = -1;
	j = -1;
	if (!(*line = (char *)malloc(sizeof(**line) * (BUFFER_SIZE * fctr + 1))))
	{
		free(tmp);
		return (-1);
	}
	while (tmp && tmp[++i])
		(*line)[i] = tmp[i]; //si on read plusieurs fois a chaque fois on copie dans line, mais on free line pour remalloc donc faut un tmp
	i = (i < 0) ? 0 : i; // si line est deja remplie de la premiere partie de la ligne il faut copier a partir de i sinon a partir de 0
	while (++j < len)
		(*line)[i + j] = buff[j]; //on copie buff dans line
	(*line)[i + j] = 0; //on ajoute le \0 a la fin de line
	j = (buff[j]) ? j + 1 : j; // si buff[j] est \n il faut faire j++ pour supprimer dans buff tout ce qui a ete copie + le \n
	i = 0; //pour copier a buff[0] ce qui est dans buff et quon a pas encore mis dans line
	while (buff[j])
		buff[i++] = buff[j++]; // on supprime de buff ce qu'on a deja mis dans line
	buff[i] = 0;
	free(tmp);
	return (1);
}

int				get_next_line(int fd, char **line)
{
	static char	buff[BUFFER_SIZE + 1];
	int			len;
	int			fctr;
	int			ret;

	fctr = 0;
	ret = 1;
	if (!(*line = NULL) && (BUFFER_SIZE < 1 || read(fd, buff, 0)))
		return (-1);
	while (ret)
	{
		if (!(buff[0]))
		{
			ret = read(fd, buff, BUFFER_SIZE);
			buff[ret] = 0;
		}
		len = 0;
		while (buff[len] && buff[len] != '\n')
			len++;
		if (buff[len] == '\n')
			return (ft_get_that_line(line, buff, ++fctr, len));
		if (ft_get_that_line(line, buff, ++fctr, len) == -1)
			return (-1);
	}
	return (0);
}
/*
int		main()
{
	int fd;
	int ret;
	int i;
	char *str = NULL;

	fd = open("test", O_RDONLY);
	ret = 1;
	while (i < 3)
	{
		ret = get_next_line(fd, &str);
		printf("%s\n", str);
		free(str);
		i++;
	}
	printf("%s\n", str);
	free(str);
	str = NULL;
}*/
