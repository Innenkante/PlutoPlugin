#pragma once
#include <Windows.h>

typedef float vec3_t[3];
typedef BYTE byte;

enum gentity_flags
{
	God = 0x1,
	Demigod = 0x2,
	NoTarget = 0x4,
};

enum entity_type
{
	ENTTYPE_SCRIPTVEHICLE = 0x11,
};

struct unk_weapon_info_t
{
	char unk1[1];
	char forceDualWield;
	char unk2[10];
};

struct player_state_t
{
	int commandTime;
	unsigned __int8 unk1[248];
	int predictableEventSequence;
	int predictableEvents[4];
	int predictableEventParms[4];
	unsigned __int8 unk2[56];
	vec3_t viewangles;
	char unk3[272];
	int heldWeapons[15];
	unk_weapon_info_t weaponInfos[15];
	int currentOffhand;
	char unk4[8];
	int currentWeapon;
	int weapFlags;
	char unk5[24];
	int lastWeaponHand;
	char unk6[540];
	unsigned int perks[2];
	char unk7[11604];
};

enum session_state
{
	Playing = 0x0,
	Dead = 0x1,
	Spectator = 0x2,
	Intermission = 0x3,
};

enum client_connected
{
	CC_DISCONNECTED = 0x0,
	CC_CONNECTING = 0x1,
	CC_CONNECTED = 0x2,
};

enum button
{
	BUTTON_ATTACK = 0x1,
	BUTTON_HOLDSPRINT = 0x2,
	BUTTON_MELEE = 0x4,
	BUTTON_ACTION = 0x8,
	BUTTON_RELOAD = 0x20,
	BUTTON_HOLDPRONE = 0x100,
	BUTTON_HOLDCROUCH = 0x200,
	BUTTON_JUMP_CHANGESTANCE = 0x400,
	BUTTON_ADS = 0x800,
	BUTTON_HOLDBREATH = 0x2000,
	BUTTON_LETHAL = 0x4000,
	BUTTON_TACTICAL = 0x8000,
	BUTTON_HOLDADS = 0x80800,
};

struct usercmd_t
{
	unsigned int serverTime;
	button buttons;
	unsigned int viewAngles[3];
	int weapon;
	int offHandIndex;
	char forwardmove;
	char sidemove;
	unsigned __int16 perks;
	char meleeChargePitch;
	char meleeChargeYaw;
	char meleeChargeDist;
	char _unk2[3];
	char missilePitch;
	char missileYaw;
	char _unk3[4];
};

enum team
{
	None = 0x0,
	Axis = 0x1,
	Allies = 0x2,
	Spectators = 0x3,
};

struct client_state_t
{
	int clientIndex;
	team current_team;
	team oldTeam;
	byte unk1[56];
	char name[16];
	byte unk2[40];
	int usingTag;
	int usingTitle;
	char titleText[24];
	int titleBg;
	char tagText[8];
	int level;
};

struct client_session_t
{
	session_state sessionState;
	unsigned __int8 unk1[20];
	int score;
	int deaths;
	int kills;
	int unk2;
	unsigned __int16 scriptPersId;
	byte unk3[2];
	client_connected connected;
	usercmd_t cmd;
	usercmd_t oldcmd;
	int localClient;
	char newnetname[16];
	unsigned __int8 unk4[36];
	client_state_t clientstate;
	unsigned __int8 unk5[336];
};


enum g_client_flags
{
	Noclip = 0x1,
	Ufo = 0x2,
	ControlsFrozen = 0x4,
};


struct gclient_t
{
	player_state_t playerstate;
	client_session_t session;
	int spectatorClient;
	g_client_flags flags;
	char unk8[728];
};

struct entity_shared_t
{
	unsigned __int8 unkFlags[3];
	unsigned __int8 inUse;
	byte unk1[24];
	int contents;
	byte unk2[24];
	vec3_t currentOrigin;
	vec3_t currentAngles;
	int ownerNum;
	int eventTime;
	gclient_t *client;
	char unk3[22];
	unsigned __int16 classname;
	unsigned __int16 script_classname;
	char unk4[14];
	gentity_flags flags;
	char unk5[20];
	int health;
	char unk6[212];
};

struct entity_state_t
{
	unsigned __int16 number;
	unsigned __int8 unk1[2];
	entity_type type;
	int eFlags;
	unsigned __int8 unk2[12];
	vec3_t origin;
	unsigned __int8 unk3[24];
	vec3_t viewAngles;
	unsigned __int8 unk4[184];
};

struct gentity_t
{
	entity_state_t state;
	entity_shared_t shared;
};

struct level_locals_t
{
	gclient_t *gclients;
};


