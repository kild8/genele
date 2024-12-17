#ifndef GNL
#define GNL
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
    #define BUFFER_SIZE 100
#elif BUFFER_SIZE <= 0
    #undef BUFFER_SIZE
    #define BUFFER_SIZE 0
#endif
char *get_next_line(int fd);
int ft_strlen(const char *s);
#endif