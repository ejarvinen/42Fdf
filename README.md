# 42Fdf: Wireframe Model for 3D Landscapes
![Example Wireframe Model](https://github.com/ejarvinen/42Fdf/blob/main/header.png)
## Overview
**FDF (Fil De Fer)** is a project designed to represent 3D landscapes as wireframe models, where surfaces are outlined with lines. This project leverages the [MLX42](https://github.com/codam-coding-college/MLX42) graphical library to render landscapes from a specific viewpoint and interact with the 3D model.

## Features
- **3D Isometric Projection**: Represents a landscape in a clean and structured wireframe format.
- **Dynamic Input Handling**: Reads landscape data from `.fdf` files, where each number represents a coordinate in 3D space.
- **Smooth Graphics Management**: Efficient window rendering, minimizing, and smooth exit functionalities.
- **[Libft](https://github.com/ejarvinen/42Libft) Integration**: Utilizes custom library functions like `get_next_line` and `ft_split` for efficient file parsing.

## Mandatory Requirements
- **Rendering**:
  - Displays a wireframe model using [isometric projection](https://en.wikipedia.org/wiki/Isometric_projection).
  - Coordinates are read from an input file in the following format:
    ```
    0 0 0 3
    0 1 2 0
    0 2 1 0
    ```
    - Horizontal position: X-axis
    - Vertical position: Y-axis
    - Value: Altitude (Z-axis)
  - Example: A file `testmap.fdf` renders a structured wireframe landscape.
- **Graphic Management**:
  - Displays the rendered image in a window.
  - Smooth handling of window events (switching, minimizing, etc.).
  - Pressing `ESC` or clicking the close button exits cleanly.

## Setup and Usage

### Prerequisites
- **C Compiler**: Ensure you have a compatible C compiler (e.g., `gcc`).
- **MLX42 Library**: MLX42 can be initialized by running `git submodule init` and `git submodule update` inside the project folder after cloning this repository.
- **Makefile**: Provided to simplify compilation.

### Installation
1. Clone this repository:
```
git clone https://github.com/ejarvinen/42Fdf.git
cd 42Fdf
```
2. Update and initialize submodules:
```
git submodule init
git submodule update
```
3. Build the project using the Makefile:
```
make
```

### Usage
To render a landscape:
```
./fdf filename.fdf
```
Example:
```
./fdf testmap.fdf
```

This will open a window displaying the wireframe model of the specified landscape.

## File Structure
- **`Makefile`**: Automates compilation and cleanup.
- **`*.c` and `*.h` files**: Source code and headers for the project.
- **Input Files**: Accepts a single `.fdf` file containing landscape data.

## Development Guidelines
- **Coding Standards**: Adheres to the 42 coding norm.
- **Memory Management**: All heap allocations are properly freed to avoid memory leaks.
- **Error Handling**: No unexpected crashes (e.g., segmentation faults).

## Example Input
### Input File: 
```
0 0 1 2 3 4 5 6 7 8 9
0 0 0 1 2 3 4 5 6 7 8
0 0 0 0 1 2 3 4 5 6 7
0 0 0 0 0 1 2 3 4 5 6
0 0 0 0 0 0 1 2 3 4 5
0 0 0 0 0 0 0 1 2 3 4
0 0 0 0 0 0 0 0 1 2 3
0 0 0 0 0 0 0 0 0 1 2
0 0 0 0 0 0 0 0 0 0 1
```
### Output
![Example model](https://github.com/ejarvinen/42Fdf/blob/main/example1.png)
