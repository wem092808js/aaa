#include "Visuals.h"
#include "Interfaces.h"
#include "RenderManager.h"

// Any init here
void CVisuals::Init()
{
	// Idk
}

// Don't really need to do anything in here
void CVisuals::Move(CUserCmd *pCmd, bool& bSendPacket) {}

// Main ESP Drawing loop
void CVisuals::Draw()
{
	if (Menu::Window.VisualsTab.OtherCrosshairType.GetIndex() == 0)
		Interfaces::Engine->ClientCmd_Unrestricted("crosshair 1");

	if (!hackManager.pLocal())
		return;

	// Crosshair
	if (Menu::Window.VisualsTab.OtherCrosshairType.GetIndex() > 0)
	{
		Interfaces::Engine->ClientCmd_Unrestricted("crosshair 0");

		if (Menu::Window.VisualsTab.OtherCrosshairType.GetIndex() == 1)
			DrawCrosshair();

		if (Menu::Window.VisualsTab.OtherCrosshairType.GetIndex() == 2)
			DrawRecoilCrosshair();
	}
}

// Draw a basic crosshair
void CVisuals::DrawCrosshair()
{
	// Crosshair
	RECT View = Render::GetViewport();
	int MidX = View.right / 2;
	int MidY = View.bottom / 2;

	if (Menu::Window.VisualsTab.OtherCrosshair.GetIndex() == 0)
	{
		Render::Line(MidX - 8, MidY - 8, MidX + 8, MidY + 8, Color(255, 0, 0, 255));
		Render::Line(MidX + 8, MidY - 8, MidX - 8, MidY + 8, Color(255, 0, 0, 255));
		Render::Line(MidX - 4, MidY - 4, MidX + 4, MidY + 4, Color(255, 0, 0, 255));
		Render::Line(MidX + 4, MidY - 4, MidX - 4, MidY + 4, Color(255, 0, 0, 255));
	}
	else if (Menu::Window.VisualsTab.OtherCrosshair.GetIndex() == 1)
	{
		Render::Line(MidX - 10, MidY, MidX + 10, MidY, Color(255, 0, 0, 255));
		Render::Line(MidX, MidY - 10, MidX, MidY + 10, Color(255, 0, 0, 255));
	}
	else if (Menu::Window.VisualsTab.OtherCrosshair.GetIndex() == 2)
	{
		Render::DrawCircle(MidX - 5, MidY - 5, 10, 10, Color(255, 0, 0, 255));
	}
	else if (Menu::Window.VisualsTab.OtherCrosshair.GetIndex() == 3)
	{
		Render::Outline(MidX - 5, MidY - 5, 10, 10, Color(255, 0, 0, 255));
	}
	else if (Menu::Window.VisualsTab.OtherCrosshair.GetIndex() == 4)
	{
		RECT View = Render::GetViewport();
		int drX = View.right / 2;
		int drY = View.bottom / 2;
		Color color(255, 0, 0, 255);

		Render::Line(drX, drY, drX, drY - 5, color);
		Render::Line(drX, drY - 5, drX + 5, drY - 5, color);

		Render::Line(drX, drY, drX + 5, drY, color);
		Render::Line(drX + 5, drY, drX + 5, drY + 5, color);

		Render::Line(drX, drY, drX, drY + 5, color);
		Render::Line(drX, drY + 5, drX - 5, drY + 5, color);

		Render::Line(drX, drY, drX - 5, drY, color);
		Render::Line(drX - 5, drY, drX - 5, drY - 5, color);

		Render::DrawCircle(drX, drY, 13, 13, color);
		Render::DrawCircle(drX, drY, 18, 18, color);
		Render::DrawCircle(drX, drY, 23, 23, color);
		Render::DrawCircle(drX, drY, 28, 28, color);
		Render::DrawCircle(drX, drY, 32, 32, color);
		Render::DrawCircle(drX, drY, 37, 37, color);
		Render::DrawCircle(drX, drY, 42, 42, color);
		Render::DrawCircle(drX, drY, 47, 47, color);
		Render::DrawCircle(drX, drY, 52, 52, color);
		Render::DrawCircle(drX, drY, 57, 57, color);
		Render::DrawCircle(drX, drY, 62, 62, color);
		Render::DrawCircle(drX, drY, 67, 67, color);
		Render::DrawCircle(drX, drY, 72, 72, color);
		Render::DrawCircle(drX, drY, 77, 77, color);
		Render::DrawCircle(drX, drY, 82, 82, color);
		Render::DrawCircle(drX, drY, 87, 87, color);
		Render::DrawCircle(drX, drY, 92, 92, color);
		Render::DrawCircle(drX, drY, 97, 97, color);
		Render::DrawCircle(drX, drY, 102, 102, color);
		Render::DrawCircle(drX, drY, 107, 107, color);
		Render::DrawCircle(drX, drY, 112, 112, color);
		Render::DrawCircle(drX, drY, 117, 117, color);
		Render::DrawCircle(drX, drY, 122, 122, color);
		Render::DrawCircle(drX, drY, 127, 127, color);
		Render::DrawCircle(drX, drY, 132, 132, color);
		Render::DrawCircle(drX, drY, 137, 137, color);
		Render::DrawCircle(drX, drY, 142, 142, color);
		Render::DrawCircle(drX, drY, 147, 147, color);
		Render::DrawCircle(drX, drY, 152, 152, color);
		Render::DrawCircle(drX, drY, 157, 157, color);
		Render::DrawCircle(drX, drY, 162, 162, color);
		Render::DrawCircle(drX, drY, 167, 167, color);
		Render::DrawCircle(drX, drY, 172, 172, color);
		Render::DrawCircle(drX, drY, 177, 177, color);
		Render::DrawCircle(drX, drY, 182, 182, color);
		Render::DrawCircle(drX, drY, 187, 187, color);
		Render::DrawCircle(drX, drY, 192, 192, color);
		Render::DrawCircle(drX, drY, 192, 192, color);
		Render::DrawCircle(drX, drY, 197, 197, color);
		Render::DrawCircle(drX, drY, 202, 202, color);
		Render::DrawCircle(drX, drY, 207, 207, color);
		Render::DrawCircle(drX, drY, 212, 212, color);
		Render::DrawCircle(drX, drY, 217, 217, color);
		Render::DrawCircle(drX, drY, 222, 222, color);
	}
	else if (Menu::Window.VisualsTab.OtherCrosshair.GetIndex() == 5)
	{
		RECT View = Render::GetViewport();
		int drX = View.right / 2;
		int drY = View.bottom / 2;
		Color color(255, 0, 0, 255);

		Render::Line(drX, drY, drX, drY - 30, color);
		Render::Line(drX, drY - 30, drX + 30, drY - 30, color);

		Render::Line(drX, drY, drX + 30, drY, color);
		Render::Line(drX + 30, drY, drX + 30, drY + 30, color);

		Render::Line(drX, drY, drX, drY + 30, color);
		Render::Line(drX, drY + 30, drX - 30, drY + 30, color);

		Render::Line(drX, drY, drX - 30, drY, color);
		Render::Line(drX - 30, drY, drX - 30, drY - 30, color);


		Render::DrawCircle(drX, drY, 52, 52, color);
		Render::DrawCircle(drX, drY, 57, 57, color);
	}

}

// Recoil crosshair
void CVisuals::DrawRecoilCrosshair()
{
	IClientEntity *pLocal = hackManager.pLocal();

	// Get the view with the recoil
	Vector ViewAngles;
	Interfaces::Engine->GetViewAngles(ViewAngles);
	ViewAngles += pLocal->localPlayerExclusive()->GetAimPunchAngle() * 2.f;

	// Build a ray going fowards at that angle
	Vector fowardVec;
	AngleVectors(ViewAngles, &fowardVec);
	fowardVec *= 10000;

	// Get ray start / end
	Vector start = pLocal->GetOrigin() + pLocal->GetViewOffset();
	Vector end = start + fowardVec, endScreen;

	if (Render::WorldToScreen(end, endScreen) && pLocal->IsAlive())
	{
		if (Menu::Window.VisualsTab.OtherCrosshair.GetIndex() == 0)
		{
			Render::Line(endScreen.x - 4, endScreen.y - 4, endScreen.x + 4, endScreen.y + 4, Color(255, 0, 0, 255));
			Render::Line(endScreen.x + 4, endScreen.y - 4, endScreen.x - 4, endScreen.y + 4, Color(255, 0, 0, 255));
			Render::Line(endScreen.x - 2, endScreen.y - 2, endScreen.x + 2, endScreen.y + 2, Color(255, 0, 0, 255));
			Render::Line(endScreen.x + 2, endScreen.y - 2, endScreen.x - 2, endScreen.y + 2, Color(255, 0, 0, 255));
		}
		else if (Menu::Window.VisualsTab.OtherCrosshair.GetIndex() == 1)
		{
			Render::Line(endScreen.x - 10, endScreen.y, endScreen.x + 10, endScreen.y, Color(255, 0, 0, 255));
			Render::Line(endScreen.x, endScreen.y - 10, endScreen.x, endScreen.y + 10, Color(255, 0, 0, 255));
		}
		else if (Menu::Window.VisualsTab.OtherCrosshair.GetIndex() == 2)
		{
			Render::DrawCircle(endScreen.x - 5, endScreen.y - 5, 10, 10, Color(255, 0, 0, 255));
		}
		else if (Menu::Window.VisualsTab.OtherCrosshair.GetIndex() == 3)
		{
			Render::Outline(endScreen.x - 5, endScreen.y - 5, 10, 10, Color(255, 0, 0, 255));
		}
	}
}
