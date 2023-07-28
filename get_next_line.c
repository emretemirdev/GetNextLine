/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emtemir <emtemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 12:59:22 by emtemir           #+#    #+#             */
/*   Updated: 2023/07/28 13:10:56 by emtemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char  *get_next_line(int fd)
{
    static char *str = NULL;
    char        *buf;
    int         char_reads;
    int         i;

    if (!str)
        str = malloc(sizeof(char) * 256);
    buf = malloc(sizeof(char) * 256);
    i = 0;
    while ((char_reads = read(fd, buf, 1)))
    {
        buf[char_reads] = '\0';
        str[i] = buf[0];
        i++;
    }
    str[i] = '\0';
    return (str);
}