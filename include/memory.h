/*
** EPITECH PROJECT, 2018
** memory.h
** File description:
** memory.h
*/

#ifndef MEMORY_H_
#define MEMORY_H_

#include "main.h"

typedef struct memory_s {
    size_t size;
    bool_t full;
    struct memory_s *next;
    struct memory_s *previous;
    void *mem_ptr;
} memory_t;

memory_t *init_memory(size_t size);
memory_t *push_back(memory_t *memory, size_t size);
memory_t *push_at(memory_t *at, size_t size);
bool_t free_mem(memory_t **memory, void *ptr);
memory_t *find_element(memory_t *memory, void *ptr);
long get_page_size(void);
void set_page_size(size_t);
void *malloc_init(size_t size, memory_t **new, pthread_mutex_t *mtx);
void show_alloc_mem(void);
void my_put_nbr(int nb);
void printbase(unsigned long long nbr, char const *base);

#endif