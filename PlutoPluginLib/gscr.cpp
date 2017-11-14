#include "stdafx.h"
#include "gscr.h"

gentity_t* base::gscr::get_entity(int entity_number)
{
	return internal::gscr_get_entity_pointer_(entity_number);
}
