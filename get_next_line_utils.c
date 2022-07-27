/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstroeva <mstroeva@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 16:34:08 by mstroeva          #+#    #+#             */
/*   Updated: 2022/07/27 15:42:47 by mstroeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *ft_load_buf(char *box, int fd)
{
	char	*buf;
	int		byte_read;

	byte_read = 1;
	while (search_n(box) == -1 && byte_read > 0)
	{
		buf = ft_create((BUFFER_SIZE + 1) * sizeof(char));
		byte_read = read(fd, buf, BUFFER_SIZE);
		if (byte_read < 0)
		{
			buf = ft_full_free(buf);
			box = ft_full_free(box);
			return(NULL);
		}
		*(buf + byte_read) = '\0';
		if(byte_read == 0)
		{
			buf = ft_full_free(buf);
			if (box)
				return(box);
			return(NULL);
		}
		box = ft_unite(box, buf); 
		if (!box)
			return(NULL);
		buf = ft_full_free(buf);
	}
	return(box);
}

char *ft_create(int i)
{
	char	*result;

	result = (char *)malloc(i * sizeof(char));
	if (result == NULL)
		return(NULL);
	*(result + (i - 1)) = '\0';
	return (result);
}

char *ft_full_free(char *tofree)
{
	free(tofree);
	return(NULL);
}

char *ft_unite(char *box, char *buf)
{
	char	*tmp;

	if (box == NULL)
		return(ft_strdup(buf));
	else
		tmp = ft_strjoin(box, buf);
	if (tmp == NULL)
		return(NULL);
	box = ft_full_free(box);
	box = ft_strdup(tmp);
	tmp = ft_full_free(tmp);
	return(box);
}

char *ft_formline(char *box)
{
	char	*line;
	int		i;
	
	if (!box || *box == '\0')
		return(NULL);
	i = 0;

	line = (char *)malloc(sizeof(char) * (ft_strlen(box) + 1));
	if(line==NULL)
		return(NULL);
	while (*(box + i) != '\0' && *(box + i) != '\n')
	{
		*(line + i) = *(box + i);
		i++;
	}
	*(line + i) = *(box + i);

	if (*(line + i) != '\0')
	{
		i++;
		*(line + i) = '\0';
	}
	return(line);
}

char *ft_formbox(char *box)
{
	char	*tmp;
	int		i;

	i = 0;
	while (*(box + i) != '\n' && *(box + i) != '\0')
		i++;
	if (*(box + i) == '\n')
		i++;
	tmp = ft_substr(box, i, (ft_strlen(box) - i));
	if (*tmp == '\0')
		{
			free(box);
			free(tmp);
			return(NULL);
		}
	box = ft_full_free(box);
	box = ft_strdup(tmp);
	tmp = ft_full_free(tmp);
	return(box);
}

//finding INDEX OF N. Returns -1 if no N or empty buffer. 
int	search_n(char *buffer)
{
	int	i;
	
	i = 0;
	if (buffer == NULL)
		return(-1);
	while(*(buffer + i) != '\n' && *(buffer + i) != '\0')
		i++;
	if (*(buffer + i) == '\0')
		i = -1;
	return(i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*res;
	unsigned int	i;

	i = 0;
	if (s == 0)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	res = malloc((len + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	while (i < (len) && s[start + i] != '\0')
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_strdup(const char *s)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = malloc(ft_strlen(s) + 1);
	if (ptr == NULL)
		return (NULL);
	while (i < (int)ft_strlen(s))
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;

	if (!s1)
		return (NULL);
	s3 = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (s3 == NULL)
		return (NULL);
	ft_strlcpy(s3, s1, (ft_strlen(s1) + 1));
	ft_strlcat(s3, (char *)s2, (ft_strlen(s1) + ft_strlen(s2) + 1));
	return ((char *)s3);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
	{
	int		ssize;
	size_t	ret2;
	size_t	j;
	size_t	dstj;
	size_t	i;

	ssize = size - 1;
	i = 0;
	ret2 = size;
	if ((int)ft_strlen(dst) <= ssize)
	{
		ret2 = ft_strlen(dst);
		j = ssize - ft_strlen(dst);
		dstj = ft_strlen(dst);
		while (i < j && src[i] != '\0')
		{
			dst[dstj] = src[i];
			i++;
			dstj++;
		}
		dst[dstj] = '\0';
	}
	return (ft_strlen(src) + ret2);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size != 0)
	{
		while (i < (size - 1) && src[i] != '\0')
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	i = 0;
	while (src[i] != '\0')
	{
		i++;
	}
	return (i);
}
