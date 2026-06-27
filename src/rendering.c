//Maria

// create frame content (corridors, walls, floor, ceiling...)

/* The use of images of the minilibX library is strongly recommended.*/

/*
Except for the map, each element must begin with its type identifier (composed
by one or two characters), followed by its specific information in a strict order:

- North texture:
NO ./path_to_the_north_texture
· identifier: NO
· path to the north texture

- South texture:
SO ./path_to_the_south_texture
· identifier: SO
· path to the south texture

- West texture:
WE ./path_to_the_west_texture
· identifier: WE
· path to the west texture

- East texture:
EA ./path_to_the_east_texture
· identifier: EA
· path to the east texture

- Floor color:
F 220,100,0
· identifier: F
· R,G,B colors in range [0,255]: 0, 255, 255

- Ceiling color:
C 225,30,0
· identifier: C
· R,G,B colors in range [0,255]: 0, 255, 255
*/

set_north_texture();
set_south_texture();
set_west_texture();
set_east_texture();
set_floor_color();
set_ceiling_texture();