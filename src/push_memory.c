/*
** EPITECH PROJECT, 2018
** push_memory.c
** File description:
** src/struct/push_memory.c
*/

#include "main.h"
#include <errno.h>
#include <pthread.h>

static long page_size = 0;

memory_t *init_memory(size_t size)
{
    memory_t *new;
    void *tmp;

    new = sbrk(((size + sizeof(memory_t)) / getpagesize() + 1) *
    getpagesize());
    if (errno == ENOMEM)
        return (NULL);
    page_size = (((size + sizeof(memory_t)) / getpagesize() + 1) *
    getpagesize()) - size;
    new->next = NULL;
    new->previous = NULL;
    new->full = TRUE;
    new->size = size;
    tmp = (void *)new + sizeof(memory_t);
    new->mem_ptr = tmp;
    return (new);
}

memory_t *push_back(memory_t *memory, size_t size)
{
    memory_t *tmp = memory;
    long alloc = ((size + sizeof(memory_t) - page_size) / getpagesize() + 1) *
        getpagesize();

    if (alloc != 0)
        sbrk(alloc);
    if (errno == ENOMEM)
        return (NULL);
    page_size = (((size + sizeof(memory_t) - page_size) / getpagesize() + 1) *
    getpagesize()) - size;
    for (; tmp->next; tmp = tmp->next);
    tmp->next = (void *)tmp + sizeof(memory_t) + tmp->size;
    tmp->next->full = TRUE;
    tmp->next->size = size;
    tmp->next->mem_ptr = (void *)(tmp->next) + sizeof(memory_t);
    tmp->next->next = NULL;
    tmp->next->previous = tmp;
    return (tmp->next);
}

memory_t *push_at(memory_t *at, size_t size)
{
    size_t s;
    void *tmp;

    at->full = TRUE;
    if (at->size > size + sizeof(memory_t)) {
        s = at->size;
        at->size = size;
        tmp = at->next;
        at->next = (void *)at + sizeof(memory_t) + size;
        at->next->size = s - size - sizeof(memory_t);
        at->next->full = FALSE;
        at->next->mem_ptr = (void *)(at->next) + sizeof(memory_t);
        at->next->previous = at;
        at->next->next = tmp;
    }
    return (at);
}

long get_page_size(void)
{
    return (page_size);
}

void set_page_size(size_t new_size)
{
    page_size = new_size;
}