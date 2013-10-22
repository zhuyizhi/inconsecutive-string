//
//  internal_buffer.cpp
//  str2-local
//
//  Created by xiazhou on 10/22/13.
//  Copyright (c) 2013 xiazhou. All rights reserved.
//

#include "internal_buffer.h"
#include "string.h"
#include "iostream"
//currently, just use new operator and doesn't throw false staus.
//Another option is using allocator.
InternalBuffer::~InternalBuffer(){
	delete[] first;
}
int InternalBuffer::init()
{
	try{
		first = new char[BUFFER_SIZE];
	}catch(std::bad_alloc){
		current_status = CORRUPTED;
		return 0;
	}
	
	current_status = EMPTY;
	return 1;
}

int InternalBuffer::clear(){
	pos = 0;
	length = 0;
	current_status = EMPTY;
	//An empty buffer doesn't have tail
	next = 0;
    
	return 1;
}

int InternalBuffer::write(const char* arr, int length)
{
	if(length <= 0)
		return length;
    
	int new_size = pos + length;
	int size_to_copy = new_size > BUFFER_SIZE ? BUFFER_SIZE - pos : length;
	memcpy(first + pos, arr, size_to_copy);
    
	pos += size_to_copy;
	if(pos > 0)
		if(pos == BUFFER_SIZE)
			current_status = FULL;
		else
			current_status = USING;
    
	return size_to_copy;
}

char* InternalBuffer::data(){
	return first;
}

int InternalBuffer::set_status(BUFFER_STATUS stat){
	current_status = stat;
	return 1;
}

int InternalBuffer::set_next(InternalBuffer* next_buffer){
	next = next_buffer;
	return 1;
}