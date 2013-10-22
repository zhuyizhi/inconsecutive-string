#include "buffer_pool.h"

BufferPool* BufferPool::buffer_pool_instance = NULL;

BufferPool::BufferPool(int buffer_number):
	buffer_number(buffer_number), available_buffer_number(0)
{
}

BufferPool *BufferPool::get_buffer_pool()
{
	if(!buffer_pool_instance)
	{
		buffer_pool_instance = new BufferPool(INIT_BUFFER_NUMBER);
		if(!buffer_pool_instance->init())
			return NULL;
	}
	return buffer_pool_instance;
}

int BufferPool::init()
{
	buffers.clear();
	buffer_is_available.clear();
	for(int i = 0; i < buffer_number; i++)
	{
		InternalBuffer *buffer = new InternalBuffer();
		if(!buffer->init())
			return 0;
		buffers.push_back(buffer);
		buffer_is_available.push_back(true);
		available_buffer_number++;
	}

	return 1;
}

int BufferPool::next_available_buffer()
{
	for(int i = 0; i < buffer_is_available.size(); i++)
	{
		if(buffer_is_available[i])
			return i;
	}
	return -1;
}

int BufferPool::add_buffer()
{
	InternalBuffer *buffer = new InternalBuffer();
	if(!buffer->init())
		return -1;

	buffers.push_back(buffer);
	buffer_is_available.push_back(true);
	available_buffer_number++;
	return buffers.size() - 1;
}

InternalBuffer *BufferPool::get_buffer()
{
	int buffer_id;

	if((buffer_id = next_available_buffer()) < 0)
		if((buffer_id = add_buffer()) < 0)
			return NULL;
	buffer_is_available[buffer_id] = false;
	available_buffer_number--;
	return buffers[buffer_id];
}

int BufferPool::return_buffer(InternalBuffer *buffer)
{
	int i;
	for(i = 0; i < buffers.size(); i++)
	{
		if(buffers[i] == buffer)
			break;
	}

	if(i >= buffers.size())
		return 0;

	buffers[i]->clear();
	buffer_is_available[i] = true;
	available_buffer_number++;
	return 1;
}