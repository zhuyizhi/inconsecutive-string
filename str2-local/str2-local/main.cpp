//
//  main.cpp
//  str2-local
//
//  Created by xiazhou on 10/22/13.
//  Copyright (c) 2013 xiazhou. All rights reserved.
//

#include <iostream>
#include "string"
#include "internal_buffer.h"

int main(int argc, const char * argv[])
{

    InternalBuffer *buffer = new InternalBuffer();
    buffer->init();
    char *str = "Hello, string~";
    buffer->write(str, strlen(str));
    
    std::cout << "Hello, World!\n";
    return 0;
}

