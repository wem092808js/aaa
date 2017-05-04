#pragma once

#include "Hacks.h"

Vector GetAutostrafeView();

class CMiscHacks : public CHack
{
public:
	void Init();
	void Draw();
	void Move(CUserCmd *pCmd, bool& bSendPacket);
private:
	void AutoJump(CUserCmd *pCmd);
	void AutoStrafe(CUserCmd *pCmd);
	void ChatSpamRegular();
	void ChatSpamReports();
	void ChatSpam1();
	void ChatSpam2();
	void ChatSpam3();
	void SpoofConvars();
	void ForceThirdPerson(CUserCmd* pCmd);
	void INTERWEBZ();
	void AIMWARE();
	void TeleportHack(CUserCmd *pCmd);
	void Thirdperson();
	void ClanNone();
	void ClanTytto();
	void ClanSkeet();
	void ClanBSQUAD();
	void ClanTrapSlayer();
};