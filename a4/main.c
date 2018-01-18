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
