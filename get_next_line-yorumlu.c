/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line-yorumlu.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emtemir <emtemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:44:03 by emtemir           #+#    #+#             */
/*   Updated: 2023/08/03 19:07:18 by emtemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line.h"

/*
 * "polish_list" fonksiyonu, dosyadan okunan satırların sonundaki '\n' karakterini
 * kaldırmak ve sonraki satıra geçmeye hazırlamak için kullanılır.
 */
void	polish_list(t_list **list)
{
	// Son düğümü ve boş bir düğümü (clean_node) tanımla
	t_list	*last_node;
	t_list	*clean_node;
	int		i;
	int		k;
	char	*buf;

	// Bellek alanı oluşturma ve NULL kontrolü
	buf = malloc(BUFFER_SIZE + 1);
	clean_node = malloc(sizeof(t_list));
	if (NULL == buf || NULL == clean_node)
		return ;

	// Son düğümü bul
	last_node = find_last_node(*list);

	// Satır sonundaki '\n' karakterini bulmak için döngü
	i = 0;
	k = 0;
	while (last_node->str_buf[i] && last_node->str_buf[i] != '\n')
		++i;

	// '\n' sonrası veriyi buf'a kopyala
	while (last_node->str_buf[i] && last_node->str_buf[++i])
		buf[k++] = last_node->str_buf[i];
	buf[k] = '\0';

	// clean_node düğümünü güncelle
	clean_node->str_buf = buf;
	clean_node->next = NULL;

	// Bellek alanlarını serbest bırakma ve bağlı listeyi güncelleme
	dealloc(list, clean_node, buf);
}

/*
 * "get_line" fonksiyonu, dosyadan okunan veriyi, bellek alanına kopyalayarak
 * bir sonraki satırı elde etmek için kullanılır.
 */
char	*get_line(t_list *list)
{
	int		str_len;
	char	*next_str;

	if (NULL == list)
		return (NULL);

	// Bir sonraki satırın uzunluğunu bul ve bellek alanı oluşturma
	str_len = len_to_newline(list);
	next_str = malloc(str_len + 1);
	if (NULL == next_str)
		return (NULL);

	// Bellek alanına veriyi kopyalama
	copy_str(list, next_str);
	return (next_str);
}

/*
 * "append" fonksiyonu, yeni bir düğüm oluşturarak, veriyi bağlı listeye eklemek için kullanılır.
 */
void	append(t_list **list, char *buf)
{
	t_list	*new_node;
	t_list	*last_node;

	// Son düğümü ve yeni düğümü oluştur
	last_node = find_last_node(*list);
	new_node = malloc(sizeof(t_list));
	if (NULL == new_node)
		return ;

	// Bağlı listeye düğümü ekleme
	if (NULL == last_node)
		*list = new_node;
	else
		last_node->next = new_node;

	new_node->str_buf = buf;
	new_node->next = NULL;
}

/*
 * "create_list" fonksiyonu, dosyadan verileri okuyarak bağlı listeyi oluşturmak için kullanılır.
 */
void	create_list(t_list **list, int fd)
{
	int		char_read;	
	char	*buf;

	// Yeni satır karakteri ('\n') bulunana kadar dosyadan veri okuma
	while (!found_newline(*list))
	{
		// Bellek alanı oluşturma ve NULL kontrolü
		buf = malloc(BUFFER_SIZE + 1);
		if (NULL == buf)
			return ;

		// Dosyadan veriyi okuma
		char_read = read(fd, buf, BUFFER_SIZE);
		if (!char_read)
		{
			free(buf);
			return ;
		}
		buf[char_read] = '\0';

		// Okunan veriyi bağlı listeye ekleme
		append(list, buf);
	}
}

/*
 * "get_next_line" fonksiyonu, verilen dosya tanımlayıcısından bir sonraki satırı okumak için kullanılır.
 */
char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*next_line;

	// Hata durumları için giriş kontrolü
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
		return (NULL);

	// Dosyadan bağlı listeyi oluşturma
	create_list(&list, fd);

	// Bağlı liste boşsa NULL döndür
	if (list == NULL)
		return (NULL);

	// Bir sonraki satırı elde et
	next_line = get_line(list);

	// Dosyadan okunan satırların sonundaki '\n' karakterini kaldır
	polish_list(&list);

	// Bir sonraki satırı döndür
	return (next_line);
}
