#include "dispatch.hpp"


extern "C" NTSTATUS DriverEntry(PDRIVER_OBJECT driver_object, PUNICODE_STRING registry_path)
{
	UNREFERENCED_PARAMETER(driver_object);
	UNREFERENCED_PARAMETER(registry_path);
	LOG("Loading driver...\n");

	bool hook_result = hook::init_hook(&dispatch::handler);
	
	if (hook_result)
	{
		LOG("Hook applied Successfuly! \n");
	}
	else
	{
		LOG("ERROR = Failed to apply hook! \n");
	}

	LOG("driver loaded! \n");

	return STATUS_SUCCESS;
}