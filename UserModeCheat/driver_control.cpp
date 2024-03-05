#include "driver_control.hpp"

ULONG driver_control::get_module_base(ULONG process_id, WCHAR* module_name)
{
    INFO_STRUCT info = { 0 };
    info.code = CODE_MODULE_REQUEST;
    info.process_id = process_id;
    info.module_name = module_name;

    hook::call_hook(&info);
    if (STATUS_HANDLED != info.status)
        return -1;
    return info.module_base;
}
