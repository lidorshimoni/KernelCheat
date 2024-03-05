#include "dispatch.hpp"

void dispatch::handler(void* info_struct)
{
	ULONG status = STATUS_UNHANDLED;
	PINFO_STRUCT info = (PINFO_STRUCT)info_struct;

	if (info->code == CODE_MODULE_REQUEST)
	{	
		if (NULL == info->module_name)
		{
			info->status = STATUS_GOT_NULL_MODULE;
			goto Exit;
		}
		PEPROCESS target_process = NULL;
		if (NT_SUCCESS(PsLookupProcessByProcessId((HANDLE)info->process_id, &target_process)))
		{
			KAPC_STATE apc;
			LOG("module_name: %ws\n", info->module_name);
			KeStackAttachProcess(target_process, &apc);
			ULONG b = memory::get_module_base(target_process, L"Microvolts.exe");
			//ULONG b = memory::get_module_base(target_process, info->module_name); TODO FIX
			KeUnstackDetachProcess(&apc);
			if (b) { info->module_base = b; }
		}
	}
	else if (info->code == CODE_READ_MEMORY)
	{
		PEPROCESS target_process = NULL;
		if (NT_SUCCESS(PsLookupProcessByProcessId((HANDLE)info->process_id, &target_process)))
		{
			memory::read_memory(target_process, (void*)info->address, &info->buffer, info->size);
		}
	}
	else if (info->code == CODE_WRITE_MEMORY)
	{
		PEPROCESS target_process = NULL;
		if (NT_SUCCESS(PsLookupProcessByProcessId((HANDLE)info->process_id, &target_process)))
		{
			memory::write_memory(target_process, &info->buffer, (void*)info->address, info->size);
		}
	}
	status = STATUS_HANDLED;
Exit:
	info->status = status;
}

