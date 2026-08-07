#Milestone_04
## [[Ray casting]] vs. [[Binary Space Partitioning]]

### [[W3D|Wolfenstein 3D]]

W3D uses [[raycasting|ray casting]] to transform a 2D map array into a pseudo-3D perspective:

```
[1][1][1][1][1] 1 = Wall
[1][0][0][0][1] 0 = Empty Space
[1][0][P][0][1] P = Player casting a ray
[1][1][1][1][1]  (Ray hits grid lines perfectly)
```

#### The Approach:
The engine casts a 2D ray or every vertical column of the player's screen resolution. It steps through a strict, uniform square grid until it hits a wall cell.

#### Why it was used:
It is incredibly fast. In 1992, computers lacked the processing power to render true 3D geometry in real-time. Raycasting reduced a 3D rendering problem into a series of simple 2D mathematical intersections.

#### The constraints:
- All walls must be exactly **90 degrees** to each other.
- All walls must conform to **the same grid size**.
- The floor and ceiling must be **perfectly flat** and uniform.
- The player **cannot look up or down** or jump.

## Doom: [[BSP|Binary Space Partitioning]]
For Doom, the developers wanted outdoor areas, non-orthogonal walls, varying light levels, and platforms at different heights. [[Understanding Ray casting]] on a flat grid made this mathematically impossible.

```
Doom Top-Down View (BSP Tree Splitting):
       /           / = Arbitrary diagonal wall
    A / B          A, B, C = Sectors at different heights
_____/___________  ____ = BSP splitting line separating
    /              visible areas from hidden areas
   /    C
```


#### The Approach
Doom uses [[Binary Space Partitioning|BSP]] trees. Before the game runs, a tool called a "node builder" splits the 2D map layout into a [[tree structure]] of [[nested]] sub-spaces. At runtime, the engine traverses this tree relative to the player's position to quickly figure out which walls are closest and draw them from front to back.

#### Why it was used
It allowed the engine to render complex 2D lines (linedefs) at any angle or length, rather than forcing everything into a rigid grid. Once the walls were drawn, the engine simply filled in the remaining spaces as floors and ceilings.

#### The constraints
Doom is still fundamentally a "2.5D" game. Because the level is generated from a 2D floor plan, you **cannot have rooms directly on top of other rooms** (no true 3D bridges).

---
