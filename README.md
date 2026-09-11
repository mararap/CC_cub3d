*This project has been created as part of the 42 curriculum by jatanaso and marapovi.*

# cub3D

## Description

`cub3D` is a first-person maze renderer inspired by *Wolfenstein 3D*. It turns
a two-dimensional `.cub` map into a pseudo-3D view by casting one ray for every
vertical screen column and locating wall intersections with the Digital
Differential Analysis (DDA) algorithm.

The project is written in C and uses MiniLibX for window management, images,
textures, and keyboard events. It was developed to practise graphics
programming, vector mathematics, parsing, resource management, and defensive
error handling under the 42 Norm.

### Implemented features

- DDA-based raycasting with perpendicular wall distances.
- Four direction-dependent XPM wall textures.
- Configurable floor and ceiling RGB colours.
- Player spawning in the `N`, `S`, `E`, or `W` direction.
- Forward, backward, and sideways movement with wall-collision checks.
- Left and right camera rotation using direction and camera-plane vectors.
- Strict `.cub` parsing and validation, including irregular maps and spaces.
- Clean shutdown through `ESC` or the window close button.
- A bonus build with a minimap, player marker, direction indicator, and ray fan.

## Requirements

The current Makefile targets the Linux/X11 version of MiniLibX. Building the
project requires:

- `cc` and `make`;
- MiniLibX installed where the compiler and linker can find `mlx.h` and
  `libmlx`;
- X11 and Xext development libraries;
- the math library.

The project includes its own `libft` and builds it automatically. On Windows,
the program can be run through WSL with working graphical support such as WSLg
or another X server.

## Instructions

Build the mandatory program:

```sh
make
```

Run it with exactly one `.cub` scene file:

```sh
./cub3D second.cub
```

Build and select the bonus version:

```sh
make bonus
./cub3D second.cub
```

`make bonus` places the bonus executable at `cub3D`. Running `make` again
selects the mandatory executable.

Other available rules are:

```sh
make clean     # remove cub3D object files
make fclean    # also remove executables and libft build products
make re        # rebuild the mandatory program from scratch
```

## Controls

| Key | Action |
| --- | --- |
| `W` | Move forward |
| `S` | Move backward |
| `A` | Strafe left |
| `D` | Strafe right |
| Left arrow | Look left |
| Right arrow | Look right |
| `ESC` | Close the program cleanly |

The window's close button also exits the program cleanly.

## Scene format

A scene file must end in `.cub`. It contains six configuration elements,
followed by the map. Configuration elements may appear in any order and may be
separated by empty lines, but the map must be the final element.

```text
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 45,38,31
C 8,18,31

111111111
100000001
1000N0001
100000001
111111111
```

### Configuration identifiers

| Identifier | Meaning |
| --- | --- |
| `NO` | North wall texture path |
| `SO` | South wall texture path |
| `WE` | West wall texture path |
| `EA` | East wall texture path |
| `F` | Floor colour as `R,G,B` |
| `C` | Ceiling colour as `R,G,B` |

Each RGB component must be between `0` and `255`. Every texture entry must
contain exactly one readable path.

### Map rules

- `1` represents a wall.
- `0` represents walkable space.
- Exactly one of `N`, `S`, `E`, or `W` defines the player position and initial
  orientation.
- Spaces are valid map content and are preserved during parsing.
- The map may be irregular, but every walkable tile and the player must be
  enclosed by walls rather than exposed to a space or the outside of the map.
- Empty lines cannot split the map.

Invalid arguments or scene data produce `Error` followed by an explanatory
message. The `maps/` directory contains valid and invalid edge-case scenes used
to exercise argument, configuration, colour, texture, player, and map-closure
validation.

## How raycasting works here

For every horizontal screen coordinate, the renderer:

1. converts the screen coordinate into camera space;
2. combines the player's direction and camera-plane vectors to create a ray;
3. uses DDA to step through map cells until a wall is reached;
4. calculates the perpendicular wall distance to avoid fish-eye distortion;
5. derives the projected wall-column height and texture coordinate;
6. draws ceiling, textured wall, and floor pixels into a MiniLibX image.

The finished image is then copied to the window. Movement updates the player
state and marks the frame for redrawing.

## Project structure

```text
include/             shared structures, constants, and prototypes
libft/               local utility library
maps/                parser and map-validation fixtures
src/app/             setup, hooks, shutdown, and resource cleanup
src/drawing/         raycasting, projection, and texture drawing
src/drawing/bonus/   minimap overlay implementation
src/input/           movement and camera rotation
src/parsing/         scene configuration and map parser
src/main.c           program entry point
src/utils/           shared error reporting
textures/            directional XPM wall textures
Obsidian_cub3D/      project subject, research, and planning notes
recources/           archived implementation references and citations
```

## Resources

### Raycasting and mathematics

- [Lode's Computer Graphics Tutorial: Raycasting](https://lodev.org/cgtutor/raycasting.html)
- [F. Permadi's Ray-Casting Tutorial](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/)
- [Interactive DDA explanation](https://aaaa.sh/creatures/dda-algorithm-interactive/)
- [Euclidean geometry overview](https://en.wikipedia.org/wiki/Euclidean_geometry)
- [Raycasting and cub3D by Beqa Tvildiani](https://www.youtube.com/watch?v=G9i78WoBBIU)
- [Raycasting in C by Daniel Hirsch](https://www.youtube.com/watch?v=2IEUa2gYJHQ)
- [Introducing RayCastWorld by javidx9](https://youtu.be/Vij_obgv9h4)
- [Super Fast Ray Casting in Tiled Worlds using DDA by javidx9](https://youtu.be/NbSee-XM7WA)
- [Raycaster demonstration by 3DSage](https://www.youtube.com/watch?v=gYRrGTC7GtA)

### MiniLibX and 42

- [MiniLibX getting-started documentation](https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html)
- [Official 42 Norminette repository](https://github.com/42School/norminette)
- [The original Wolfenstein 3D browser demo linked by the subject](http://users.atw.hu/wolf3d/)
- [Local project subject](Obsidian_cub3D/Subject.md)
- [Local research link collection](Obsidian_cub3D/Useful%20Links.md)

### Implementation references and attribution

The project research archive records implementation references used while
studying DDA and ray setup. They are included here for transparent attribution:

- [`calc_ray_dir.c` from lverdoes/cub3D](https://github.com/lverdoes/cub3D/blob/9348799f9e504349ccc4377b3903e0da49a4e08f/mandatory/engine/calc_ray_dir.c)
- [`ray.c` from DeRuina/cub3D-Advanced-Raycasting](https://github.com/DeRuina/cub3D-Advanced-Raycasting/blob/38115c9555ecc54c6362559ae333ebac3b2d9b36/src/ray.c)
- [Local code-citation notes](recources/Code_from_GitHub/Code_Citations.md)

These external implementations were treated as learning references. Their
licensing is recorded as unknown in the local citation notes and is not assumed
by this repository.

### Use of AI

AI tools were used as learning and development aids for:

- explaining raycasting, DDA, camera-plane vectors, projection, and wall-slice
  calculations;
- discussing parser design, validation cases, and small debugging steps;
- reviewing build rules, cleanup paths, and requirement coverage;
- suggesting focused refactors and helping consolidate this documentation.

AI-generated suggestions were reviewed against the subject, the C code, compiler
output, project-specific edge-case maps, and memory-checking results. The team
retained responsibility for understanding, adapting, testing, and defending the
final implementation.
