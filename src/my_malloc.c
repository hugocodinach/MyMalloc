/*
** EPITECH PROJECT, 2018
** PSU_2018_malloc
** File description:
** src/struct/my_malloc.c
*/

#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include "main.h"

static memory_t *new = NULL;
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void *malloc(size_t size)
{
    void *tmp = NULL;
    memory_t *tmpmem;

    pthread_mutex_lock(&mtx);
    if (new == NULL) {
        return (malloc_init(size, &new, &mtx));
    }
    for (memory_t *ctp = new; ctp != NULL && ctp->next != NULL;
    ctp = ctp->next) {
        if (ctp->full == FALSE && ctp->size >= size) {
            ctp = push_at(ctp, size);
            pthread_mutex_unlock(&mtx);
            return (ctp->mem_ptr);
        }
    }
    tmpmem = push_back(new, size);
    if (tmpmem)
        tmp = tmpmem->mem_ptr;
    pthread_mutex_unlock(&mtx);
    return (tmp);
}

void *realloc_ptr(void *ptr, size_t size, memory_t *tmp)
{
    void *tmpmem;

    for (memory_t *ctp = new; ctp != NULL && ctp->next != NULL;
    ctp = ctp->next) {
        if (ctp->mem_ptr != ptr && ctp->full == FALSE && ctp->size >= size) {
            ctp = push_at(ctp, size);
            pthread_mutex_lock(&mtx);
            memcpy(ptr, ctp->mem_ptr, tmp->size);
            pthread_mutex_unlock(&mtx);
            return (ctp->mem_ptr);
        }
    }
    tmpmem = malloc(size);
    pthread_mutex_lock(&mtx);
    memcpy(ptr, tmpmem, (tmp->size < size) ? tmp->size : size);
    pthread_mutex_unlock(&mtx);
    free(ptr);
    return (tmpmem);
}

void *realloc(void *ptr, size_t size)
{
    memory_t *tmp;

    if (!ptr) {
        return (malloc(size));
    }
    if (ptr && size == 0) {
        free(ptr);
        return (NULL);
    }
    tmp = ptr - sizeof(memory_t);
    if (tmp->size >= size) {
        tmp->size = size;
        return (tmp->mem_ptr);
    }
    return (realloc_ptr(ptr, size, tmp));
}

void free(void *ptr)
{
    memory_t *tmp = new;

    for (; tmp && tmp->mem_ptr != ptr; tmp = tmp->next);
    if (tmp && tmp->next != NULL) {
        tmp->full = FALSE;
    } else if (tmp) {
        if (tmp->previous) {
            tmp = tmp->previous;
            tmp->size += sizeof(memory_t) + tmp->next->size;
            if (tmp->next->size >= (size_t)get_page_size()) {
                tmp->size -= (tmp->next->size / getpagesize()) * getpagesize();
                sbrk((tmp->next->size / getpagesize()) * getpagesize() * -1);
                set_page_size(0);
            }
            tmp->next = NULL;
        } else {
            sbrk((tmp->size / getpagesize()) * getpagesize() * -1);
            set_page_size(0);
            new = NULL;
        }
    }
}

void show_alloc_mem(void)
{
    write(1, "break : 0x", 10);
    printbase((unsigned long long int)sbrk(0), "0123456789ABCDEF");
    write(1, "\n", 1);
    for (memory_t *tmp = new; tmp != NULL; tmp = tmp->next) {
        write(1, "0x", 2);
        printbase((unsigned long long int)tmp->mem_ptr, "0123456789ABCDEF");
        write(1, " - 0x", 5);
        printbase((unsigned long long int)tmp->mem_ptr + tmp->size,
        "0123456789ABCDEF");
        write(1, " : ", 3);
        my_put_nbr(tmp->size);
        write(1, "bytes\n", 6);
    }
}