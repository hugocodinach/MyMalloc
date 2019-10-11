/*
** EPITECH PROJECT, 2018
** sec_malloc.c
** File description:
** src/struct/sec_malloc.c
*/

#include "main.h"

void *malloc_init(size_t size, memory_t **new, pthread_mutex_t *mtx)
{
    *new = init_memory(size);
    pthread_mutex_unlock(mtx);
    if (!new) {
        return (NULL);
    }
    return ((*new)->mem_ptr);
}

void *calloc(size_t num, size_t size)
{
    void *ptr = malloc(size * num);

    memset(ptr, 0, size * num);
    return (ptr);
}