#pragma once
#include "datatypes.h"
namespace base
{
	namespace scr
	{
		gentity_t* get_entity(int object_number);
		namespace internal
		{
			typedef gentity_t*(__cdecl* scr_get_entity_t)(int object_number);
			static scr_get_entity_t scr_get_entity_pointer_ = (scr_get_entity_t)0x004B18E0;
		}
	}
}