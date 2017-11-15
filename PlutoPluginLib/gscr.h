#pragma once
#include "datatypes.h"

namespace base
{
	namespace gscr
	{
		gentity_t* get_entity(int entity_number);

		DWORD iprint_ln(char* message);
		DWORD iprint_ln_bold(char* message);

		namespace internal
		{
			typedef gentity_t*(__cdecl* gscr_get_entity_t)(int entity_number);
			static gscr_get_entity_t gscr_get_entity_pointer_ = (gscr_get_entity_t)0x00494EB0;
		}
	}

}
