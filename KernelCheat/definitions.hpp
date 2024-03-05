#pragma once

#include "ntapi.hpp"

#define LOG(fmt, ...) DbgPrintEx(0, 0, "[Lidor-Driver] - %s:%s:%d: " fmt, __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)

#define CODE_MODULE_REQUEST 0x1
#define CODE_READ_MEMORY 0x2
#define CODE_WRITE_MEMORY 0x3

#define STATUS_UNHANDLED 0x0
#define STATUS_HANDLED 0x1
#define STATUS_GOT_NULL_MODULE 0x2

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