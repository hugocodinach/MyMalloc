/*
** EPITECH PROJECT, 2017
** my_putnbr_base.c
** File description:
** my_putnbr_base
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void my_putchar(char c)
{
    write(1, &c, 1);
}

void my_put_nbr(int nb)
{
    int mod;

    if (nb < 0) {
        my_putchar('-');
        nb = nb * -1;
    }
    if (nb >= 0) {
        if (nb >= 10) {
            mod = (nb % 10);
            nb = (nb - mod) / 10;
            my_put_nbr(nb);
            my_putchar(mod + 48);
        } else {
            my_putchar(48 + (nb % 10));
        }
    }
}

int len(char const *str)
{
    int i = 0;

    if (!str)
        return (0);
    for (; str[i] != '\0'; i += 1 );
    return (i);
}

void printbase(unsigned long long nbr, char const *base)
{
    unsigned long long step1 = nbr;
    int base_len = len(base);
    unsigned long long disp;
    char rslt[512];
    int i = 0;

    disp = nbr % base_len;
    rslt[i] = base[disp];
    while (step1 >= (size_t)base_len) {
        i = i + 1;
        step1 = step1 / base_len;
        disp = step1 % base_len;
        rslt[i] = base[disp];
    }
    for (; i >= 0; i -= 1)
        write(1, &rslt[i], 1);
}