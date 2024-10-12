#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <Windows.h>

typedef unsigned long long u64;
typedef struct rfile
{
    void *handle;
    char *data;
    u64 length;
    bool valid;
} rfile;

#ifndef RIODEF
    #ifdef RIO_STATIC
        #define RIODEF static
    #else
        #define RIODEF extern
    #endif
#endif

RIODEF rfile rfile_open(const char *filename);
RIODEF rfile rfile_create(const char *filename);
RIODEF void rfile_read(rfile *self);
RIODEF void rfile_write(rfile *self, char *data, u64 len);
RIODEF void rfile_close(rfile *self);

#define _RIO_IMPLEMENTATION_
#ifdef _RIO_IMPLEMENTATION_

#ifdef _WIN32

RIODEF rfile rfile_open(const char *filename)
{
    rfile file = {0}; 
    //TODO: Check for errors
    file.handle = CreateFileA(filename, GENERIC_READ | GENERIC_WRITE,
                              0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL); 
    LARGE_INTEGER file_size = {0};
    GetFileSizeEx(file.handle, &file_size);
    file.length = file_size.QuadPart;
    file.data = VirtualAlloc(NULL, file.length, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    file.valid = true;
    return file;
}

RIODEF rfile rfile_create(const char *filename)
{
    rfile file = {0};

    file.handle = CreateFileA(filename, GENERIC_READ | GENERIC_WRITE,
                              0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
    file.valid = true;
    return file;
}

RIODEF void rfile_read(rfile *self)
{
    //TODO: Check for errors
    DWORD bytes_read = 0;
    ReadFile(self->handle, self->data, self->length, &bytes_read, NULL);
}

RIODEF void rfile_write(rfile *self, char *data, u64 len)
{
    //TODO: Check for errors
    DWORD bytes_written = 0;
    WriteFile(self->handle, data, len, &bytes_written, NULL);
}

RIODEF void rfile_close(rfile *self)
{
    //TODO: Check for errors
    VirtualFree(self->data, 0, MEM_RELEASE);
    CloseHandle(self->handle);
}

#else
    #error "Only Windows support"
#endif
#endif

