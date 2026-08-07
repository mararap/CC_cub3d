---

kanban-plugin: board

---

## [[Inbox]]



## [[Read]]

- [ ] Read & Summarize [[DDA]] in my own words (no copy-paste)
- [ ] Skim https://lodev.org/cgtutor raycasting chapter
- [ ] Draw [[DDA]] step-by-step on paper / excalidraw


## [[Understand]]/[[Explain]]

- [ ] in 1 sentence: what does [[DDA]] do that a regular line-drawing algorithm doesn't?
- [ ] Trace through: "Player at (5,5) shooting ray at 0°, map is 5x5. Show ray hitting which walls step by step"
- [ ] Explain to Juliyan or rubber duck: Why do we cast ONE ray per screen column, not a grid of rays?
- [ ] Sketch the formula: wall_height = window_height / distance - when would wall_height be off screen?


## [[Code]]

- [ ] [[Ray caster]]
- [ ] Phase 1: Data pipeline
	 - [ ] Modify `set_north_texture()` in `rendering.c` to actually store the texture path in `state->scene.tex_no`
	 - [ ] Repeat for S, E, W textures and floor/ceiling colors
	 - [ ] Implement `init_player()` to scan map, find N/S/E/W, initialize pos + direction vector
	 - [ ] Test: Print player position to verify it's not (0, 0)
- [ ] Phase 2: Raycasting loop
	- [ ] Create stub function `raycaster()` that takes player state and returns a 1D array of wall distances (one per screen column)
	- [ ] Implement DDA inside: for each column, step through grid until you hit a '1', store distance
	- [ ] Test: Print distances for 5 columns to debug
	- [ ] Replace the 2D map drawing in `render_frame()` with a simple version that draws vertical lines of varying height (no texture yet)
- [ ] Phase 3: Texture sampling
	- [ ] Load textures with `mlx_xpm_file_to_image()` at startup
	- [ ] For each wall column, calculate which pixel in the texture to sample (hit_x_offset)
	- [ ] Sample that column from the texture image and draw it
- [ ] Phase 4 Movement
	- [ ] Implement WASD movement in `keys.c` (update pos_dir.x_pos / y pos)
	- [ ] Implement arrow key rotation (rotate pos_dir deirection vector and camera plane)
	- [ ] Test: Move around. walls should distort correctly


## [[Test]] & [[Debug]]

- [ ] After each phase:
	- [ ] No segfaults
	- [ ] Can move without clipping walls (collision later = bonus)
	- [ ] Textures don't shimmer or flip
	- [ ] Fish-eye distortion not too extreme


## [[Done]]





%% kanban:settings
```
{"kanban-plugin":"board","list-collapse":[false,false,false,false,false]}
```
%%