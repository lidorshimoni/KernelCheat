#pragma once

#include <Windows.h>
#include <iostream>

#define LOG(fmt, ...) printf("[Microvolts-Cheat] - %s:%s:%d: " fmt, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)

#define PROCESS_NAME "Microvolts.exe"
#define MODULE_NAME L"Microvolts.exe"

#define CODE_MODULE_REQUEST 0x1
#define CODE_READ_MEMORY 0x2
#define CODE_WRITE_MEMORY 0x3

#define STATUS_UNHANDLED 0x0
#define STATUS_HANDLED 0x1

typedef struct _INFO_STRUCT
{
	ULONG code;
	ULONG process_id;
	WCHAR* module_name;
	ULONG module_base;
	ULONG address;
	ULONG buffer;
	ULONG size;
	ULONG status;
}INFO_STRUCT, * PINFO_STRUCT;