#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 69
#endif 

int ft_strlen(char *s)
{
	int i = 0;
	while (s[i])
			i++;
	
	return i;
}


char *ft_strchr(char *str, char c)
{
	while (*str)
	{
		if (*str == c)
				return str;

		str++;
	}
	return NULL;
}


void ft_append(char **mem, char *buf)
{
	char *nstr = malloc(ft_strlen(*mem) + ft_strlen(buf) + 1);

	int i = 0;
	int j = 0;

	while ((*mem)[j])
	{
		nstr[i] = (*mem)[j];
		i++;
		j++;
	}

	j = 0;
	while (buf[j])
	{
		nstr[i] = buf[j];
		i++;
		j++;
	}
	nstr[i] = '\0';
	

	free(*mem);
	*mem = nstr;
}


void read_line(char **mem, int fd)
{
	char *buffer = malloc(BUFFER_SIZE + 1);

	buffer[BUFFER_SIZE] = '\0';

	while (NULL == ft_strchr(*mem, '\n'))
	{
		int x = read(fd, buffer, BUFFER_SIZE);
		
		
		if (x == -1)
		{
			free(*mem);
			free(buffer);
			*mem = NULL;
			return;
		}
		
		else if (x == 0)
				break;

		buffer[x] = '\0';
		ft_append(mem, buffer);

	}

	free(buffer);
}



char *ft_strdup(char *mem)
{
	char *str = malloc(ft_strlen(mem) + 1);
	
	int i = 0;
	for ( ; mem[i] != '\0' && mem[i] != '\n' ; i++)
	{
		str[i] = mem[i];
	}

	if (mem[i] == '\n')
			str[i++] = '\n';

	str[i] = '\0';

	return str;
}


void ft_maqrum(char **mem)
{
	char *t = *mem;

	while (*t && *t != '\n')
		t++;

	if (*t == '\n')
		t++;

	char *str = malloc(ft_strlen(t) + 1);
	
	int i = 0;
	for ( ; t[i] != '\0' ; i++)
	{
		str[i] = t[i];
	}

	str[i] = '\0';

	free(*mem);
	*mem = str;
}



char *get_next_line(int fd)
{
	static char *mem;

	if (BUFFER_SIZE < 1 || fd < 0)
		return NULL;

	
	if (mem == NULL)
	{
		mem = malloc(1);
		*mem = '\0';
	}

	else
	{
		ft_maqrum(&mem);
	}

	read_line(&mem, fd);
	
	if (*mem == '\0')
	{
		free(mem);
		mem = NULL;
		return NULL;
	}

	return ft_strdup(mem);
}

/*
void gnel(int fd)
{
	char *line = get_next_line(fd);
	printf("%s", line);
	free(line);
}

int main()
{
	int fd = open("get_next_line.c", O_RDONLY);
	for (int i = 0; i < 1700; i++)
		gnel(fd);

	close(fd);
	return 0;
}



*/




