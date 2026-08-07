---

kanban-plugin: board

---

## [[Inbox]]

- [ ] Rendering
	- [ ] Phase 1: Data pipeline 📅 2026-08-09
		 - [ ] Data Hookup): Rewrite the 6 stubs in `rendering.c` using the `extract_path` method (google AI mode), so paths are saved into `state->scene.tex_no`, `tex_so`, etc.
		 - [ ] Implement `init_player()` to scan map, find N/S/E/W, 
			 - [ ] Set positions: `state->pos_dir.x_pos = x + 0.5;` and `state->pos_dir.y_pos = y + 0.5;`
			 - [ ] Set the initial camera direction vector fields: `x_dir` and `y_dir`.
			 - [ ] **Crucial Step:** Initialize your **camera plane vectors** (`x_plane` and `y_plane`) to determine your Field of View (FOV). For a standard 66° FOV, if facing North (`x_dir = 0, y_dir = -1`), your plane should be (`x_plane = 0.66, y_plane = 0`).
		 - [ ] Test: Print player position to verify it's not (0, 0)
	- [ ] Phase 2: Raycasting loop 📅 2026-08-11 
		- [ ] The Math Bridge: Create function `void raycaster(t_app_state *state)` that takes player state and returns a 1D array of wall distances (one per screen column) inside a new file raycast.c.
		- [ ] write loop across window width (`0` to `WINDOW_WIDTH` / 1280). For every individual column x:
			- [ ] calculate the ray position and vector direction based on the currend camera plane
			- [ ] step through grid (`mapX`, `mapY`) using DDA until you hit a '1', store distance in `state->map`
			- [ ] calculate straight-line distance (`perpWallDist`)
		- [ ] Test: Print distances for 5 columns to debug
		- [ ] Replace the 2D map drawing in `render_frame()` with a simple version that loops through every column x on the screen, calculate `line-height` unsing `perpWallDist`, and call juliyan's pixel driver:
			- [ ] draw ceiling color (`state->scene.color_ceil`) from pixel row `0` to `draw_start`
			- [ ] draw a solid wall color (e.g., green `0x00FF00`) from `draw_start` to `draw_end`
			- [ ] draw floor color (`state->scene.color_floor`) from `draw_end` to `WINDOW_HEIGHT` (720)
	- [ ] Phase 3: Texture sampling 📅 2026-09-07
		- [ ] Load textures with `mlx_xpm_file_to_image()` at startup
		- [ ] For each wall column, calculate which pixel in the texture to sample (hit_x_offset)
		- [ ] Sample that column from the texture image and draw it
	- [ ] Phase 4 Movement 📅 2026-08-13
		- [ ] **Task 1 (Linear Step Processing):**  modify `on_key_press()` in `keys.c`. When `KEY_W` or `KEY_S` is caught, modify `state->pos_dir.x_pos` and `y_pos` by adding or subtracting a fraction of `x_dir` and `y_dir` vectors.
		- [ ] **Task 2 (The Rotation Matrix):** When `KEY_LEFT` or `KEY_RIGHT` is pressed, use basic trigonometric rotation formulas to spin both your direction vectors (`x_dir`/`y_dir`) and camera plane vectors (`x_plane`/`y_plane`) using a small angle configuration variable (like `0.05` radians).
		- [ ] **The Vacation Gate:**  Using keyboard to seamlessly move around a solid-colored maze made possible 🏁


## [[Read]]

- [ ] Read & Summarize [[DDA]] in my own words (no copy-paste)
- [ ] Skim https://lodev.org/cgtutor raycasting chapter


## [[Understand]]/[[Explain]]

- [ ] Trace through: "Player at (5,5) shooting ray at 0°, map is 5x5. Show ray hitting which walls step by step"
- [ ] Draw [[DDA]] step-by-step on paper / excalidraw
- [ ] in 1 sentence: what does [[DDA]] do that a regular line-drawing algorithm doesn't?


## [[Code]]



## [[Test]] & [[Debug]]

- [ ] After each phase:
	- [ ] No segfaults 📅 2026-09-08 
	- [ ] Can move without clipping walls (collision later = bonus)  📅 2026-09-08 
	- [ ] Textures don't shimmer or flip  📅 2026-09-08 
	- [ ] Fish-eye distortion not too extreme  📅 2026-09-08


## [[Done]]

- [ ] Explain to Juliyan or rubber duck: Why do we cast ONE ray per screen column, not a grid of rays?




%% kanban:settings
```
{"kanban-plugin":"board","list-collapse":[false,true,true,true,false,true]}
```
%%