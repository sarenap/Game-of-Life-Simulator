/**
 
 *
 */
#include "cse30life.h"
#include "board.h"

/**
 * create a new board
 *
 * - malloc a boards structure
 * - set the generation to 0
 * - open the file (if it doesn't exist, return a NULL pointer
 * - read the first line which is the number of rows
 * - read the second line which is the number of cols
 * - set the # of rows and # of cols in the boards structure
 * - malloc bufferA and bufferB 
 * - Set currentBuffer and nextBuffer
 * - clear both board buffers
 * - read the file until done.  each row contains a row and a columns separted by
 *   white space
 *     for each line, set the cell in the current buffer
 * - close the file
 * - return the boards pointer if successfull or NULL ptr otherwise
 */
boards_t * createBoard(char *initFileName){

  boards_t *boardptr = (boards_t*)malloc(sizeof(boards_t)); //ptr to board struc
  boardptr->gen = 0;  //already using struct

  FILE *fp; //file pointer to open initfilename. free ptr then return null
  if((fp = fopen(initFileName, "r")) == NULL ){
    free(boardptr);
    return NULL; 
  }

  fscanf(fp, "%u\n%u", &(boardptr->numRows), &(boardptr->numCols));
   

  boardptr->bufferA = (belem*)malloc(boardptr->numRows * boardptr->numCols * sizeof(belem));
  if(boardptr->bufferA == NULL) {
    free(boardptr->bufferA);
    free(boardptr);
    return NULL;
  }
  
  boardptr->bufferB = (belem*)malloc(boardptr->numRows * boardptr->numCols * sizeof(belem));
  if(boardptr->bufferB == NULL) {
    free(boardptr->bufferB);
    free(boardptr);
    return NULL;
  }


  boardptr->currentBuffer = boardptr->bufferA;
  boardptr->nextBuffer = boardptr->bufferB;

  clearBoards(boardptr);


//Read in the input file 
//initialize appropriate cells in currentBuffer to be alive.
size_t row = 0;
size_t col = 0; 
while(fscanf(fp, "%u %u", &row, &col) != EOF ){
  size_t index = getIndex(boardptr->numCols, row, col);
  boardptr->currentBuffer[index] = 1; //all cell in config alive=1. 1d array
  // *(boardptr->currentBuffer + index ) = 1;
}

  // free(boardptr->bufferA);
  // free(boardptr->bufferB);
  fclose(fp);
  return boardptr;
}

/**
 * delete a board. pass in boardptr
 * takes a ptr to a ptr to a boards_t struct
 * deallocates (frees) all memory associated with struct.
 *  sets ptr to the boards_t struct to null.
 */
void deleteBoard(boards_t **bptrPtr){
  free( (*bptrPtr)->bufferA);
  free( (*bptrPtr)->bufferB);
  free( (*bptrPtr));
  *bptrPtr = NULL;
}

/**
 * set all the belems in both buffers to 0
 * 1d array of belems
 * self (the board) has buffer A and B
 */
void clearBoards(boards_t *self){ 
  memset(self->bufferA, 0, self->numRows * self->numCols * sizeof(belem));
  memset(self->bufferB, 0, self->numRows * self->numCols * sizeof(belem));
}

/**
 * swap the current and next buffers
 * swapBuffers() takes a boards_t struct pointer 
 * and swaps the current buffer with the next
 * buffer.swap adres
 */
void swapBuffers(boards_t *self){
  belem *tmp = self->currentBuffer;
  self->currentBuffer = self->nextBuffer;
  self->nextBuffer = tmp;
}


/**
 * get a cell index. use later in createboard to say who's alive or dead
 */
size_t getIndex(size_t numCols, size_t row, size_t col){
  return (row * numCols) + col; 
}
  
