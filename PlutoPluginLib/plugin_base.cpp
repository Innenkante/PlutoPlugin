#include "stdafx.h"
#include "plugin_base.h"


std::function<void(gentity_t*, team*, char*)> base::plugin_base::g_say_callback_ = nullptr;
std::function<void(gentity_t*)> base::plugin_base::client_connect_callback_ = nullptr;
std::function<void(gentity_t*)> base::plugin_base::client_disconnect_callback_ = nullptr;
std::function<void(gentity_t*, gentity_t*, gentity_t*, int*, int*, int*, bool*, vec3_t, int*)> base::plugin_base::scr_player_killed_callback_ = nullptr;
std::function<void(gentity_t*, gentity_t*, gentity_t*, int*, int*, int*, bool*, vec3_t, int*)> base::plugin_base::scr_player_damaged_callback_ = nullptr;


base::plugin_base::g_say_t base::plugin_base::g_say_pointer_ = nullptr;
base::plugin_base::scr_player_killed_t base::plugin_base::scr_player_killed_pointer_ = nullptr;
base::plugin_base::scr_player_damaged_t base::plugin_base::scr_player_damaged_pointer_ = nullptr;

base::plugin_base::gscr_get_entity_t base::plugin_base::gscr_get_entity_pointer_ = (gscr_get_entity_t)0x00494EB0;
base::plugin_base::scr_get_entity_t base::plugin_base::scr_get_entity_pointer_ = (scr_get_entity_t)0x004B18E0;

bool base::plugin_base::exec_ent_thread_hook_set = false;

int function_handle;
int object_ref;
int jump_back = 0x004F0289;
__declspec(naked) void hk_exec_ent_thread_num()
{
	__asm mov[function_handle], eax;
	__asm mov[object_ref], ecx;

	__asm pushad;
	__asm pushfd;

	base::plugin_base::exec_ent_thread_num_solve(function_handle, object_ref);

	__asm popfd;
	__asm popad;

	__asm push ebp;
	__asm mov ebp, esp;
	__asm and esp, 0x0FFFFFFF8;
	__asm sub esp, 8;

	__asm jmp[jump_back];
}

void base::plugin_base::install_g_say_callback(std::function<void(gentity_t*, team*, char*)> callback)
{
	g_say_callback_ = callback;
	g_say_pointer_ = (g_say_t)detour_function((BYTE*)0x0047E900, (BYTE*)hk_g_say, 0x6);
}

void base::plugin_base::install_client_connected_callback(std::function<void(gentity_t*)> callback)
{
	client_connect_callback_ = callback;
	
	if (!exec_ent_thread_hook_set)
	{
		detour_function((BYTE*)0x004F0280, (BYTE*)hk_exec_ent_thread_num, 0x6);
		exec_ent_thread_hook_set = true;
	}

}

void base::plugin_base::install_client_disconnect_callback(std::function<void(gentity_t*)> callback)
{
	client_disconnect_callback_ = callback;

	if (!exec_ent_thread_hook_set)
	{
		detour_function((BYTE*)0x004F0280, (BYTE*)hk_exec_ent_thread_num, 0x6);
		exec_ent_thread_hook_set = true;
	}
}

void base::plugin_base::install_scr_player_killed_callback(
	std::function<void(gentity_t*, gentity_t*, gentity_t*, int*, int*, int*, bool*, vec3_t, int*)> callback)
{
	scr_player_killed_callback_ = callback;
	scr_player_killed_pointer_ = (scr_player_killed_t)detour_function((BYTE*)0x004AD030, (BYTE*)hk_scr_player_killed, 0x6);
}

void base::plugin_base::install_scr_player_damaged_callback(
	std::function<void(gentity_t*, gentity_t*, gentity_t*, int*, int*, int*, bool*, vec3_t, int*)> callback)
{
	scr_player_damaged_callback_ = callback;
	scr_player_damaged_pointer_ = (scr_player_damaged_t)detour_function((BYTE*)0x004ACE50, (BYTE*)hk_scr_player_damaged, 0x6);
}


gentity_t* base::plugin_base::gscr_get_entiy(int entity_number)
{
	return gscr_get_entity_pointer_(entity_number);
}

gentity_t* base::plugin_base::scr_get_entity(int object_number)
{
	return scr_get_entity_pointer_(object_number);
}

char* base::plugin_base::hk_g_say(gentity_t* entity, team team, char* msg)
{
	g_say_callback_(entity, &team, msg);
	return g_say_pointer_(entity, team, msg);
}

void base::plugin_base::exec_ent_thread_num_solve(int function_handle, int object_ref)
{
	if (function_handle == 412300 && client_connect_callback_ != nullptr)
		client_connect_callback_(scr_get_entity(object_ref));
	if (function_handle == 412332 && client_disconnect_callback_ != nullptr)
		client_disconnect_callback_(scr_get_entity(object_ref));
}

void base::plugin_base::hk_scr_player_killed(gentity_t* player_who_died, gentity_t* inflictor, gentity_t* killer,
	int damage, int mod, int weapon_index, bool is_alternate_weapon, vec3_t direction, int hit_location, int unkown_0,
	int unknow_1)
{
	scr_player_killed_callback_(player_who_died, inflictor, killer, &damage, &mod, &weapon_index, &is_alternate_weapon, direction, &hit_location);
	return scr_player_killed_pointer_(player_who_died, inflictor, killer, damage, mod, weapon_index, is_alternate_weapon, direction, hit_location, unkown_0, unknow_1);
}

void base::plugin_base::hk_scr_player_damaged(gentity_t* player_who_was_damaged, gentity_t* inflictor,
	gentity_t* player_who_damanged, int damage, int unknown_0, int mod, int weapon_index, bool is_alternate_weapon,
	vec3_t direction, int unknown_1, int hit_location, int unknown_2)
{
	scr_player_damaged_callback_(player_who_was_damaged, inflictor, player_who_damanged, &damage, &mod, &weapon_index, &is_alternate_weapon, direction, &hit_location);
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
