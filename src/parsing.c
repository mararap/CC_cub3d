// Juliyan

// handle map

/*• Your program must take as a first argument a scene description file with the .cub
extension.
◦ The map must be composed of only 6 possible characters: 0 for an empty space,
1 for a wall, and N,S,E or W for the player’s start position and spawning
orientation.
This is a simple valid map:
111111
100101
101001
1100N1
111111
◦ The map must be closed/surrounded by walls, if not the program must return
an error.
◦ Except for the map content, each type of element can be separated by one or
more empty lines.
◦ Except for the map content which always has to be the last, each type of
element can be set in any order in the file.
◦ Except for the map, each type of information from an element can be separated
by one or more spaces.
◦ The map must be parsed as it looks in the file. Spaces are a valid part of the
map and are up to you to handle. You must be able to parse any kind of map,
as long as it respects the rules of the map.*/

void set_map(char** map)
{
    //check char 0 for an empty space,1 for a wall, and N,S,E or W + space

    //check if the map is closed by wall

    //remove space

    int row = 0;
    int i = 0;

    while (map[row] != '\0')
    {
        if (ft_strchr(map[row], '0') && ft_strchr(map[row], '1') && ft_strchr(map[row], 'N') && ft_strchr(map[row], 'S')
        && ft_strchr(map[row], 'E') && ft_strchr(map[row], 'W') && ft_strchr(map[row], ' ')
            perror("Error\n: unrecognized char in the map");
        i = 0;
        if (map[row][0] != '1')
            perror("Error\n: Map does not start with a wall"); 
        while(map[row][i])
        {
            i++;
        }
        if (map[row][i] != '1')
            perror("Error\n: Map does not end with a wall"); 
    }

}

int	parse_command_line(int argc, char **argv, t_app_state *state)
{
    int fd;
    char*  line;
    char**   map;
    int i = 0;

    if (argv != 2)
    {
        perror("Error\n: No scene file was specified!");
        exit(1);
    }
    fd = open("first.cub", O_RDONLY);
    if (fd == -1)
    {
        perror("Error\n: Program");
        exit(1);
    }
    while ((line = get_next_line(fd)) != NULL)
    {
        if (line[0] == '\n')
        {
            //skip;
        }
        else if (line[0] == 'N')
            set_north_texture();
        else if (line[0] == 'S')
            set_south_texture();
        else if (line[0] == 'W')
            set_west_texture();
        else if (line[0] == 'E')
            set_east_texture();
        else if (line[0] == 'F')
            set_floor_color();
        else if (line[0] == 'C')
            set_ceiling_texture();
        else if (line[0] == 1)
        {
            while ((map[i] = get_next_line(fd)) != NULL)
                i++;
            set_map(map);
        }
        else
            perror("Error\n: Unrecognized character in the cub file");
    }
	return (0);
}