#include "memory.hpp"

ULONG memory::get_process_id_by_name(const char* process_name)
{
	ULONG process_id = 0;
	HANDLE ss = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	std::string process_name_str(process_name);
	std::wstring process_name_wide_str(process_name_str.begin(), process_name_str.end());

	if (ss)
	{
		PROCESSENTRY32 pe;
		pe.dwSize = sizeof(PROCESSENTRY32);
		if (Process32First(ss, &pe))
		{
			do
			{
				std::wstring temp_process_name(pe.szExeFile);
				//if (!strcmp((char*)pe.szExeFile, process_name))
				if(!process_name_wide_str.compare(temp_process_name))
				{
					process_id = pe.th32ProcessID;
					break;
				}
			} while (Process32Next(ss, &pe));
		}
		CloseHandle(ss);
	}
	return process_id;
}
