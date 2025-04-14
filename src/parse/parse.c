#include "../cub3d.h"

int	init_parser(t_display *display)
{
    display->mapboleen = 0;
    display->initsuccess = 0;
    display->textnum = 0;
    display->errorbool = 0;
    display->maptofree = -1;
    display->south = NULL;
    display->north = NULL;
    display->west = NULL;
    display->east = NULL;
    display->spritepwd = NULL;
    display->filename = NULL;
    return (0);
}

int	parse(int argc, char *str, t_parse *parse, t_display *display)
{
    int		fd;

    if (argc == 3)
        display->bmp = 1;
    else
        display->bmp = 0;
    if ((display->filename = malloc(sizeof(char) * strlentoend(str) + 1)) == NULL)
        return (showerror(display, "Unable to Malloc"));
    if (checkcubextension(str, display) != 1)
        return (0);  // Error is handled in checkcubextension
    ft_strcpy(display->filename, str);
    fd = open(str, O_RDONLY);
    if (fd == -1)
        return (showerror(display, "Unable to open file"));
    display->fd = fd;
    if (checkparse(display, parse, fd) != 0)
        return (0);  // Error is handled in checkparse
    return (1);
}

int	checkparse(t_display *display, t_parse *parse, int fd)
{
    int		u;
    char	*line;

    u = 0;
    while (u > -1)
    {
        u = get_next_line(fd, &line);
        if (u == -1)
            return (showerror(display, "Error reading file"));
        
        if (line[numberblank(line)] == '1' || u == 0)
            u = -1;
        if (parseline(line, parse, display) == -1)
            u = -1;
        free(line);
    }
    close(fd);
    if (display->textnum < 8)
        return (showerror(display, "Elements Missing"));
    if (display->textnum > 8)
        return (showerror(display, "Duplicate Element"));
    if (display->mapboleen == 0)
        return (showerror(display, "Missing Map"));
    return (0);
}

int	parseline(char *line, t_parse *parse, t_display *display)
{
    int index;

    index = 0 + numberblank(line);
    if (line[index] == '\0' || line[index] == '\n')
        return (1);
    
    if (line[index] == 'R')
        return (stockresolution(line + index + 1, parse, display));
    if (line[index] == 'N' && line[index + 1] == 'O')
        return (stocktextures_no(line + index + 2, display));
    if (line[index] == 'S' && line[index + 1] == 'O')
        return (stocktextures_so(line + index + 2, display));
    if (line[index] == 'W' && line[index + 1] == 'E')
        return (stocktextures_we(line + index + 2, display));
    if (line[index] == 'E' && line[index + 1] == 'A')
        return (stocktextures_ea(line + index + 2, display));
    if (line[index] == 'S' && line[index + 1] == ' ')
        return (stocktextures_s(line + index + 1, display));
    if (line[index] == 'F' && line[index + 1] == ' ')
        return (stockcolorf(line + index + 1, display));
    if (line[index] == 'C' && line[index + 1] == ' ')
        return (stockcolorc(line + index + 1, display));
    if (line[index] == '1' || line[index] == '2' || line[index] == '0')
        return (stockmap(parse, display));
    
    return (showerror(display, "One or more elements in .cub are not correct"));
}

int	checkcubextension(char *str, t_display *display)
{
    int i;

    i = 0;
    while (str[i] != '\0')
        i++;
    if (i < 5) // Need at least ".cub"
        return (showerror(display, "Invalid filename"));
    
    if (str[i - 1] == 'b' && str[i - 2] == 'u'
    && str[i - 3] == 'c' && str[i - 4] == '.')
    {
        if ((i = open(str, O_RDONLY)) == -1)
            return (showerror(display, "File Name is not correct"));
        close(i);
        return (1);
    }
    return (showerror(display, "Files without .cub extension are not accepted"));
}

int	strlentoend(char *str)
{
    int i;

    i = 0;
    while (str[i] && str[i] != '\0')
        i++;
    return (i);
}

int	isend(char *line)
{
    if (*line == '\n' || *line == '\0' || *line == ' ')
        return (1);
    return (0);
}

int	numberblank(char *str)
{
    int i;

    i = 0;
    while (str[i] == ' ' || str[i] == '\t')
        i++;
    return (i);
}

int	searchcomma(char *line)
{
    int i;

    i = 0;
    while (line[i] && line[i] != ',')
        i++;
    if (line[i] == ',')
        return (i);
    return (-1);
}
