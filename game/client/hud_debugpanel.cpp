// (C) Valve Software, meowcat767 & MIXX Brigade 2026
// --------------------------------------------------
// Purpose: debugging panel
// --------------------------------------------------

#include "cbase.h"
#include "hud_debugpanel.h"

#include "iclientmode.h"
#include "hud_macros.h"
#include "c_baseplayer.h"

using namespace vgui;

DECLARE_HUDELEMENT(CHuDebugPanel);

ConVar cl_debug_panel("cl_debug_panel", "0");

CHuDebugPanel::CHuDebugPanel(const char *name) : CHudElement(name), BaseClass(NULL, "HudDebugPanel")
{
	SetParent(g_pClientMode->GetViewport());
}

void CHuDebugPanel::Init()
{
}

void CHuDebugPanel::VidInit()
{
}

void CHuDebugPanel::Paint()
{
	if (!cl_debug_panel.GetBool())
		return;

	C_BasePlayer *player = C_BasePlayer::GetLocalPlayer();

	if (!player)
		return


}