//
//  buffer_pool.h
//  str2-local
//
//  Created by xiazhou on 10/22/13.
//  Copyright (c) 2013 xiazhou. All rights reserved.
//

#ifndef str2_local_buffer_pool_h
#define str2_local_buffer_pool_h

#include "internal_buffer.h"
#include "vector"

class BufferPool
{
public:
    ~BufferPool();
    static BufferPool* get_buffer_pool();
    
    InternalBuffer* get_buffer();
    InternalBuffer* return_buffer(int buffer_id);

private:
    int next_available_buffer();
    int add_buffer();
    
private:
    static BufferPool* buffer_pool_instance = NULL;
    
    std::vector<InternalBuffer *> buffers;
    std::vector<bool> buffer_is_available;
    int buffer_number;
    int available_buffer_number;
    
private:
    BufferPool();
    

};

#endif
