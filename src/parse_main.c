#include "cub3d.h"

int main(int argc, char **argv)
{
    t_parse     parse;
    t_display   display;

    initparse(&display);
    
    if (argc == 1)
        return (showerror(&display, "No path to scene file have been provided."));
    if (argc > 3)
        return (showerror(&display, "More than two argument have been provided."));
    if (argc == 3 && !cmp(argv[2], "--save", 6))
        return (showerror(&display, "Invalid second argument"));
        
    if (!parse(argc, argv[1], &parse, &display))
        return (EXIT_FAILURE);
        
    display.rgbfloor[0] = colortoint(display.rgbfloor[0], display.rgbfloor[1], display.rgbfloor[2]);
    display.rgbceiling[0] = colortoint(display.rgbceiling[0], display.rgbceiling[1], display.rgbceiling[2]);
    
    if (argc == 3 && cmp(argv[2], "--save", 6))
    {
        create_bmp(&display);
    }
    else
    {
        display.r1 = parse.r1;
        display.r2 = parse.r2;
        
        if (display_game(&parse, &display) != 0)
            return (EXIT_FAILURE);
    }
    
    return (EXIT_SUCCESS);
}
