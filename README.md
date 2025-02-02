
> (WIP)

# cub3D

## Description
**cub3D** is a **team project** at [42](https://42.fr), implementing a **Wolfenstein-like** game using the **MLX42** library ([MLX42 GitHub](https://github.com/codam-coding-college/MLX42)). It features a **raycasting engine**, **map parsing**, and **player interactions** with extended **gameplay features** beyond the base project requirements.

## Project PDFs
- [📄 Project PDF (EN)](link_to_pdf_eng)
- [📄 Projet PDF (FR)](link_to_pdf_fra)

## Contributors  

**oroy:**  
- Raycaster engine  
- Elevator and segworld logic  
- Door and sprite animation  
- In-game controls menu  
- Texture choice and design  
- Wall-collisions

**cdumais:**  
- Cubfile parsing and validation  
- Multi-map logic  
- Player controls and events system  
- Minimap  
- Pixel drawing functions  
- VXF (shadow rendering)  

---

# Requirements

- Raycasting engine rendering a 3D world with wall textures based on orientation (N, S, E, W).  
- Floor and ceiling colors defined in `.cub` file.  
- Movement: `WASD` for movement, arrow keys for rotation.  
- `.cub` file defining textures, colors, and a map layout.  
- Map enclosed by walls, using symbols `0` (walkable), `1` (walls), `N, S, E, W` (player spawn).  


## 🔹 **Base Requirements**
cub3D must include:
- A **raycasting engine** that simulates a 3D environment.
- **Texture loading** for walls from a `.cub` file.
- **Movement & rotation mechanics** for the player.
- **Custom map parsing** with `.cub` files defining world structure.
- Floor & ceiling colors (two distinct RGB values).

- Basic movement & rotation:
	- WASD for movement.
	- Left/Right Arrows for rotation.
	- ESC or window close button to exit.

Wall textures that change based on orientation (North, South, East, West).

## 🔹🎯  **Bonus Features**
Features from the official cub3D bonus list in the PDF:
- **Wall collisions** to prevent walking through obstacles.
- **Minimap rendering**.
Functional doors (open/close).
Animated sprites.
Mouse control for camera rotation.


## 🔹 **Extra Features**
Additional features implemented beyond the base requirements:
- **Multi-map support** (transitioning between different `.cub` files).
- **Elevator system** ().
- **Optional floor and ceiling textures** in `.cub` files.
- **Texture rendering toggle** (switch between wireframe & textures).
- **Interactive mode** (cursor activation for object interactions).
- **Improved minimap with dynamic colors & radar mode**.

Additional gameplay and visual improvements:
- **Player sprint mechanic** (`Left Shift` for speed boost).
- **Secondary raycasting for minimap field of view simulation**.
- **Glitch effect rendering toggle** (disabling floor & ceiling updates).
- **Procedural animated sprites** (randomly placed, blue flames effect).
- **Student extraction system** (fetches 42 profile images during compilation).
- **Interference effect for radar in elevators** (pixel noise simulating radio disruption).

Extras

(Additional features beyond the PDF bonus list)

🚀 Optional Floor & Ceiling Textures

Can be defined in .cub files (FL for floor, CE for ceiling).

Textures override colors but colors remain required.


🏃 Player Sprint

Left Shift increases movement speed.


🎨 Texture Rendering Toggle

Can switch between textured & wireframe mode.


🖱️ Interaction Mode

Right Mouse Click enables cursor mode for interacting with objects (e.g., elevators).


🏗️ Elevator System

Replaces doors with fully functional elevators that move between levels.

Automatic doors open when the player is near.

Green buttons appear inside the elevator:

Click a button to move to the next level.

Doors close before movement and reopen at the new floor.


Elevator constraints in .cub files:

Symbol: 3

Must be enclosed by three 1s and one 0 (entry side).

Example valid placement:

111111  
111001  
113101  
100001  
111111

🌌 Segworld Mechanic

If transitioning from a level with an elevator to one without, the game sends the player to a hidden "segworld" instead.

Blocks further level progression in a multi-map scenario.


🖼️ Student Extraction (42-Specific Feature)

Extracts evaluating student’s profile picture (from a predefined school Mac path).

Fallback to a default image if the file is not found.

Handled in the Makefile during compilation.


🔥 Animated Sprites

Blue flames appear in random positions (excluding near doors).


🎭 Glitchy Floor & Ceiling Rendering (Toggle Option)

Disables floor & ceiling re-rendering to create a "glitch" effect.

Requires texture rendering to be off.


---

## 🗺️ Minimap System

Two Minimap Modes

1. Centered Tile-Based Minimap  
Fixed grid showing the entire map.  

2. Radar-Style Minimap (Top-Right)  
Round minimap with a colored border.  
Centered around the player's position.

### Minimap Features
Optional player position highlighting.  
Player icon is a triangle, pointing in the facing direction.

#### Dynamic Minimap Colors:

Walkable areas: Averaged floor texture color (if defined), otherwise default color.
Walls: Averaged wall texture colors.
Player Icon: Inverted walkable tile color.

### Field of View Simulation:

Separate simplified raycaster displays colored rays from the player.  
Approximate values, Configurable via macros in `minimap.h` file.  

### Radar-Mode Extras

Interference Effect inside elevators.  
Simulated pixel noise mimicking a "radio disruption" effect. 

---



🎮 In-Game Controls Menu

UI menu displaying available controls.



---

🎮 Controls
(tableau here)


---

📦 Installation & Compilation

Dependencies


---

# 📜 Cubfile Details

## **Valid `.cub` File Requirements**  
- Must have a `.cub` suffix and contain all valid elements.  
- **Can include the following elements in any order** (except the map, which must be last):
  - **Wall textures:** One per direction (`NO`, `SO`, `WE`, `EA`).  
  - **Floor & ceiling colors** (`F R,G,B` and `C R,G,B`).
  - **Optional floor & ceiling textures** (`FL`, `CE`).
  - **Map layout** defining walls, floors, and elevator positions.

## **Map Rules & Symbols**
| Symbol | Meaning |
|--------|---------|
| `0` | Walkable space |
| `1` | Wall |
| `N`, `S`, `E`, `W` | Player spawn (facing direction) |
| `3` | Elevator |

- The elevator (`3`) must be bordered by exactly three `1`s (wall) and one `0` (walkable space).  

### **Example of a Valid `.cub` File**  
```plaintext
NO ./img/school/paint_wall.png
SO ./img/school/window.png
WE ./img/school/brick_wall.png
EA ./img/school/lockers.png

CE ./img/school/light.png
FL ./img/school/checker.png

F 142,136,73
C 109,192,195

1111111111111111
1111000000000111
110000000000W111
1110000131000011
1110000010000011
1000000000000001
1000101111110011
10000011 1000011
11111111 1111111
```

Invalid .cub Examples

🔗 [Invalid Cubfiles Directory](./map/bad_maps/)


---

Extras

- Optional Floor & Ceiling Textures

.cub files can include FL and CE textures for the floor and ceiling.


- Player Speedup on Left Shift

Pressing Left Shift increases movement speed.


- Texture Rendering Toggle

Switch between textures and base color rendering.


- Interaction Mode (Right Click)

Disables mouse turning, enables cursor to interact with objects like elevator buttons.


- Elevator System

Replaces doors with elevators that open automatically when the player approaches.

Green buttons appear inside the elevator.

Clicking a button moves the elevator up/down, closing doors before movement and reopening at arrival.


- Multi-Map Implementation

Supports launching multiple .cub files.
Elevator must exist in a .cub file to transition to the next level.

Example command:

```bash
./cub3D maps/level1.cub maps/level2.cub maps/level3.cub
```

Valid Elevator Rules:
Symbol: 3.
Must be bordered by exactly three 1s and one 0 (walkable space).

Image of a valid elevator in .cub file:

---

🏗️ Elevator System  
Replaces doors with automated elevators.  
Opens/closes based on proximity.  
Interactive buttons inside the elevator:  
Green buttons appear when inside.  
Click to move up/down.  
Doors close before movement and open upon arrival.


## 🚀 Multi-Map Support

Allows launching multiple .cub files.
Elevator required in .cub file to transition between levels.

Command Example:

```bash
./cub3D maps/level1.cub maps/level2.cub maps/level3.cub
```

Rules for valid elevators:
One per level.
3 walls, 1 open side.
Correct .cub file syntax.


## Segworld

Edge-case when transitioning from an elevator level to a non-elevator level:  
A hidden "segworld" level is created as the next destination.  
Blocks progression beyond that level.  

### 🌌 Segworld Mechanic  
Edge case handling for levels without an elevator:  
A hidden "segworld" level is created as the next destination.  
Blocks following levels from loading.  

-

Additional features:

🖼️ Student Extraction Mechanic  
Extracts the evaluating student's picture from a 42 Mac path.  
Fallback default image if extraction fails.  
Handled via the Makefile during compilation.  


🔥 Animated Sprites  
Blue flames randomly spawn (not near doors).  
Glitchy Floor & Ceiling Rendering (Toggle Option): Stops re-rendering floor and ceiling.  
Condition: Requires texture rendering to be off.  

Example short clip of segworld glitch effect:


---

- UI Menu for Controls

Toggleable partial or full display.


---



🖼️ Student Extraction Mechanic

Extracts the evaluating student's picture from a 42 Mac path.
Fallback default image if extraction fails.
Handled via the Makefile during compilation.


---

🎮 UI & Controls
(tableau here)


---

📦 Installation & Compilation

Dependencies

MLX42 (Installation Guide)

CMake (Required for MLX42)

GNU Make


Build Instructions

git clone https://github.com/SaydRomey/cub3D.git
cd cub3D
make
./cub3D maps/example.cub


---

🖥️ Showcase



🔗 Demo Video


---

📝 Credits

Authors: @oroy & @cdumais

42 School Project

Inspired by Wolfenstein 3D
