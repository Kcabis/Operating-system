//Program to implement Interprocess communication between processes
#include <stdio.h>
#include <string.h>
 #include <windows.h> //using Windows API (Application Programming Interface) 

#define SHM_SIZE 1024

int main() {
    const char *sharedMemoryName = "SharedMemoryExample";
    
    HANDLE hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE,    
        NULL,                   
        PAGE_READWRITE,          
        0,                     
        SHM_SIZE,              
        sharedMemoryName        
    );

    if (hMapFile == NULL) {
        printf("Could not create file mapping object (%d).\n", GetLastError());
        return 1;
    }

    char *shared_mem = (char *)MapViewOfFile(
        hMapFile,               
        FILE_MAP_ALL_ACCESS,  
        0,                   
        0,                  
        SHM_SIZE               
    );

    if (shared_mem == NULL) {
        printf("Could not map view of file (%d).\n", GetLastError());
        CloseHandle(hMapFile);
        return 1;
    }

    const char *message = "Hello from Windows shared memory!";
    strcpy(shared_mem, message);
    printf("Data written to shared memory: %s\n", message);
    printf("Data read from shared memory: %s\n", shared_mem);

    UnmapViewOfFile(shared_mem);
    CloseHandle(hMapFile);

    return 0;
}

