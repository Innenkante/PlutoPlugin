#include "stdafx.h"
#include "gscr.h"
#include "base.h"

gentity_t* base::gscr::get_entity(int entity_number)
{
	return internal::gscr_get_entity_pointer_(entity_number);
}

DWORD base::gscr::iprint_ln(char* message)
{
	return base::internal::sv_send_server_command_pointer_(0, 0, "%c  \"%s\"", 102, message);
}

DWORD base::gscr::iprint_ln_bold(char* message)
{
	return base::internal::sv_send_server_command_pointer_(0, 0, "%c  \"%s\"", 103, message);
}
