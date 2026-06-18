#include "cbase.h"
#include "hud_debugpanel.h"

#include "iclientmode.h"
#include "hud_macros.h"
#include "c_baseplayer.h"

using namespace vgui;

DECLARE_HUDELEMENT(CHudDebugPanel);

ConVar cl_debug_panel("cl_debug_panel", "0");

CHudDebugPanel::CHudDebugPanel(const char *name)
	: CHudElement(name), BaseClass(NULL, "HudDebugPanel")
{
	SetParent(g_pClientMode->GetViewport());
}

void CHudDebugPanel::Init()
{
}

void CHudDebugPanel::VidInit()
{
}

void CHudDebugPanel::Paint()
{
	if (!cl_debug_panel.GetBool())
		return;

	C_BasePlayer *player = C_BasePlayer::GetLocalPlayer();

	if (!player)
		return;

	Vector vel = player->GetAbsVelocity();
	float speed = vel.Length2D();

	int y = 100;

	wchar_t text[128];

	swprintf(text, 128, L"Speed: %.0f", speed);

	surface()->DrawSetTextPos(50, y);
	surface()->DrawPrintText(text, wcslen(text));
}