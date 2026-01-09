# C Tutorial Renderer

I made this quick project to improve my C coding skills and concepts. I also wanted to learn optimization so the rendering is done entirely by the CPU :)

### The Process

First, I decided to use SDL to manage the window and actions pertaining to it(open, close, etc), so I looked at the documentation for structuring the different elements of an application, which is the window, the renderer, and a texture. These three layers all interact and combine together to form the basis of the program.

Next, I needed a way to convert lines to pixels on a screen. There are a lot of simple methods and algorithms for this task, but I chose Bresenham's line algorithm because it relies entirely on integer division, eliminating the need for costly floating-point division. Afterwards, I wrote a function to draw a triangle from these lines, and I used the Barycentric coordinate system to determine whether a point(pixel) is inside of the triangle to fill it in. Along the way, I made a file full of helper functions to handle vector and matrix math.

Finally, I grabbed a mapping of the verticies of a cube off of the internet and mapped it in the program using the new functions I made. I applied the rotation matrix to make the cube rotate counter-clockwise, colored in some of the triangles so that the rotation is noticeable, and implemented a simple z-buffer to ensure that triangles that are hidden behind the cube are not rendered. I also added a simple FPS counter to the top right of the application window to measure performance.

### Optimizations

In terms of optimizations, there are three main optimizations I implemented after the naive implementation (on the unoptimized branch of this repo). The first optimization was to use the integer division version of Bresenham's algorithm to avoid slow floating-point operations. The second optimization was to calculate a "bounding box" for each triangle such that all of the pixels on the screen don't have to be redrawn every update. The third optimzation involves a single linear loop to clear the z-buffer instead of the normal double-nested for loop to handle width and height.

### Final Thoughts

I managed to learn a whole lot about how computer rendering works, how different concepts of linear algebra combine together to form the basis of rendering images on a screen, and most importantly, improving my skills in C. I also learned some fancy new terms like "z-buffer", "clip space", and "rasterization". It was a simple, yet fun project!

## Dependencies

`clang`/`gcc`, `make`, `SDL2`

### Install on Linux

**Ubuntu/Debian**
```bash
sudo apt-get update
sudo apt-get install clang make libsdl2-dev
```

**Fedora**
```bash
sudo dnf install clang make SDL2-devel
```

**Arch**
```bash
sudo pacman -S clang make sdl2
```

## Instructions for Testing

- `cd` into the project folder
- run `make`
- run the renderer like this: `./renderer`