#pragma once

#include "Hacks.h"

class CEsp : public CHack
{
public:
	void Init();
	void Draw();
	void Move(CUserCmd *pCmd, bool& bSendPacket);
private:

	
	struct matrix3x3_t
	{
		float m_flMatVal[3][3];
	};

	struct matrix3x4_t
	{
		float m_flMatVal[3][4];
	};

	
	// Other shit
	IClientEntity *BombCarrier;

	struct ESPBox
	{
		int x, y, w, h;
	};

	// Draw a player
	void DrawPlayer(IClientEntity* pEntity, player_info_t pinfo);

	// Get player info
	Color GetPlayerColor(IClientEntity* pEntity);
	bool GetBox(IClientEntity* pEntity, ESPBox &result);

	// Draw shit about player
	void DrawBox(ESPBox size, Color color);
	void DrawBox2(ESPBox size, Color color);
	void DrawName(player_info_t pinfo, ESPBox size);
	void DrawNameRainbow(player_info_t pinfo, ESPBox size);
	void DrawHealth(IClientEntity* pEntity, ESPBox size);
	void DrawHealth2(IClientEntity* pEntity, ESPBox size);
	void DrawHealth3(IClientEntity* pEntity, ESPBox size);
	void HealthBar(Vector bot, Vector top, float health);
	void DrawInfo(IClientEntity* pEntity, ESPBox size);
	void DrawCross(IClientEntity* pEntity);
	void DrawSkeleton(IClientEntity* pEntity);
	void DrawSkeletonRainbow(IClientEntity* pEntity);

	void DrawDrop(IClientEntity* pEntity, ClientClass* cClass);
	void DrawBombPlanted(IClientEntity* pEntity, ClientClass* cClass);
	void DrawBomb(IClientEntity* pEntity, ClientClass* cClass);
	void DrawGlow();
};

