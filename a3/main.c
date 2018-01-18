#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mhDefs.h"
#include "stuDefs.h"


int main()
{
  HeapType *heap;
  void  *ptr1, *ptr2, *ptr3, *ptr4, *ptr5, *ptr6, *ptr7, *ptr8, *ptr9;

  heap = (HeapType *) malloc(sizeof(HeapType));
  mh_init(heap);

  ptr1 = mh_alloc(heap, 5*sizeof(int), "ints");
  ptr2 = mh_alloc(heap, 10*sizeof(double), "doubles");
  ptr3 = mh_alloc(heap, 8*sizeof(char), "chars");
  ptr4 = mh_alloc(heap, 12*sizeof(StudentType), "Students");
  ptr5 = mh_alloc(heap, 5*sizeof(GameType), "Games");

  //This dump frees ptr1, ptr2, and ptr3
  printf("\nDUMP 1, byte count = %d\n", mh_count(heap));
  mh_dump(heap);

  mh_dealloc(heap, ptr1);
  mh_dealloc(heap, ptr2);
  mh_dealloc(heap, ptr3);

  //This dump frees up all current memory and creates 2 new dynamicly allocated memory
  printf("\nDUMP 2, byte count = %d\n", mh_count(heap));
  mh_dump(heap);

  mh_collect(heap);

  ptr6 = mh_alloc(heap, 3*sizeof(BusType), "Busses");
  ptr7 = mh_alloc(heap, 12*sizeof(WorkType), "Workers");
  
  //this dump creates new memory
  printf("\nDUMP 3, byte count = %d\n", mh_count(heap));
  mh_dump(heap);

  ptr8 = mh_alloc(heap, 8*sizeof(TeamType), "Teams");
  
  //This dump frees up ptr 8
  printf("\nDUMP 4, byte count = %d\n", mh_count(heap));
  mh_dump(heap);

  mh_dealloc(heap, ptr8);

  //Thus dump creates ptr9
  printf("\nDUMP 5, byte count = %d\n", mh_count(heap));
  mh_dump(heap);

  ptr9 = mh_alloc(heap, 9*sizeof(ProductType), "Products");
  
  //this dump frees up all memory
  printf("\nDUMP 6, byte count = %d\n", mh_count(heap));
  
  mh_dump(heap);
  mh_collect(heap);

  printf("\nDUMP 7, byte count = %d\n", mh_count(heap));
  
  mh_dump(heap);
  printf("\n\n");

  mh_cleanup(heap);
  free(heap);

  return 0;
}

/*
  Function:  mh_init
  Purpose:   To initilize the dynamically allocated memory in HeapType
       in:   the address of the HeapType
 */

void mh_init(HeapType *heap){

  heap->numBlocks = 0;
  heap->blocks = (BlockType *) calloc (MAX_BLK, sizeof(BlockType));

}

/*
  Function:  mh_cleanup
  Purpose:   To free the dynamically allocated memory in HeapType
       in:   the address of the HeapType
 */

void mh_cleanup(HeapType *heap){

  free(heap->blocks);

}

/*
  Function:  *mh_alloc
  Purpose:   To initilize the BlockType dynamically allocated memory
       in:   the address of the HeapType
       in:   the size of memory to be allocated
       in:   the label for the new memory
      out:   the address of the new memory
 */

void *mh_alloc(HeapType *heap, int n, char *label){
  
  int currBlock = heap->numBlocks;
  heap->blocks[heap->numBlocks].rsv = C_TRUE;
  heap->blocks[heap->numBlocks].addr = malloc(n);
  heap->blocks[heap->numBlocks].size = n;
  strcpy(heap->blocks[heap->numBlocks].tag, label);
  heap->numBlocks++;

  return heap->blocks[currBlock].addr;
}

/*
  Function:  mh_count
  Purpose:   To count the size of memory being stored
       in:   the address of the HeapType
 */

int mh_count(HeapType *heap){
  
  int size = 0;
  int i;
 
    for (i=0; i<heap->numBlocks; i++){
    if(heap->blocks[i].rsv == C_TRUE){
      size += heap->blocks[i].size;
    }
    
  }
  return size;
}

/*
  Function:  mh_dealloc
  Purpose:   To deallocate the memory stored at the address passed into the function
       in:   the address of the HeapType
       in:   the address of memory to be deallocated
 */

void mh_dealloc(HeapType *heap, void *addr){

  int i;

  for(i=0; i<heap->numBlocks; i++){

    if(heap->blocks[i].addr == addr){
      heap->blocks[i].rsv = C_FALSE;
      free(heap->blocks[i].addr);
      break;
    }
  }
}

/*
  Function:  mh_dump
  Purpose:   To dump the information about the dynamically allocated memory to the screen
       in:   the address of the HeapType
 */

void mh_dump(HeapType *heap){

  int i;

  for(i=0; i<heap->numBlocks; i++){
    if(heap->blocks[i].rsv == C_TRUE){
      printf("%20s:   %4d bytes stored at %p\n",  heap->blocks[i].tag,  heap->blocks[i].size,  heap->blocks[i].addr);
    }
  }

}

/*
  Function:  mh_collect
  Purpose:   To frees up any last reserved memory in the BlockType memory
       in:   the address of the HeapType
 */

void mh_collect(HeapType *heap){

  int i;

  for(i=0; i<heap->numBlocks; i++){

    if(heap->blocks[i].rsv == C_TRUE){
      heap->blocks[i].rsv = C_FALSE;
      free(heap->blocks[i].addr);
    }
  }
}
