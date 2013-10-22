//
//  main.cpp
//  str2-local
//
//  Created by xiazhou on 10/22/13.
//  Copyright (c) 2013 xiazhou. All rights reserved.
//

#include <iostream>
#include "string"
#include "..\internal_buffer.h"
#include "..\buffer_pool.h"

int main(int argc, const char * argv[])
{

    InternalBuffer *buffer = new InternalBuffer();
    buffer->init();
    char *str = "Hello, string~";
    buffer->write(str, strlen(str));
    
	BufferPool *pool = BufferPool::get_buffer_pool();

	int times = 24;
	while(times--)
	{
		InternalBuffer *buffer = pool->get_buffer();

		if(times == 3)
			pool->return_buffer(buffer);
		
	}

	system("pause");
    return 0;
}

