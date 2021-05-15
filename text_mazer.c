#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

// constants
int NORTH = 0; 
int EAST = 1; 
int SOUTH = 2;
int WEST = 3; 

void grid_init(int rows, int cols, char *grid) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      grid[i * cols + j] = '#';
    }
  }
}

int get_coords(int x, int y, int cols) {
  return y * cols + x; 
}

bool in_bounds(int x, int y, int rows, int cols) {
  if (x < 0 || x >= cols || y < 0 || y >= rows) {
    return false;
  } else {
    return true;
  }
}

void shuffle(int *array, size_t n) {
  if (n > 1) {
    size_t i = 0; 
    for (i = 0; i < n - 1; i++) {
      size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
      int t = array[j];
      array[j] = array[i];
      array[i] = t;
    }
  }
}

void dfs(int x, int y, char *grid, int rows, int cols) {
  grid[get_coords(x, y, cols)] = ' '; 

  int neighbours[4] = {NORTH, EAST, SOUTH, WEST};
  shuffle(neighbours, 4);

  for (int i = 0; i < 4; i++) {
    int dx = 0;
    int dy = 0; 

    if (neighbours[i] == NORTH) {
      dy = -1; 
    } else if (neighbours[i] == SOUTH) {
      dy = 1; 
    } else if (neighbours[i] == EAST) {
      dx = 1;
    } else if (neighbours[i] == WEST) {
      dx = -1; 
    }
    
    int x2 = x + (dx << 1);
    int y2 = y + (dy << 1);

    if (in_bounds(x2, y2, rows, cols) == true &&
        grid[get_coords(x2, y2, cols)] == '#') {
      grid[get_coords(x2 - dx, y2 - dy, cols)] = ' ';
      dfs(x2, y2, grid, rows, cols); 
    }
  }
}

void print_grid(int rows, int cols, char *grid) {
  for (int y = 0; y < rows; ++y) {
    for (int x = 0; x < cols; ++x) {
      grid[get_coords(0, y, cols)] = '#';
      grid[get_coords(cols - 1, y, cols)] = '#';
      grid[get_coords(x, rows - 1, cols)] = '#';
      grid[get_coords(x, 0, cols)] = '#';
      printf("%c", grid[get_coords(x, y, cols)]);
    }
    printf("\n");
  }
}

void generate_maze(int rows, int cols, char *grid) {
  printf("%d x %d MAZE:\n", cols, rows);
  grid_init(rows, cols, grid); 
  dfs(1, 1, grid, rows, cols); 
  print_grid(rows, cols, grid);
}

int main(void) {
  // define size of maze
  int cols = 50;
  int rows = 25;
  char *grid = malloc((cols * rows) * sizeof(char));
  generate_maze(rows, cols, grid);
  free(grid); 
}