#include "../cub3d.h"

int showerror(t_display *display, char *str)
{
    display->errorbool = 1;
    printf("\033[0;31mError\n%s\n", str);
    freemap(display);
    return (0);
}

int freemap(t_display *display)
{
    int i;

    i = 0;
    if (display->maptofree == -1)
        return (0);
        
    while (i < display->maptofree)
    {
        if (display->map[i])
            free(display->map[i]);
        i++;
    }
    
    free(display->map);
    display->map = NULL;
    
    if (display->north)
        free(display->north);
    if (display->south)
        free(display->south);
    if (display->west)
        free(display->west);
    if (display->east)
        free(display->east);
    if (display->spritepwd)
        free(display->spritepwd);
    if (display->filename)
        free(display->filename);
        
    return (1);
}

int ft_strlen(char *str)
{
    int i;

    i = 0;
    if (!str)
        return (0);
        
    while (str[i])
        i++;
        
    return (i);
}

char *ft_strcpy(char *dest, char *src)
{
    int i;

    i = 0;
    while (src[i])
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    
    return (dest);
}

int cmp(char *s1, char *s2, size_t n)
{
    size_t i;

    i = 0;
    while (s1[i] && s2[i] && i < n)
    {
        if (s1[i] != s2[i])
            return (0);
        i++;
    }
    
    if (i == n)
        return (1);
        
    return (0);
}

int freeandexit(t_display *display)
{
    freemap(display);
    if (display->errorbool == 0)
        printf("\033[0;32m[ Successfully exited ]\n");
    exit(0);
    return (0);
}
