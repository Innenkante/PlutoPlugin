// dllmain.cpp : Definiert den Einstiegspunkt für die DLL-Anwendung.
#include "stdafx.h"
#include "datatypes.h"
#include "plugin_base.h"

typedef void(__cdecl* sys_print_t)(char* a1);
sys_print_t sys_print = (sys_print_t)0x004D8E80;

void client_say(gentity_t* entity, team t,char* msg)
{
	char buffer[256];
	sprintf_s(buffer, "%s || %i || %s \n", entity->shared.client->session.clientstate.name, t, msg);
	sys_print(buffer);
}

void client_connect(int entity)
{
	auto ent = base::plugin_base::gscr_get_entiy(entity);
	char buffer[256];

	sprintf_s(buffer, "%s connected! \n", ent->shared.client->session.clientstate.name);

	sys_print(buffer);
}

void client_disconnect(int entity)
{
	auto ent = base::plugin_base::gscr_get_entiy(entity);
	char buffer[256];

	sprintf_s(buffer, "%s disconnected! \n", ent->shared.client->session.clientstate.name);

	sys_print(buffer);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		sys_print("Hay motherfucker I am here \n");
		base::plugin_base::install_g_say_callback(client_say);
		base::plugin_base::install_client_connected_callback(client_connect);
		base::plugin_base::install_client_disconnect_callback(client_disconnect);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

