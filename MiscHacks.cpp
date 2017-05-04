#include "MiscHacks.h"
#include "Interfaces.h"
#include "RenderManager.h"
#include "MiscClasses.h"
#include "UTIL Functions.h"
#include "Utilities.h"
#include <time.h>

Vector AutoStrafeView;

void CMiscHacks::Init()
{
	// Any init
}

void CMiscHacks::Draw()
{
	// Any drawing	
}


void CMiscHacks::Move(CUserCmd *pCmd, bool& bSendPacket)
{
	static ConVar* nameConvar = Interfaces::CVar->FindVar("name");
	static int Times = 250;
	// Clan Changer
	switch (Menu::Window.MiscTab.ClanTag.GetIndex())
	{
	case 0:
		ClanNone();
		break;
	case 1:
		ClanTytto();
		break;
	case 2:
		ClanSkeet();
		break;
	case 3:
		ClanBSQUAD();
		break;
	case 4:
		ClanTrapSlayer();
		break;
	}

	// Bhop
	if (Menu::Window.MiscTab.OtherBunnyhop.GetState())
		AutoJump(pCmd);

	// Strafe
	Interfaces::Engine->GetViewAngles(AutoStrafeView);
	if (Menu::Window.MiscTab.OtherAutoStrafe.GetState())
		AutoStrafe(pCmd);


	// Spams
	switch (Menu::Window.MiscTab.OtherChatSpam.GetIndex())
	{
	case 0:
		// No Chat Spam
		break;
	case 1:
		// Regular
		ChatSpam1();
		break;
	case 2:
		// Anime
		ChatSpam2();
		break;
	case 3:
		// E-THUG
		ChatSpam3();
		break;
	}
}
#pragma region ClanTags
void SetClanTag(const char* tag, const char* name)
{
	static auto pSetClanTag = reinterpret_cast<void(__fastcall*)(const char*, const char*)>(((DWORD)(Utilities::Memory::FindPattern("engine.dll", (PBYTE)"\x53\x56\x57\x8B\xDA\x8B\xF9\xFF\x15\x00\x00\x00\x00\x6A\x24\x8B\xC8\x8B\x30", "xxxxxxxxx????xxxxxx"))));
	pSetClanTag(tag, name);
}
void CMiscHacks::ClanNone()
{
	SetClanTag("", "None");
}
void CMiscHacks::ClanTytto()
{
	int x = Menu::Window.MiscTab.ClanTagAnim.GetIndex();
	if (x == 0)
	{
		SetClanTag("tytto.pw", "tytto.pw");
	}
	else if (x == 1)
	{
		int iLastTime = 0;
		if (int(Interfaces::Globals->curtime) != iLastTime)
		{
			switch (int(Interfaces::Globals->curtime) % 2)
			{
			case 0:SetClanTag("\r tytto.pw", "tytto.pw"); break;
			case 1:SetClanTag("tytto.pw \r", "tytto.pw"); break;
			}
			iLastTime = int(Interfaces::Globals->curtime);
		}
	}
	else if (x == 2)
	{
		int iLastTime = 0;
		if (int(Interfaces::Globals->curtime) != iLastTime)
		{
			switch (int(Interfaces::Globals->curtime) % 18)
			{
			case 0:SetClanTag("          ", "tytto.pw"); break;
			case 1:SetClanTag("         t", "tytto.pw"); break;
			case 2:SetClanTag("        ty", "tytto.pw"); break;
			case 3:SetClanTag("       tyt", "tytto.pw"); break;
			case 4:SetClanTag("      tytt", "tytto.pw"); break;
			case 5:SetClanTag("     tytto", "tytto.pw"); break;
			case 6:SetClanTag("    tytto.", "tytto.pw"); break;
			case 7:SetClanTag("   tytto.p", "tytto.pw"); break;
			case 8:SetClanTag(" tytto.pw", "tytto.pw"); break;
			case 9:SetClanTag("tytto.pw ", "tytto.pw"); break;
			case 10:SetClanTag("ytto.pw  ", "tytto.pw"); break;
			case 11:SetClanTag("tto.pw   ", "tytto.pw"); break;
			case 12:SetClanTag("to.pw    ", "tytto.pw"); break;
			case 13:SetClanTag("o.pw     ", "tytto.pw"); break;
			case 14:SetClanTag(".pw      ", "tytto.pw"); break;
			case 15:SetClanTag("pw       ", "tytto.pw"); break;
			case 16:SetClanTag("w        ", "tytto.pw"); break;
			case 17:SetClanTag("         ", "tytto.pw"); break;
			}
		}
	}
}
void CMiscHacks::ClanSkeet()
{
	int x = Menu::Window.MiscTab.ClanTagAnim.GetIndex();
	if (x == 0)
	{
		SetClanTag("skeet.cc", "skeet.cc");
	}
	if (x == 1)
	{
		int iLastTime = 0;
		if (int(Interfaces::Globals->curtime) != iLastTime)
		{
			switch (int(Interfaces::Globals->curtime) % 2)
			{
			case 0:SetClanTag("\r skeet.cc", "skeet.cc"); break;
			case 1:SetClanTag("skeet.cc \r", "skeet.cc"); break;
			}
			iLastTime = int(Interfaces::Globals->curtime);
		}
	}
	if (x == 2)
	{
		int iLastTime = 0;
		if (int(Interfaces::Globals->curtime) != iLastTime)
		{
			switch (int(Interfaces::Globals->curtime) % 18)
			{
			case 0:SetClanTag("          ", "skeet.cc"); break;
			case 1:SetClanTag("         s", "skeet.cc"); break;
			case 2:SetClanTag("        sk", "skeet.cc"); break;
			case 3:SetClanTag("       ske", "skeet.cc"); break;
			case 4:SetClanTag("      skee", "skeet.cc"); break;
			case 5:SetClanTag("     skeet", "skeet.cc"); break;
			case 6:SetClanTag("    skeet.", "skeet.cc"); break;
			case 7:SetClanTag("   skeet.c", "skeet.cc"); break;
			case 8:SetClanTag(" skeet.cc", "skeet.cc"); break;
			case 9:SetClanTag("skeet.cc ", "skeet.cc"); break;
			case 10:SetClanTag("keet.cc  ", "skeet.cc"); break;
			case 11:SetClanTag("eet.cc   ", "skeet.cc"); break;
			case 12:SetClanTag("et.cc    ", "skeet.cc"); break;
			case 13:SetClanTag("t.cc     ", "skeet.cc"); break;
			case 14:SetClanTag(".cc      ", "skeet.cc"); break;
			case 15:SetClanTag("cc       ", "skeet.cc"); break;
			case 16:SetClanTag("c        ", "skeet.cc"); break;
			case 17:SetClanTag("         ", "skeet.cc"); break;
			}
			iLastTime = int(Interfaces::Globals->curtime);
		}
	}
}
void CMiscHacks::ClanBSQUAD()
{
	int x = Menu::Window.MiscTab.ClanTagAnim.GetIndex();
	if (x == 0)
	{
		SetClanTag("br0$quad", "br0$quad");
	}
	if (x == 1)
	{
		int iLastTime = 0;
		if (int(Interfaces::Globals->curtime) != iLastTime)
		{
			switch (int(Interfaces::Globals->curtime) % 2)
			{
			case 0:SetClanTag("\r br0$quad", "br0$quad"); break;
			case 1:SetClanTag("br0$quad \r", "br0$quad"); break;
			}
			iLastTime = int(Interfaces::Globals->curtime);
		}
	}
	if (x == 2)
	{
		int iLastTime = 0;
		if (int(Interfaces::Globals->curtime) != iLastTime)
		{
			switch (int(Interfaces::Globals->curtime) % 18)
			{
			case 0:SetClanTag("          ", "br0$quad"); break;
			case 1:SetClanTag("         b", "br0$quad"); break;
			case 2:SetClanTag("        br", "br0$quad"); break;
			case 3:SetClanTag("       br0", "br0$quad"); break;
			case 4:SetClanTag("      br0$", "br0$quad"); break;
			case 5:SetClanTag("     br0$q", "br0$quad"); break;
			case 6:SetClanTag("    br0$qu", "br0$quad"); break;
			case 7:SetClanTag("   br0$qua", "br0$quad"); break;
			case 8:SetClanTag(" br0$quad", "br0$quad"); break;
			case 9:SetClanTag("br0$quad ", "br0$quad"); break;
			case 10:SetClanTag("r0$quad  ", "br0$quad"); break;
			case 11:SetClanTag("0$quad   ", "br0$quad"); break;
			case 12:SetClanTag("$quad    ", "br0$quad"); break;
			case 13:SetClanTag("quad    ", "br0$quad"); break;
			case 14:SetClanTag("uad      ", "br0$quad"); break;
			case 15:SetClanTag("ad       ", "br0$quad"); break;
			case 16:SetClanTag("d        ", "br0$quad"); break;
			case 17:SetClanTag("         ", "br0$quad"); break;
			}
			iLastTime = int(Interfaces::Globals->curtime);
		}
	}
}
void CMiscHacks::ClanTrapSlayer()
{
	int x = Menu::Window.MiscTab.ClanTagAnim.GetIndex();
	if (x == 0)
	{
		SetClanTag("TRAP$LAYER", "TRAPSLAYER");
	}
	if (x == 1)
	{
		int iLastTime = 0;
		if (int(Interfaces::Globals->curtime) != iLastTime)
		{
			switch (int(Interfaces::Globals->curtime) % 2)
			{
			case 0:SetClanTag("\r TRAP$LAYER", "TRAP$LAYER"); break;
			case 1:SetClanTag("TRAP$LAYER \r", "TRAP$LAYER"); break;
			}
			iLastTime = int(Interfaces::Globals->curtime);
		}
	}
	if (x == 2)
	{
		int iLastTime = 0;
		if (int(Interfaces::Globals->curtime) != iLastTime)
		{
			switch (int(Interfaces::Globals->curtime) % 22)
			{
			case 0:SetClanTag("             ", "TRAP$LAYER"); break;
			case 1:SetClanTag("            T", "TRAP$LAYER"); break;
			case 2:SetClanTag("           TR", "TRAP$LAYER"); break;
			case 3:SetClanTag("          TRA", "TRAP$LAYER"); break;
			case 4:SetClanTag("         TRAP", "TRAP$LAYER"); break;
			case 5:SetClanTag("        TRAP$", "TRAP$LAYER"); break;
			case 6:SetClanTag("       TRAP$L", "TRAP$LAYER"); break;
			case 7:SetClanTag("      TRAP$LA", "TRAP$LAYER"); break;
			case 8:SetClanTag("     TRAP$LAY", "TRAP$LAYER"); break;
			case 9:SetClanTag("    TRAP$LAYE", "TRAP$LAYER"); break;
			case 10:SetClanTag(" TRAP$LAYER", "TRAP$LAYER"); break;
			case 11:SetClanTag("TRAP$LAYER ", "TRAP$LAYER"); break;
			case 12:SetClanTag("RAP$LAYER   ", "TRAP$LAYER"); break;
			case 13:SetClanTag("AP$LAYER    ", "TRAP$LAYER"); break;
			case 14:SetClanTag("P$LAYER     ", "TRAP$LAYER"); break;
			case 15:SetClanTag("$LAYER      ", "TRAP$LAYER"); break;
			case 16:SetClanTag("LAYER       ", "TRAP$LAYER"); break;
			case 17:SetClanTag("AYER        ", "TRAP$LAYER"); break;
			case 18:SetClanTag("YER         ", "TRAP$LAYER"); break;
			case 19:SetClanTag("ER          ", "TRAP$LAYER"); break;
			case 20:SetClanTag("R           ", "TRAP$LAYER"); break;
			case 21:SetClanTag("            ", "TRAP$LAYER"); break;
			}
			iLastTime = int(Interfaces::Globals->curtime);
		}
	}
}
#pragma endregion
void CMiscHacks::TeleportHack(CUserCmd *pCmd)
{
	if (GetAsyncKeyState(VK_F2))   //Klawisz do teleportowania
	{
		*(DWORD*)(&pCmd->viewangles.z) = 0x7F7FFFFF;
	}
}

void CMiscHacks::AutoJump(CUserCmd *pCmd)
{
	if (pCmd->buttons & IN_JUMP && GUI.GetKeyState(VK_SPACE))
	{
		int iFlags = hackManager.pLocal()->GetFlags();
		if (!(iFlags & FL_ONGROUND))
			pCmd->buttons &= ~IN_JUMP;

		if (hackManager.pLocal()->GetVelocity().Length() <= 45)
		{
			pCmd->forwardmove = 450.f;
		}
	}
}

void CMiscHacks::AutoStrafe(CUserCmd *pCmd)
{
	IClientEntity* pLocal = hackManager.pLocal();
	static bool bDirection = true;

	bool bKeysPressed = true;

	if (GUI.GetKeyState(0x41) || GUI.GetKeyState(0x57) || GUI.GetKeyState(0x53) || GUI.GetKeyState(0x44))
		bKeysPressed = false;
	if (pCmd->buttons & IN_ATTACK)
		bKeysPressed = false;

	float flYawBhop = 0.f;
	if (pLocal->GetVelocity().Length() > 45.f)
	{
		float x = 30.f, y = pLocal->GetVelocity().Length(), z = 0.f, a = 0.f;

		z = x / y;
		z = fabsf(z);

		a = x * z;

		flYawBhop = a;
	}

	if ((GetAsyncKeyState(VK_SPACE) && !(pLocal->GetFlags() & FL_ONGROUND)) && bKeysPressed)
	{

		if (bDirection)
		{
			AutoStrafeView -= flYawBhop;
			GameUtils::NormaliseViewAngle(AutoStrafeView);
			pCmd->sidemove = -450;
			bDirection = false;
		}
		else
		{
			AutoStrafeView += flYawBhop;
			GameUtils::NormaliseViewAngle(AutoStrafeView);
			pCmd->sidemove = 430;
			bDirection = true;
		}

		if (pCmd->mousedx < 0)
		{
			pCmd->forwardmove = 22;
			pCmd->sidemove = -450;
		}

		if (pCmd->mousedx > 0)
		{
			pCmd->forwardmove = +22;
			pCmd->sidemove = 450;
		}
	}
}

Vector GetAutostrafeView()
{
	return AutoStrafeView;
}

#include <random>
__forceinline int RandomInt(int Min, int Max) {
	std::random_device RandomDevice;
	std::mt19937 MT(RandomDevice());
	std::uniform_int_distribution<int>Compartment(Min, Max);
	return Compartment(MT);
}

std::vector<std::string> chatspamss =
{ "O-onii-chan!!~", "Nyaa~", "2d girls > 3d girls", "i afk autostrafe while i fuck my waifu", "want my anime list?", "even my waifu is better than you", ":3", "no waifu no laifu!", "Anime is my bae.", "my waifu > your mom", "calling you a baka would be an understatement", "pfft youtube? only vids i watch are on hentaihaven", "they're not cartoons, they're animes...", "one punch man? i'm one tap man.", "your cheat is worse than a person who watches dub", "do you even know japanese?" };

void CMiscHacks::ChatSpam2()
{
	static DWORD lastspammed = 0;
	if (GetTickCount() - lastspammed > 800)
	{
		lastspammed = GetTickCount();
		auto say = "say ";
		std::string p = say + chatspamss[rand() % chatspamss.size()];
		Interfaces::Engine->ClientCmd_Unrestricted(p.c_str());
	}
}

std::vector<std::string> chatspams =
{ "tytto.priv | Private Rage/Legit CS:GO Cheat" };

void CMiscHacks::ChatSpam3()
{
	static DWORD lastspammed = 0;
	if (GetTickCount() - lastspammed > 800)
	{
		lastspammed = GetTickCount();
		auto say = "say ";
		std::string p = say + chatspams[rand() % chatspams.size()];
		Interfaces::Engine->ClientCmd_Unrestricted(p.c_str());
	}
}
std::vector<std::string> chatspamsss =
{ "dunked by tytto.pw", "tytto.pw > you", "nice k/d, you pay for that?", "refund shit p2c", "UFF YA", "its not fakelag its telstra", "tytto.pw owns me and all", "laff 1tapped nerd", "go subscribe to /groups/metaphorically nerd", "tytto.priv > your shit p2c", "nice steam level, you pay for that?", "nice cheat, go chargeback aimware lol", "go get aimtux and you might stand a chance against mpgh cheats", "c u @ media", "lol raged irl", "f12" };

void CMiscHacks::ChatSpam1()
{
	static DWORD lastspammed = 0;
	if (GetTickCount() - lastspammed > 800)
	{
		lastspammed = GetTickCount();
		auto say = "say ";
		std::string p = say + chatspamsss[rand() % chatspamsss.size()];
		Interfaces::Engine->ClientCmd_Unrestricted(p.c_str());
	}
}
void ConVar::SetValue(const char* value)
{
	typedef void(__thiscall* OriginalFn)(void*, const char*);
	return  call_vfunc<OriginalFn>(this, 14)(this, value);
}

void ConVar::SetValue(float value)
{
	typedef void(__thiscall* OriginalFn)(void*, float);
	return call_vfunc<OriginalFn>(this, 15)(this, value);
}

void ConVar::SetValue(int value)
{
	typedef void(__thiscall* OriginalFn)(void*, int);
	return call_vfunc<OriginalFn>(this, 16)(this, value);
}
float ConVar::GetFloat(void) const {
	return pParent->fValue;
}
int ConVar::GetInt(void) const {
	return pParent->nValue;
}
const char* ConVar::GetString(void) const {
	return pParent->pszDefaultValue;
}

Color ConVar::GetColor(void) const {
	unsigned char *pColorElement = ((unsigned char *)&pParent->nValue);
	return Color(pColorElement[0], pColorElement[1], pColorElement[2], pColorElement[3]);
}
void ConVar::SetValue(Color value)
{
	typedef void(__thiscall* OriginalFn)(void*, Color);
	return call_vfunc<OriginalFn>(this, 17)(this, value);
}

char* ConVar::GetName()
{
	typedef char*(__thiscall* OriginalFn)(void*);
	return call_vfunc<OriginalFn>(this, 5)(this);
}

char* ConVar::GetDefault()
{
	return pszDefaultValue;
}

template<typename T>
inline void MinspecCvar::SetValue(T value)
{
	m_pConVar->SetValue(T);
}
MinspecCvar::MinspecCvar(const char* szCVar, char* newname, float newvalue) : m_pConVar(nullptr)
{
	m_pConVar = Interfaces::CVar->FindVar(szCVar);
	m_newvalue = newvalue;
	m_szReplacementName = newname;
	Spoof();
}

MinspecCvar::~MinspecCvar()
{
	if (ValidCvar())
	{
		Interfaces::CVar->UnregisterConCommand(m_pConVar);
		m_pConVar->pszName = m_szOriginalName;
		m_pConVar->SetValue(m_OriginalValue);
		Interfaces::CVar->RegisterConCommand(m_pConVar);
	}
}

bool MinspecCvar::ValidCvar()
{
	return m_pConVar != nullptr;
}
void MinspecCvar::Spoof()
{
	if (ValidCvar())
	{
		Interfaces::CVar->UnregisterConCommand(m_pConVar);
		m_szOriginalName = m_pConVar->pszName;
		m_OriginalValue = m_pConVar->GetFloat();

		m_pConVar->pszName = m_szReplacementName;
		Interfaces::CVar->RegisterConCommand(m_pConVar);
		m_pConVar->SetValue(m_newvalue);
	}
}

int MinspecCvar::GetInt()
{
	if (ValidCvar()) {
		return m_pConVar->GetInt();
	}
	return 0;
}

float MinspecCvar::GetFloat()
{
	if (ValidCvar()) {
		return m_pConVar->GetFloat();
	}
	return 0.0f;
}

const char* MinspecCvar::GetString()
{
	if (ValidCvar()) {
		return m_pConVar->GetString();
	}
	return nullptr;
}
SpoofedConvar::SpoofedConvar(const char* szCVar) {
	m_pOriginalCVar = Interfaces::CVar->FindVar(szCVar);
	Spoof();
}
SpoofedConvar::SpoofedConvar(ConVar* pCVar) {
	m_pOriginalCVar = pCVar;
	Spoof();
}
SpoofedConvar::~SpoofedConvar() {
	if (IsSpoofed()) {
		DWORD dwOld;

		SetFlags(m_iOriginalFlags);
		SetString(m_szOriginalValue);

		VirtualProtect((LPVOID)m_pOriginalCVar->pszName, 128, PAGE_READWRITE, &dwOld);
		strcpy((char*)m_pOriginalCVar->pszName, m_szOriginalName);
		VirtualProtect((LPVOID)m_pOriginalCVar->pszName, 128, dwOld, &dwOld);

		//Unregister dummy cvar
		Interfaces::CVar->UnregisterConCommand(m_pDummyCVar);
		free(m_pDummyCVar);
		m_pDummyCVar = NULL;
	}
}
bool SpoofedConvar::IsSpoofed() {
	return m_pDummyCVar != NULL;
}
void SpoofedConvar::Spoof() {
	if (!IsSpoofed() && m_pOriginalCVar) {
		//Save old name value and flags so we can restore the cvar lates if needed
		m_iOriginalFlags = m_pOriginalCVar->nFlags;
		strcpy(m_szOriginalName, m_pOriginalCVar->pszName);
		strcpy(m_szOriginalValue, m_pOriginalCVar->pszDefaultValue);

		sprintf_s(m_szDummyName, 128, "d_%s", m_szOriginalName);

		//Create the dummy cvar
		m_pDummyCVar = (ConVar*)malloc(sizeof(ConVar));
		if (!m_pDummyCVar) return;
		memcpy(m_pDummyCVar, m_pOriginalCVar, sizeof(ConVar));

		m_pDummyCVar->pNext = NULL;
		//Register it
		Interfaces::CVar->RegisterConCommand(m_pDummyCVar);

		//Fix "write access violation" bullshit
		DWORD dwOld;
		VirtualProtect((LPVOID)m_pOriginalCVar->pszName, 128, PAGE_READWRITE, &dwOld);

		//Rename the cvar
		strcpy((char*)m_pOriginalCVar->pszName, m_szDummyName);

		VirtualProtect((LPVOID)m_pOriginalCVar->pszName, 128, dwOld, &dwOld);

		SetFlags(FCVAR_NONE);
	}
}
void SpoofedConvar::SetFlags(int flags) {
	if (IsSpoofed()) {
		m_pOriginalCVar->nFlags = flags;
	}
}
int SpoofedConvar::GetFlags() {
	return m_pOriginalCVar->nFlags;
}
void SpoofedConvar::SetInt(int iValue) {
	if (IsSpoofed()) {
		m_pOriginalCVar->SetValue(iValue);
	}
}
void SpoofedConvar::SetBool(bool bValue) {
	if (IsSpoofed()) {
		m_pOriginalCVar->SetValue(bValue);
	}
}
void SpoofedConvar::SetFloat(float flValue) {
	if (IsSpoofed()) {
		m_pOriginalCVar->SetValue(flValue);
	}
}
void SpoofedConvar::SetString(const char* szValue) {
	if (IsSpoofed()) {
		m_pOriginalCVar->SetValue(szValue);
	}
}