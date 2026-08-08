
[...:] the idea is to check at every side of a wall the ray will encounter. We give each square width 1, so each side of a wall is an integer value and the places in between have a value after the point. Now the step size isn't constant, it depends on the distance to the next side:

![[ray_with_dda.png]]

Digital Differential Analysis or [[Digital differential Analysis|DDA]] is a fast #algorithm typically used on square grids to find which squares a line hits [...].

2 options: [[Euclidean geometry]] & [[Field of View]] OR additional [[vectors]] - direction vector and camera plane vector