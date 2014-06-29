#include "unity.h"
#include "GenericCircularBuffer.h"
#include "malloc.h"
#include "stdio.h"
#include "CException.h"
#include "Integer.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_circularBufferNew_given_3_should_create_new_int_buffer(void)
{
	CircularBuffer *cb = circularBufferNew(3, sizeof(int));
	
	TEST_ASSERT_NOT_NULL(cb);
	TEST_ASSERT_NOT_NULL(cb->buffer);
	TEST_ASSERT_EQUAL(3, cb->length);
	TEST_ASSERT_EQUAL(0, cb->size);
	TEST_ASSERT_EQUAL(sizeof(int), cb->sizeOfType);
	TEST_ASSERT_EQUAL_PTR(cb->buffer, cb->head);
	TEST_ASSERT_EQUAL_PTR(cb->buffer, cb->tail);
	
	circularBufferDel(cb);
}

void test_circularBufferNew_given_3pt5_should_create_new_double_buffer(void)
{
	CircularBuffer *cb = circularBufferNew(3.5, sizeof(double));
	
	TEST_ASSERT_NOT_NULL(cb);
	TEST_ASSERT_NOT_NULL(cb->buffer);
	TEST_ASSERT_EQUAL(3.5, cb->length);
	TEST_ASSERT_EQUAL(0, cb->size);
	TEST_ASSERT_EQUAL(sizeof(double), cb->sizeOfType);
	TEST_ASSERT_EQUAL_PTR(cb->buffer, cb->head);
	TEST_ASSERT_EQUAL_PTR(cb->buffer, cb->tail);
	
	circularBufferDel(cb);
}

void test_circularBufferAdd_should_add_1_integer(void)
{
	CircularBuffer *cb = circularBufferNew(7, sizeof(int));
	int integer = 3;
	
	circularBufferAdd(cb, &integer, copyInt);
	
	TEST_ASSERT_NOT_NULL(cb);
	TEST_ASSERT_NOT_NULL(cb->buffer);
	TEST_ASSERT_EQUAL(7, cb->length);
	TEST_ASSERT_EQUAL(sizeof(int), cb->sizeOfType);
	TEST_ASSERT_EQUAL(1, cb->size);
	TEST_ASSERT_EQUAL(3, *((int *)cb->tail));
	

}

void test_circularBufferAdd_given_length1_but_add2number_should_give_exception(void)
{
	CircularBuffer *cb = circularBufferNew(1, sizeof(int));
	int int1=1;
	int int2=2;
		
	CEXCEPTION_T err;
	
	
	Try	  	 {	circularBufferAdd(cb, &int1, copyInt);
				circularBufferAdd(cb, &int2, copyInt);	 }	
				
  Catch(err)  {  TEST_ASSERT_EQUAL(ERR_BUFFER_IS_FULL, err);
				printf("Success: Exception generated. Error code: %d.\n", err);}
}


void test_circularBufferRemove_given_length2_remove_1value_should_remove(void){


	CircularBuffer *cb = circularBufferNew(2, sizeof(int));
	int int1=1;
	
	circularBufferAdd(cb, &int1, copyInt);
	circularBufferRemove(cb, &int1, copyInt);
	
	TEST_ASSERT_NOT_NULL(cb);
	TEST_ASSERT_NOT_NULL(cb->buffer);
	TEST_ASSERT_EQUAL(2, cb->length);
	TEST_ASSERT_EQUAL(sizeof(int), cb->sizeOfType);
	TEST_ASSERT_EQUAL(0, cb->size);
	

}
	

void test_circularBufferRemove_given_length1_but_remove_2value_should_give_exception(void){


	CircularBuffer *cb = circularBufferNew(2, sizeof(int));
	int int1=1;
	int int2=2;
		
	CEXCEPTION_T err;
	
	
	Try	  	 {	circularBufferAdd(cb, &int1, copyInt);
				circularBufferAdd(cb, &int2, copyInt);	 
				circularBufferRemove(cb, &int1, copyInt);
				circularBufferRemove(cb, &int2, copyInt);}	
				
  Catch(err)  {  TEST_ASSERT_EQUAL(ERR_BUFFER_IS_EMPTY, err);
				printf("Success: Exception generated. Error code: %d.\n", err);}
}
	
