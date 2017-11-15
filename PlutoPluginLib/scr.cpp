#include "stdafx.h"
#include "scr.h"
#include "base.h"

gentity_t* base::scr::get_entity(int object_number)
{
	return internal::scr_get_entity_pointer_(object_number);
}

DWORD base::scr::iprint_ln(gentity_t* entity, char* message)
{
	return base::internal::sv_send_server_command_pointer_(entity->state.number, 0, "%c \"%s\"", 102, message);	
}

DWORD base::scr::iprint_ln_bold(gentity_t* entity, char* message)
{
	return base::internal::sv_send_server_command_pointer_(entity->state.number, 0, "%c \"%s\"", 103, message);
}
