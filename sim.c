/**

 */
#include "sim.h"

#define CIMP
extern void asm_doRow(belem *, belem *, size_t, size_t, size_t);

/**
 * gets x mod N (works for negative numbers as well! Use this instead of %)
 */
size_t getModVal(int x, size_t N){
     size_t adj = x/N;

     return((x+adj*N)%N);
}

/**
 * process one row of the board. 1d array
 * is it ded 0 or alive 1. store cell's future val into nextbuffer
 * incompatible types
 */
static void doRow(belem *dest, belem *src, size_t row, size_t rows, size_t cols){
  
  for(size_t col = 0; col < cols; col++){
    //pretend 2d
    int live_neighbors = 0;
    int n1 = getIndex( cols, getModVal( row - 1, rows ), getModVal( col - 1, cols) ); //row-1 col-1
    int n2 = getIndex( cols, getModVal( row - 1, rows), getModVal( col, cols));
    int n3 = getIndex( cols, getModVal( row - 1, rows), getModVal( col + 1, cols));
    int n4 = getIndex( cols, getModVal( row, rows), getModVal( col - 1, cols));
    //skip itself
    int n6 = getIndex( cols, getModVal( row, rows), getModVal(col + 1, cols));
    int n7 = getIndex( cols, getModVal( row + 1, rows), getModVal( col - 1, cols));
    int n8 = getIndex( cols, getModVal( row + 1, rows), getModVal(cols, cols));
    int n9 = getIndex( cols, getModVal( row + 1, rows), getModVal( col + 1, cols));

    //src start at 0,0. pretend 1d
    live_neighbors += *(src + n1 );
    live_neighbors += *(src + n2 );
    live_neighbors += *(src + n3 );
    live_neighbors += *(src + n4 );
    live_neighbors += *(src + n6 );
    live_neighbors += *(src + n7 );
    live_neighbors += *(src + n8 );
    live_neighbors += *(src + n9 );
    if(*(src + (row * cols) + col) == 1 ){ //alive
      if( live_neighbors == 0 || live_neighbors == 1 || live_neighbors >= 4) *(dest + (row * cols) + col) = 0;
      else *(dest + (row * cols) + col) = 1;
    }
    else{
      if( live_neighbors == 3) *(dest + (row * cols) + col) = 1;
      else *(dest + (row * cols) + col) = 0;
    }
}
}




/**
 * perform a simulation for "steps" generations
 *
 * for steps
 *   calculate the next board
 *   swap current and next
 * 
 * inc gen
 */
void simLoop(boards_t *self, unsigned int steps){
  //declare the current and nexft than swap
  for(unsigned int i = 0; i < steps; i++){
    for(size_t r = 0; r < self->numRows; r++){
      doRow(self->nextBuffer, self->currentBuffer, r, self->numRows, self->numCols);
    }
    swapBuffers(self);
    self->gen+=1;
  }
}


