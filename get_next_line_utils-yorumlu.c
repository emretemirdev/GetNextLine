/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emtemir <emtemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 19:01:38 by emtemir           #+#    #+#             */
/*   Updated: 2023/08/03 19:01:42 by emtemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

/*
 * "found_newline" fonksiyonu, bağlı listede bir '\n' karakteri bulunup bulunmadığını kontrol eder.
 * Eğer '\n' karakteri bulunursa 1 döndürür, aksi takdirde 0 döndürür.
 */
int found_newline(t_list *list)
{
    int i;

    if (NULL == list)
        return (0);

    while (list)
    {
        i = 0;
        // Listenin mevcut düğümünde '\n' karakterini arar
        while (list->str_buf[i] && i < BUFFER_SIZE)
        {
            if (list->str_buf[i] == '\n')
                return (1);
            ++i;
        }
        // Bir sonraki düğüme geçer
        list = list->next;
    }

    return (0);
}

/*
 * "find_last_node" fonksiyonu, bağlı listedeki son düğümü bulur ve geri döndürür.
 */
t_list *find_last_node(t_list *list)
{
    if (NULL == list)
        return (NULL);

    // Son düğüme kadar ilerler
    while (list->next)
        list = list->next;

    return (list);
}

/*
 * "copy_str" fonksiyonu, bağlı listeden bir sonraki satırın verisini "str" adlı
 * hedef bellek alanına kopyalar. Eğer '\n' karakteri bulunursa kopyalamayı durdurur.
 */
void copy_str(t_list *list, char *str)
{
    int i;
    int k;

    if (NULL == list)
        return;

    k = 0;
    // Bağlı listede gezinerek veriyi kopyalar
    while (list)
    {
        i = 0;
        while (list->str_buf[i])
        {
            if (list->str_buf[i] == '\n')
            {
                str[k++] = '\n';
                str[k] = '\0';
                return;
            }
            str[k++] = list->str_buf[i++];
        }
        list = list->next;
    }

    str[k] = '\0';
}

/*
 * "len_to_newline" fonksiyonu, bağlı listedeki bir sonraki satıra kadar olan toplam veri uzunluğunu hesaplar.
 */
int len_to_newline(t_list *list)
{
    int i;
    int len;

    if (NULL == list)
        return (0);

    len = 0;
    // Bağlı listede gezinerek uzunluğu hesaplar
    while (list)
    {
        i = 0;
        while (list->str_buf[i])
        {
            if (list->str_buf[i] == '\n')
            {
                ++len;
                return (len);
            }
            ++i;
            ++len;
        }
        list = list->next;
    }

    return (len);
}

/*
 * "dealloc" fonksiyonu, bağlı listedeki tüm düğümleri ve ilgili bellek alanlarını serbest bırakır.
 * "clean_node" adlı düğümü listenin başına ekler ve dosyadan okunan son satırdaki veriyi temsil eder.
 * Eğer clean_node düğümünde veri varsa, listenin başına eklenir, aksi takdirde temizlenir.
 */
void dealloc(t_list **list, t_list *clean_node, char *buf)
{
    t_list *tmp;

    if (NULL == *list)
        return;

    // Bağlı listedeki tüm düğümleri ve bellek alanlarını serbest bırakma
    while (*list)
    {
        tmp = (*list)->next;
        free((*list)->str_buf);
        free(*list);
        *list = tmp;
    }

    *list = NULL;

    // clean_node düğümündeki veriye bağlı olarak listenin başına ekleme veya temizleme
    if (clean_node->str_buf[0])
        *list = clean_node;
    else
    {
        free(buf);
        free(clean_node);
    }
}
