/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emtemir <emtemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 18:31:54 by emtemir           #+#    #+#             */
/*   Updated: 2023/07/26 19:32:20 by emtemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
 int main()
 {
    int fd;
    char buf[256];
    int char_reads;

    fd = open("file.txt", O_RDWR | O_CREAT);

    while ((char_reads = read(fd, buf, 1)))
    {
        buf[char_reads] = '\0';
        usleep(150000);
        printf("buf -> %s\n", buf);
    }
    
 }


