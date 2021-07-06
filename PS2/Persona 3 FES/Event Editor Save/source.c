//Hamo Lib hasnt realeased yet but may as well
#include "lib/hamolib.h"


hook_call(fopen, 0x0038e8e4)


hook_call(fopen, 0x0038e8f8)

hook_ovr(fwrite, 0x004c0420)

hook_ovr(fclose, 0x004c0370)

//004c0370


func(malloc, 0x00191af0, 0x007d2cf0, void*, unsigned int size)

func(scePrintf, 0x5225a8, 0x007d2cf0, int, const char* format, ...)


typedef unsigned int uint;

typedef struct {
	void* fileData;
	unsigned int fileSize;
	uint currentSize;
	char* name;
} fileHandle;



void* fopen(char* name, char* mode) {
	scePrintf("P3 Event Editor File Save by Tupelov \nVersion 1.0\n");
	scePrintf("Opened file: %s\n", name);
	scePrintf("In mode: %s\n", mode);

	fileHandle* handle = (fileHandle*)malloc(sizeof(fileHandle));

	handle->fileData = malloc(0xFFFF);
	handle->fileSize = 0xFFFFF;
	handle->currentSize = 0;
	scePrintf("Size: %d\n", sizeof(fileHandle));

	int i;
	for (i = 0; i < handle->fileSize; i++)
	{
		((char*)handle->fileData)[i] = 0;

	}


	scePrintf("FileHandle is at: %08X\n", handle);
	scePrintf("File is at: %08X\n", handle->fileData);
	//hexDump("file", &handle, sizeof(fileHandle));
	scePrintf("\n");
	return handle;
}

fwrite(const void* data, uint size, uint count, fileHandle * handle) {

	int i;
	int j;
	int dataCount = 0;
	unsigned char buff[17];
	unsigned char* pc = (unsigned char*)data;

	for(j = 0; j< count; j++){
		for (i = 0; i < size; i++) {
			((char*)handle->fileData)[handle->currentSize]=((char*)data)[dataCount];
			handle->currentSize += 1;
			dataCount += 1;
		}
	}
	return;
}




fclose(fileHandle* handle) {

	scePrintf("P3 Event Editor File Save by Tupelov \nVersion 1.0\n");
	scePrintf("-----Warning! I am too lazy to prevent a memory leak!-----\n");
	scePrintf("FileHandle is at: %08X\n", handle);
	scePrintf("File is at: %08X\n", handle->fileData);
	scePrintf("Name: %s\n", handle->name);
	//20000000
	scePrintf("Cheat Engine Addresses:\n");

	scePrintf("Start: %08X\n", (handle->fileData+0x20000000));
	scePrintf("End: %08X\n", (handle->currentSize+handle->fileData + 0x20000000-1));

	scePrintf("\n");
}
