#pragma once
#include "datatypes.h"
#include <functional>
namespace base
{
	class plugin_base
	{
	public:
		static void install_g_say_callback(std::function<void(gentity_t*, team*, char*)> callback);
		static void install_client_connected_callback(std::function<void(gentity_t*)> callback);
		static void install_client_disconnect_callback(std::function<void(gentity_t*)> callback);
		static void install_scr_player_killed_callback(std::function<void(gentity_t*, gentity_t*, gentity_t*, int*, int*, int*, bool*, vec3_t, int*)> callback);
		static void install_scr_player_damaged_callback(std::function<void(gentity_t*, gentity_t*, gentity_t*, int*, int*, int*, bool*, vec3_t, int*)> callback);

		static gentity_t* gscr_get_entiy(int entity_number);
		static gentity_t* scr_get_entity(int object_number);

		static void* detour_function(BYTE * src, const BYTE * dst, const int len);

		static void exec_ent_thread_num_solve(int function_handle, int object_ref);
	private:

		typedef char*(__cdecl* g_say_t)(gentity_t* entity, team team, char* msg);
		typedef void(__cdecl* scr_player_killed_t)(gentity_t* player_who_died, gentity_t* inflictor, gentity_t* killer, int damage, int mod, int weapon_index, bool is_alternate_weapon, vec3_t direction, int hit_location, int unkown_0, int unknow_1);
		typedef void(__cdecl* scr_player_damaged_t)(gentity_t* player_who_was_damaged, gentity_t* inflictor, gentity_t* player_who_damanged, int damage, int unknown_0, int mod, int weapon_index, bool is_alternate_weapon, vec3_t direction, int unknown_1, int hit_location, int unknown_2);
		typedef gentity_t*(__cdecl* gscr_get_entity_t)(int entity_number);
		typedef gentity_t*(__cdecl* scr_get_entity_t)(int obj_entity_number);

		static g_say_t g_say_pointer_;
		static scr_player_killed_t scr_player_killed_pointer_;
		static scr_player_damaged_t scr_player_damaged_pointer_;
		static scr_get_entity_t scr_get_entity_pointer_;

		static gscr_get_entity_t gscr_get_entity_pointer_;

		static std::function<void(gentity_t*, team*, char*)> g_say_callback_;
		static std::function<void(gentity_t*)> client_connect_callback_;
		static std::function<void(gentity_t*)> client_disconnect_callback_;
		static std::function<void(gentity_t*, gentity_t*, gentity_t*, int*, int*, int*, bool*, vec3_t, int*)> scr_player_killed_callback_;
		static std::function<void(gentity_t*, gentity_t*, gentity_t*, int*, int*, int*, bool*, vec3_t, int*)> scr_player_damaged_callback_;

		static char* hk_g_say(gentity_t* entity, team team, char* msg);

		static bool exec_ent_thread_hook_set;

		static void hk_scr_player_killed(gentity_t* player_who_died, gentity_t* inflictor, gentity_t* killer, int damage, int mod, int weapon_index, bool is_alternate_weapon, vec3_t direction, int hit_location, int unkown_0, int unknow_1);
		static void hk_scr_player_damaged(gentity_t* player_who_was_damaged, gentity_t* inflictor, gentity_t* player_who_damanged, int damage, int unknown_0, int mod, int weapon_index, bool is_alternate_weapon, vec3_t direction, int unknown_1, int hit_location, int unknown_2);

	};
}
