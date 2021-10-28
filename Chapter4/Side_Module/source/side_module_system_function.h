#pragma once


#ifndef SIDE_MODULE_SYSTEM_FUNCTION_H_
#define SIDE_MODULE_SYSTEM_FUNCTION_H_

#include <stdio.h>

void InsertIntoAllocatedArray(int new_item_index, int offset_start, int size_needed);

int Create_Buffer(int size_needed);
void free_buffer(int offset);

char* strcpy(char* destination, const char* source);
size_t strlen(const char* value);

int atoi(const char* value);

#endif // SIDE_MODULE_SYSTEM_FUNCTION_H_