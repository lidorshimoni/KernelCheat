#include "cheat.hpp"

void cheat::run()
{
	LOG("Looking for %s process...\n", PROCESS_NAME);
	ULONG process_id = memory::get_process_id_by_name(PROCESS_NAME);
	if (process_id)
	{
		LOG("Process identifier found: %d\n", process_id);
		LOG("Looking for module: %ws...\n", MODULE_NAME);
		ULONG module_base = driver_control::get_module_base(process_id, (WCHAR*)MODULE_NAME);
		if (module_base)
		{
			LOG("%ws found: 0x%x\n", MODULE_NAME, module_base);
			LOG("Running...\n");
			
			while (1)
			{
				Sleep(500);

				ULONG ptr = driver_control::read_memory<ULONG>(process_id, module_base + 0xE60B38);
				LOG("ptr1 = %x\n", ptr);
				if (0 == ptr)
					continue;
				ULONG ptr2 = driver_control::read_memory<ULONG>(process_id, ptr + 0x7c);
				LOG("ptr2 = %x\n", ptr2);
				if (0 == ptr2)
					continue;
				ULONG ptr3 = driver_control::read_memory<ULONG>(process_id, ptr + 0x10c);
				LOG("ptr3 = %x\n", ptr3);
				if (0 == ptr3)
					continue;
				ULONG ptr4 = driver_control::read_memory<ULONG>(process_id, ptr + 0x10);
				LOG("ptr4 = %x\n", ptr4);
				if (0 == ptr4)
					continue;
				ULONG ptr5 = driver_control::read_memory<ULONG>(process_id, ptr + 0xc);
				LOG("ptr5 = %d\n", ptr5);
				if (0 == ptr5)
					continue;
				//uint32_t result = driver_control::read_memory<uint32_t>(process_id, player_obj_ptr + 0xEC);
				//driver_control::write_memory<uintk32_t>(process_id, player_obj_ptr + 0xEC, 1337);
				//driver_control::write_memory<uint32_t>(process_id, player_obj_ptr + 0x138, 1337);
				//LOG("health = %d\n", result);
			}

			/*for (;0;)
			{
				ULONG my_player = driver_control::read_memory<ULONG>(process_id, module_base + m_dwLocalPlayer);
				if (my_player <= 0) { continue; }

				ULONG my_team = driver_control::read_memory<ULONG>(process_id, my_player + m_iTeamNum);
				ULONG my_cross = driver_control::read_memory<ULONG>(process_id, my_player + m_iCrossHairID);

				if (my_cross >= 1 && my_cross <= 64)
				{
					ULONG entity = driver_control::read_memory<ULONG>(process_id, module_base + m_dwEntityList + ((my_cross - 1) * 0x10));
					if (entity <= 0) { continue; }

					ULONG entity_health = driver_control::read_memory<ULONG>(process_id, entity + m_iHealth);
					ULONG entity_team = driver_control::read_memory<ULONG>(process_id, entity + m_iTeamNum);

					if (entity_health > 0 && entity_team != my_team && entity_team > 1)
					{
						Sleep(3);
						mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
						Sleep(1);
						mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
					}
				}
				Sleep(1);
			}*/
		}
		else
		{
			LOG("Failed to obtain %ws\n", MODULE_NAME);
		}
	}
	else
	{
		LOG("Failed to find %s process\n", PROCESS_NAME);
	}
}
