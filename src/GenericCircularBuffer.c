#include "GenericCircularBuffer.h"
#include "malloc.h"
#include "stdio.h"
#include "Integer.h"
#include "CException.h"


CircularBuffer *circularBufferNew(int length, int sizeOfType){
	CircularBuffer *cb;
	
	cb = malloc(sizeof(CircularBuffer));
	cb->buffer = malloc(sizeOfType * length);
	cb->length = length;
	cb->size = 0;
	cb->sizeOfType = sizeOfType;
	cb->head=cb->buffer;
	cb->tail=cb->buffer;
	
	return cb;
}


 void circularBufferDel(CircularBuffer *cb)
 {
	if(cb)
	{
		if(cb->buffer)
			free(cb->buffer);

		free(cb);
	}
 }
 
 int circularBufferIsFull(CircularBuffer *cb){

  if(cb->size > cb->length)
		return 1;

	 return 0;
  
}

int circularBufferIsEmpty(CircularBuffer *cb)
{
  if (cb->length ==0 )
		return 1 ;

		return 0 ;

}
 
 
 
void circularBufferAdd(CircularBuffer *cb, void *obj, void (*copy)(void *, void *)){

	
	 if (!circularBufferIsFull(cb)) //if buffer is not full 
	 {
	    
		copy(obj, cb->buffer);
		cb->buffer++; 
		cb->size++; 
	 
	 
	   if(cb->size ==0)   // if size is empty then copy obj to tail
	    copy(obj, cb->tail);
	   else if (cb->size !=0)  //if size is noy empty then copy obj to head 
	    copy(obj, cb->head); 
		
	   else 
	  cb->head++;
	 
	  
	 }
	 else
	 Throw (ERR_BUFFER_IS_FULL);  //if buffer is full throw error
	 
	 
}	
	
	
	
	
void circularBufferRemove(CircularBuffer *cb, void *obj, void (*copy)(void *, void *))
{
   if(circularBufferIsEmpty(cb))  //if buffer is empty return err
   Throw (ERR_BUFFER_IS_EMPTY);
   
   else
   copy(obj , cb->tail);
    cb->tail++; 
	cb->size -- ;


}

