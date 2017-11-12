#pragma once
#include "datatypes.h"
#include <functional>
namespace base
{
	typedef char*(__cdecl* g_say_t)(gentity_t* entity, team team, char* msg);
	typedef void(__cdecl* scr_player_killed_t)(gentity_t* player_who_died, gentity_t* inflictor, gentity_t* killer, int damage, int mod, int weapon_index, bool is_alternate_weapon, vec3_t direction, int hit_location, int unkown_0, int unknow_1);
	typedef void(__cdecl* scr_player_damaged_t)(gentity_t* player_who_was_damaged, gentity_t* inflictor, gentity_t* player_who_damanged, int damage, int unknown_0, int mod, int weapon_index, bool is_alternate_weapon, vec3_t direction, int unknown_1, int hit_location, int unknown_2);
	typedef void(__cdecl* client_connect_t)(int entity_number,short script_id);
	typedef void(__cdecl* client_disconnect_t)(int entity_number);
	typedef gentity_t*(__cdecl* gscr_get_entity_t)(int entity_number);

	class plugin_base
	{
	public:
		static void install_g_say_callback(std::function<void(gentity_t*, team, char*)> callback);
		static void install_client_connected_callback(std::function<void(int)> callback);
		static void install_client_disconnect_callback(std::function<void(int)> callback);
		static void install_scr_player_killed_callback(std::function<void(gentity_t*, gentity_t*, gentity_t*, int, int, int, bool, vec3_t, int)> callback);
		static void install_scr_player_damaged_callback(std::function<void(gentity_t*, gentity_t*, gentity_t*, int, int, int, bool, vec3_t, int)> callback);

		static gentity_t* gscr_get_entiy(int entity_number);

	private:
		static g_say_t g_say_pointer_;
		static scr_player_killed_t scr_player_killed_pointer_;
		static scr_player_damaged_t scr_player_damaged_pointer_;
		static client_connect_t client_connect_pointer_;
		static client_disconnect_t client_disconnect_pointer_;

		static gscr_get_entity_t gscr_get_entity_pointer_;

		static std::function<void(gentity_t*, team, char*)> g_say_callback_;
		static std::function<void(int)> client_connect_callback_;
		static std::function<void(int)> client_disconnect_callback_;
		static std::function<void(gentity_t*, gentity_t*, gentity_t*, int, int, int, bool, vec3_t, int)> scr_player_killed_callback_;
		static std::function<void(gentity_t*, gentity_t*, gentity_t*, int, int, int, bool, vec3_t, int)> scr_player_damaged_callback_;

		static char* hk_g_say(gentity_t* entity, team team, char* msg);
		static void hk_client_connect(int entity_number,short script_id);
		static void hk_client_disconnect(int entity_number);
		static void hk_scr_player_killed(gentity_t* player_who_died, gentity_t* inflictor, gentity_t* killer, int damage, int mod, int weapon_index, bool is_alternate_weapon, vec3_t direction, int hit_location, int unkown_0, int unknow_1);
		static void hk_scr_player_damaged(gentity_t* player_who_was_damaged, gentity_t* inflictor, gentity_t* player_who_damanged, int damage, int unknown_0, int mod, int weapon_index, bool is_alternate_weapon, vec3_t direction, int unknown_1, int hit_location, int unknown_2);

		static void* detour_function(BYTE * src, const BYTE * dst, const int len);

	};
}
