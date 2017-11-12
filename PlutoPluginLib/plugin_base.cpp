#include "stdafx.h"
#include "plugin_base.h"


std::function<void(gentity_t*, team, char*)> base::plugin_base::g_say_callback_ = nullptr;
std::function<void(int)> base::plugin_base::client_connect_callback_ = nullptr;
std::function<void(int)> base::plugin_base::client_disconnect_callback_ = nullptr;
std::function<void(gentity_t*, gentity_t*, gentity_t*, int, int, int, bool, vec3_t, int)> base::plugin_base::scr_player_killed_callback_ = nullptr;
std::function<void(gentity_t*, gentity_t*, gentity_t*, int, int, int, bool, vec3_t, int)> base::plugin_base::scr_player_damaged_callback_ = nullptr;


base::g_say_t base::plugin_base::g_say_pointer_ = nullptr;
base::client_connect_t base::plugin_base::client_connect_pointer_ = nullptr;
base::client_disconnect_t base::plugin_base::client_disconnect_pointer_ = nullptr;
base::scr_player_killed_t base::plugin_base::scr_player_killed_pointer_ = nullptr;
base::scr_player_damaged_t base::plugin_base::scr_player_damaged_pointer_ = nullptr;

base::gscr_get_entity_t base::plugin_base::gscr_get_entity_pointer_ = (base::gscr_get_entity_t)0x00494EB0;

void base::plugin_base::install_g_say_callback(std::function<void(gentity_t*, team, char*)> callback)
{
	g_say_callback_ = callback;
	g_say_pointer_ = (g_say_t)detour_function((BYTE*)0x0047E900, (BYTE*)hk_g_say, 0x6);
}

void base::plugin_base::install_client_connected_callback(std::function<void(int)> callback)
{
	client_connect_callback_ = callback;
	client_connect_pointer_ = (client_connect_t)detour_function((BYTE*)0x004716A0, (BYTE*)hk_client_connect, 0x6); //
}

void base::plugin_base::install_client_disconnect_callback(std::function<void(int)> callback)
{
	client_disconnect_callback_ = callback;
	client_disconnect_pointer_ = (client_disconnect_t)detour_function((BYTE*)0x00471E60, (BYTE*)hk_client_disconnect, 0x5);
}

void base::plugin_base::install_scr_player_killed_callback(
	std::function<void(gentity_t*, gentity_t*, gentity_t*, int, int, int, bool, vec3_t, int)> callback)
{
	scr_player_killed_callback_ = callback;
	scr_player_killed_pointer_ = (scr_player_killed_t)detour_function((BYTE*)0x004AD030, (BYTE*)hk_scr_player_killed, 0x6);
}

void base::plugin_base::install_scr_player_damaged_callback(
	std::function<void(gentity_t*, gentity_t*, gentity_t*, int, int, int, bool, vec3_t, int)> callback)
{
	scr_player_damaged_callback_ = callback;
	scr_player_damaged_pointer_ = (scr_player_damaged_t)detour_function((BYTE*)0x004ACE50, (BYTE*)hk_scr_player_damaged, 0x6);
}


gentity_t* base::plugin_base::gscr_get_entiy(int entity_number)
{
	return gscr_get_entity_pointer_(entity_number);
}

char* base::plugin_base::hk_g_say(gentity_t* entity, team team, char* msg)
{
	g_say_callback_(entity, team, msg);
	return g_say_pointer_(entity, team, msg);
}

void base::plugin_base::hk_client_connect(int entity_number, short script_id)
{
	client_connect_callback_(entity_number);
	return client_connect_pointer_(entity_number, script_id);
}

void base::plugin_base::hk_client_disconnect(int entity_number)
{
	client_disconnect_callback_(entity_number);
	return client_disconnect_pointer_(entity_number);
}

void base::plugin_base::hk_scr_player_killed(gentity_t* player_who_died, gentity_t* inflictor, gentity_t* killer,
	int damage, int mod, int weapon_index, bool is_alternate_weapon, vec3_t direction, int hit_location, int unkown_0,
	int unknow_1)
{
	scr_player_killed_callback_(player_who_died, inflictor, killer, damage, mod, weapon_index, is_alternate_weapon, direction, hit_location);
	return scr_player_killed_pointer_(player_who_died, inflictor, killer, damage, mod, weapon_index, is_alternate_weapon, direction, hit_location, unkown_0, unknow_1);
}

void base::plugin_base::hk_scr_player_damaged(gentity_t* player_who_was_damaged, gentity_t* inflictor,
	gentity_t* player_who_damanged, int damage, int unknown_0, int mod, int weapon_index, bool is_alternate_weapon,
	vec3_t direction, int unknown_1, int hit_location, int unknown_2)
{
	scr_player_damaged_callback_(player_who_was_damaged, inflictor, player_who_damanged, damage, mod, weapon_index, is_alternate_weapon, direction, hit_location);
	return scr_player_damaged_pointer_(player_who_was_damaged, inflictor, player_who_damanged, damage, unknown_0, mod, weapon_index, is_alternate_weapon, direction, unknown_1, hit_location, unknown_2);
}


void* base::plugin_base::detour_function(BYTE* src, const BYTE* dst, const int len)
{
	BYTE* jmp = (BYTE*)malloc(len + 5);
	DWORD dwBack;

	VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &dwBack);
	memcpy(jmp, src, len);

	jmp += len;
	jmp[0] = 0xE9;

	*(DWORD*)(jmp + 1) = (DWORD)(src + len - jmp) - 5;

	src[0] = 0xE9;
	*(DWORD*)(src + 1) = (DWORD)(dst - src) - 5;
	for (int i = 5; i < len; i++)
		src[i] = 0x90;
	VirtualProtect(src, len, dwBack, &dwBack);

	return (jmp - len);
}
