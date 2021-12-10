
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 5

char *ft_strdup(char *s1)
{
	char *res; 
	int i; 
	i = 0; 

	res = malloc (strlen(s1) + 1);
	while (s1[i])
	{
		res [i] = s1[i];
		i++;
	}
		res [i] = '\0'; 
		return(res);
}

char *ft_substr (char *s, int start, int len)
{

int i; 
char *res;
res = malloc(len + 1);

i = 0; 
while (i <= len)
{
	res[i] = s[i]; 
	i++;
}
	res[i] = '\0';
	return(res); 
}


int strc(char *str, char c)
{
	int i; 

	i = 0; 
	if (!str)
		return(0); 	
	else
	{
		while (*str)
		{
			if (*str == c)
				return(1);
			str++; 
		}
	}
	return(0);
}

char *strjoinf(char *s1, char *s2)
{

	char *res; 

	int i = 0;
	int j = 0;
	res = malloc (strlen(s1) +  strlen(s2) + 1);

	while (s1[i])
	{
		res[i] =  s1[i]; 
		i++;
	}
	while (s2[j])
	{
		res [i + j] = s2[j];
		j++;
	}
	res [i+j] = '\0';
	if (s1)
		free(s1);
	return(res);
}

void		*ft_calloc(size_t count, size_t size)
{
	int		*pointeur;
	int		s;
	size_t	i;

	s = count * size;
	if (s == 0)
		s = 1;
	pointeur = malloc(s);
	if (pointeur == NULL)
		return (0);
	i = 0;
	while (i < size)
	{
		((unsigned char *)pointeur)[i] = '\0';
		i++;
	}
	return (pointeur);
}

char *toom(char *memory, int i, char **line)
{

	char *tmp; 
	tmp = ft_strdup (memory); 
	int j;
	j = 0;
	if (memory[i])
	{
		while(memory[i] != '\0')
		{
			tmp[j] =  memory[i + 1];
			j++; 
			i++;
		}
		tmp[j] = '\0';
		free(memory); 
		memory = strdup(tmp);
		free(tmp);
	}
	else 
	{
		free(tmp);
		free(memory);
		memory = NULL; 
	}
	return(memory);
}


char *work(char *memory, char **line)
{
	int i; 
	char *tmp = ft_strdup(memory);

	i = 0;	
	if (memory[i])	
	{
		while (memory[i] && memory[i] != '\n')
			i++;
		*line = ft_substr(memory, 0, i); 
	}	
	else 
		*line = NULL;
	memory = toom(memory, i, line);
	return(memory);
}


char *get_next_line(int fd)
{
	static char *memory;
	char *line = NULL;
	char *buff = NULL;
	int ret = 0; 

	if (fd < 0 && BUFFER_SIZE <= 0)
		return(NULL);

	if (!memory)
		memory = ft_calloc(sizeof(char), 1); 
	buff = ft_calloc (sizeof(char), BUFFER_SIZE + 1);
	while (!strc(buff, '\n') && (ret = read(fd,buff,BUFFER_SIZE)) > 0)
	{
		buff[ret] = '\0';
		memory = strjoinf(memory, buff);
	}
	memory = work(memory, &line);
	free(buff);
	if (ret || memory || line)
		return(line); 
	free(memory);
	return(NULL);
}


int		main(int argc, char **argv)
 {
 	int		fd;
 	char	*line;

 	
	 
	//fd = 0;
		fd = open(argv[1], O_RDONLY);
		 line = get_next_line(fd);
 	while (line != NULL)
     {
 		dprintf(1, "line = |%s|", line);
		 free(line);
		 line = get_next_line(fd);
     }
     free(line);
 	return (0);
 }