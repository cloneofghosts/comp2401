#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mhDefs.h"
#include "stuDefs.h"


/*
  Function:  mh_init
  Purpose:   To initilize the dynamically allocated memory in HeapType and set the head of the linked list to NULL
       in:   the address of the HeapType
 */

void mh_init(HeapType *heap){
  heap->numBlocks = 0;
  heap->blocks = NULL;

}

/*
  Function:  mh_cleanup
  Purpose:   To free up any last information contained in the linked list by using the function mh_collect which does this for us
       in:   the address of the HeapType
 */

void mh_cleanup(HeapType *heap){

  mh_collect(heap);

}

/*
  Function:  *mh_alloc
  Purpose:   To initilize the the newly created node and add it to the very end of the linked list
       in:   the address of the HeapType
       in:   the size of memory to be allocated
       in:   the label for the new memory
      out:   the address of the new memory
 */


void *mh_alloc(HeapType *heap, int n, char *label){

  BlockNode *newNode, *currNode, *prevNode;

  //allocates the memory for newNode and the data accociated with that node
  newNode = (BlockNode *) malloc(sizeof(BlockNode));
  newNode->data = (BlockType *) malloc(sizeof(BlockType));
  newNode->next = NULL;
  currNode = heap->blocks;
  prevNode = NULL;

  //loops to the end of the list to make sure that the data is added to the end of the list
  while(currNode != NULL){
    prevNode = currNode;
    currNode = currNode->next;
  }
 
  //checks to see if the element is being added to the start of the list
  if(prevNode == NULL)
    heap->blocks = newNode;
  else
     prevNode->next = newNode;
    
  //initilizes data
  newNode->data->rsv = C_TRUE;
  newNode->data->addr = malloc(n);
  newNode->data->size = n;
  strcpy(newNode->data->tag, label);

  return newNode->data->addr;
}

/*
  Function:  mh_count
  Purpose:   To count the size of memory being stored
       in:   the address of the HeapType
 */



int mh_count(HeapType *heap){
  
  int size = 0;
  BlockNode *currNode = heap->blocks;

  //loops over the linked list and calculates the size of the list
  while(currNode != NULL){
    size += currNode->data->size;
    currNode = currNode->next;
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
  BlockNode *currNode, *prevNode;

  currNode = heap->blocks;
  prevNode = NULL;

  while(currNode != NULL){
    //compaires the current address in memory to the one passed into the function
    if(currNode->data->addr == addr)
      break;
    prevNode = currNode;
    currNode = currNode->next;
  }

  //checks to see if the head of the list is empty and returns if it is
  if(currNode == NULL)
    return;

  //checks to see if the node we are deleting is the first element of the list
  if(prevNode == NULL){
    heap->blocks = currNode->next;
  }
  //the case where we are deleting from the middle or the end of the list
  else{
    prevNode->next = currNode->next;
  }

  //frees all data accociated with that node
  free(currNode->data->addr);
  free(currNode->data);
  free(currNode);
}

/*
  Function:  mh_dump
  Purpose:   To dump the information about the dynamically allocated memory to the screen
       in:   the address of the HeapType
 */


void mh_dump(HeapType *heap){

  int i;
  BlockNode *currNode = heap->blocks;

  while(currNode != NULL){
    printf("%20s:   %4d bytes stored at %p\n",  currNode->data->tag,  currNode->data->size,  currNode->data->addr);
    currNode = currNode->next;
  }
  
}

/*
  Function:  mh_collect
  Purpose:   To frees up any last reserved memory in the BlockType memory
       in:   the address of the HeapType
 */


void mh_collect(HeapType *heap){

  int i;
  BlockNode *currNode, *nextNode;

  currNode = heap->blocks;

  while(currNode != NULL){
    //sets the nextNode to the next element of the list so we can continue to loop through the list after the data is freed
    nextNode = currNode->next;
    //sets the head of the list to the next element in the list
    heap->blocks = currNode->next;
    //frees all data from currNode
    free(currNode->data->addr);
    free(currNode->data);
    free(currNode);
    currNode = nextNode;
  }
}
