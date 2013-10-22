//
//  internal_buffer.h
//  str2-local
//
//  Created by xiazhou on 10/22/13.
//  Copyright (c) 2013 xiazhou. All rights reserved.
//

#ifndef str2_local_internal_buffer_h
#define str2_local_internal_buffer_h

enum BUFFER_STATUS{
	CORRUPTED,
	EMPTY,
	USING,
	FULL
};

static const int BUFFER_SIZE = 1024 * 1024;

class InternalBuffer
{
public:
	InternalBuffer():first(0), pos(0), length(0), current_status(CORRUPTED), next(0){};
	~InternalBuffer();
	int init();//init will allocate memory
	int clear();
	int write(const char*, int length);
	char* data();
	int set_status(BUFFER_STATUS stat);
	inline BUFFER_STATUS status(){return current_status;};
	inline int size(){return length;};
	int set_next(InternalBuffer* next_buffer);
	InternalBuffer* next;
    
private:
	char* first;
	int pos;//next empty place
	int length;
	BUFFER_STATUS current_status;
	//static std::allocator<char> alloc;
};


#endif
