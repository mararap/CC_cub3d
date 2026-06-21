Maria — 14.06.26, 15:32Sonntag, 14. Juni 2026 um 15:32
Retrospective Jumanshe:

What went well?
we where able to do it,
we finished in time,
we learned a lot,
good collaboration,
solid planning,
ability to defend project,
attention to details,

What did not go so well?
relied too much on AI in the beginning resulting in us not understanding the code,
relied too much on external tester,
attention to details,
badly/insufficiently structuring the working process,
punctuality,

Lessons learned / how to improve?
come up with own test cases,
use AI for debugging and small steps,
keep the actual goal in mind, don't get (too) lost in rabbit holes,
git structure: one feature = one branch,
spend more time in the planning phase on clearing work division, create work chunks & sprints,
meet in the afternoon rather than 10/11 a.m. in the weekend,
meet in the evening during the week,
 (Bearbeitet)Sonntag, 14. Juni 2026 um 15:51
:heart:
Klicken, um zu reagieren
:thumbsup:
Klicken, um zu reagieren
:joy:
Klicken, um zu reagieren
Reaktion hinzufügen
Bearbeiten
Weiterleiten
Mehr

Maria — 14.06.26, 16:54Sonntag, 14. Juni 2026 um 16:54
splitting genaral:

A good 2-person split (balanced + low dependency friction)
 Juliyan: “World model + parsing + correctness gatekeeper”

You take responsibility for everything that defines what the world is:

.cub file parsing
Map validation (walls closed, only valid chars, player start, etc.)
Texture / color parsing
Building the central game_state struct
Ensuring data consistency (no invalid state reaches rendering)

 Output of your work:
A fully validated and ready-to-run game state, something like:

map grid
player position + direction
textures paths loaded/validated
RGB floor/ceiling values

 Your role is similar to minishell parsing, but even more strict:
“If it reaches Maria, it must already be correct.”

 Maria: “Rendering engine + raycasting + visuals”

You take the performance/graphics side:

Raycasting algorithm (DDA / step-by-step grid traversal)
Wall distance calculation
Projection math (fish-eye correction, wall height)
Texture mapping (choosing correct texture column)
Drawing to screen buffer
Frame rendering loop

 Output of your work:
A function that takes Juliyans game_state and produces:

a rendered frame in a window

 Your responsibility:
“Given correct data, make it look like a 3D world.”

 Shared responsibility (VERY important)

These are where most 42 teams fail if not agreed early:

Game state structure (t_game, t_player, etc.),

You MUST design this together.

What does the renderer need?
What does parsing need to provide?

 This is your “API contract”

MiniLibX / window + loop setup,

Decide together:

who initializes mlx
who owns the loop
how events are handled

Usually:

Maria: renders per frame
Juliyan: input updates state

Input system,

Split like this:

Juliyan: update state (move player, rotate)
Maria: uses updated state to render
:heart:
Klicken, um zu reagieren
:thumbsup:
Klicken, um zu reagieren
:joy:
Klicken, um zu reagieren
Reaktion hinzufügen
Bearbeiten
Weiterleiten
Mehr

Juliyan — 14.06.26, 17:13Sonntag, 14. Juni 2026 um 17:13
!!!1st of July @ 17.00 at the campus!!!
:heart:
Klicken, um zu reagieren
:thumbsup:
Klicken, um zu reagieren
:joy:
Klicken, um zu reagieren
Reaktion hinzufügen
Antworten
Weiterleiten
Mehr

Maria — 14.06.26, 17:18Sonntag, 14. Juni 2026 um 17:18
1st sprint: 14th June - 1st July

Juliyan: Map Validation, no invalid state reaches rendering

Maria: Research, notes, pseudo code, explain to Juliyan
Ray Casting Algorithm
Wall distance calculation
Projection math (fish-eye correction, wall height)
Drawing to screen buffer
Frame rendering loop
:heart:
Klicken, um zu reagieren
:thumbsup:
Klicken, um zu reagieren
:joy:
Klicken, um zu reagieren
Reaktion hinzufügen
Bearbeiten
Weiterleiten
Mehr

Maria — 14.06.26, 17:26Sonntag, 14. Juni 2026 um 17:26
common goal: merge and create working executable that opens a window and renders 1 frame (Bearbeitet)Sonntag, 14. Juni 2026 um 20:38
:heart:
Klicken, um zu reagieren
:thumbsup:
Klicken, um zu reagieren
:joy:
Klicken, um zu reagieren
Reaktion hinzufügen
Bearbeiten
Weiterleiten
Mehr
[17:28]Sonntag, 14. Juni 2026 um 17:28
suggestion: 4 sprints, 2 weeks each
switch responsibility for each sprint 