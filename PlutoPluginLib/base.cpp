#include "stdafx.h"
#include "base.h"
#include "scr.h"

int function_handle;
int object_ref;
int jump_back = 0x004F0289;
__declspec(naked) void hk_exec_ent_thread_num()
{
	__asm mov[function_handle], eax;
	__asm mov[object_ref], ecx;

	__asm pushad;
	__asm pushfd;

	base::internal::exec_ent_thread_num_helper(function_handle, object_ref);

	__asm popfd;
	__asm popad;

	__asm push ebp;
	__asm mov ebp, esp;
	__asm and esp, 0x0FFFFFFF8;
	__asm sub esp, 8;

	__asm jmp[jump_back];
}

void base::install_g_say_callback(std::function<void(gentity_t*, team*, char*)> callback)
{
	internal::g_say_callback_ = callback;
	internal::g_say_pointer_ = (internal::g_say_t)internal::detour_function((BYTE*)0x0047E900, (BYTE*)internal::hk_g_say, 0x6);
}

void base::install_client_connected_callback(std::function<void(gentity_t*)> callback)
{
	internal::client_connect_callback_ = callback;
	
	if (!internal::exec_ent_thread_hook_set)
	{
		internal::detour_function((BYTE*)0x004F0280, (BYTE*)hk_exec_ent_thread_num, 0x6);
		internal::exec_ent_thread_hook_set = true;
	}

}

void base::install_client_disconnect_callback(std::function<void(gentity_t*)> callback)
{
	internal::client_disconnect_callback_ = callback;

	if (!internal::exec_ent_thread_hook_set)
	{
		internal::detour_function((BYTE*)0x004F0280, (BYTE*)hk_exec_ent_thread_num, 0x6);
		internal::exec_ent_thread_hook_set = true;
	}
}

void base::install_scr_player_killed_callback(
	std::function<void(gentity_t*, gentity_t*, gentity_t*, int*, int*, int*, bool*, vec3_t, int*)> callback)
{
	internal::scr_player_killed_callback_ = callback;
	internal::scr_player_killed_pointer_ = (internal::scr_player_killed_t)internal::detour_function((BYTE*)0x004AD030, (BYTE*)internal::hk_scr_player_killed, 0x6);
}

void base::install_scr_player_damaged_callback(
	std::function<void(gentity_t*, gentity_t*, gentity_t*, int*, int*, int*, bool*, vec3_t, int*)> callback)
{
	internal::scr_player_damaged_callback_ = callback;
	internal::scr_player_damaged_pointer_ = (internal::scr_player_damaged_t)internal::detour_function((BYTE*)0x004ACE50, (BYTE*)internal::hk_scr_player_damaged, 0x6);
}

void base::install_client_spawn_callback(std::function<void(gentity_t*)> callback)
{
	internal::client_spawn_callback_ = callback;
	internal::client_spawn_pointer_ = (internal::client_spawn_t)internal::detour_function((BYTE*)0x00471980, (BYTE*)internal::hk_client_spawn, 0x6);
}

void base::say_all(char* message)
{
	internal::sv_send_server_command_pointer_(0, 0, "%c \"\x15%s\"", 84, message);
}


char* base::internal::hk_g_say(gentity_t* entity, team team, char* msg)
{
	g_say_callback_(entity, &team, msg);
	return g_say_pointer_(entity, team, msg);
}

void base::internal::exec_ent_thread_num_helper(int function_handle, int object_ref)
{
	if (function_handle == 412300 && client_connect_callback_ != nullptr)
		client_connect_callback_(scr::get_entity(object_ref));
	if (function_handle == 412332 && client_disconnect_callback_ != nullptr)
		client_disconnect_callback_(scr::get_entity(object_ref));
}

void base::internal::hk_scr_player_killed(gentity_t* player_who_died, gentity_t* inflictor, gentity_t* killer,
	int damage, int mod, int weapon_index, bool is_alternate_weapon, vec3_t direction, int hit_location, int unkown_0,
	int unknow_1)
{
	scr_player_killed_callback_(player_who_died, inflictor, killer, &damage, &mod, &weapon_index, &is_alternate_weapon, direction, &hit_location);
	return scr_player_killed_pointer_(player_who_died, inflictor, killer, damage, mod, weapon_index, is_alternate_weapon, direction, hit_location, unkown_0, unknow_1);
}

void base::internal::hk_scr_player_damaged(gentity_t* player_who_was_damaged, gentity_t* inflictor,
	gentity_t* player_who_damanged, int damage, int unknown_0, int mod, int weapon_index, bool is_alternate_weapon,
	vec3_t direction, int unknown_1, int hit_location, int unknown_2)
{
	scr_player_damaged_callback_(player_who_was_damaged, inflictor, player_who_damanged, &damage, &mod, &weapon_index, &is_alternate_weapon, direction, &hit_location);
	return scr_player_damaged_pointer_(player_who_was_damaged, inflictor, player_who_damanged, damage, unknown_0, mod, weapon_index, is_alternate_weapon, direction, unknown_1, hit_location, unknown_2);
}

void base::internal::hk_client_spawn(gentity_t* entity, vec3_t spawn_position, vec3_t view_angle)
{
	client_spawn_callback_(entity);
	return client_spawn_pointer_(entity, spawn_position, view_angle);
}


void* base::internal::detour_function(BYTE* src, const BYTE* dst, const int len)
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