// (C) Valve Software, meowcat767 & MIXX Brigade 2026
// --------------------------------------------------
// Purpose: debugging hud
// --------------------------------------------------

#include "cbase.h"
#include "hud.h"
#include "hud_macros.h"
#include "iclientmode.h"
#include "vgui_controls\Controls.h"
#include "vgui\ISurface.h"

#include "hud_debug.h"


using namespace vgui;

extern ConVar cl_debug_hud;

DECLARE_HUDELEMENT(CHudDebug);

CHudDebug::CHudDebug(const char *pElementName) : CHudElement(pElementName), BaseClass(NULL, "HudDebug")
{
	SetParent(g_pClientMode->GetViewport());
}

void CHudDebug::Init()
{
	SetVisible(true);
}

void CHudDebug::VidInit()
{
	// Use me to re-init fonts or res here later if needed!
}

void CHudDebug::Paint()
{
	if (!cl_debug_hud.GetBool())
		return;

	C_BasePlayer *pPlayer = C_BasePlayer::GetLocalPlayer();
	if (!pPlayer)
		return;

	int y = 20;

	Vector vel = pPlayer->GetAbsVelocity();
	float speed2D = vel.Length2D();

	DrawLine(y, "=== ReSource Debugger ===");
	DrawLine(y, "Speed: %.2f", speed2D);
	DrawLine(y, "Velocity Z: %.2f", vel.z);
	DrawLine(y, "Flags: %d", pPlayer->GetFlags());
	DrawLine(y, "On Ground: %d", (pPlayer->GetFlags() & FL_ONGROUND) != 0);
	
	

}