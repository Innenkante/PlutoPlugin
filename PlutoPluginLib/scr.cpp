#include "stdafx.h"
#include "scr.h"

gentity_t* base::scr::get_entity(int object_number)
{
	return internal::scr_get_entity_pointer_(object_number);
}
