// (C) Valve Software, meowcat767 & MIXX Brigade 2026
// --------------------------------------------------
// Purpose: debugging hud
// --------------------------------------------------

#include "cbase.h"
#include "hud.h"
#include "hud_macros.h"
#include "iclientmode.h"
#include "vgui_controls/Controls.h"
#include "vgui/ISurface.h"
#include <vgui/ILocalize.h>
#include <vgui/IScheme.h>

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

void CHudDebug::DrawLine(int &y, const char *fmt, ...)
{
	char msg[1024]; // Safe array buffer allocation
	va_list argptr;
	va_start(argptr, fmt);
	Q_vsnprintf(msg, sizeof(msg), fmt, argptr);
	va_end(argptr);

	// Correctly pull the Default font from the client scheme engine
	if (m_hFont == vgui::INVALID_FONT)
	{
		vgui::HScheme scheme = vgui::scheme()->GetScheme("ClientScheme");
		vgui::IScheme *pScheme = vgui::scheme()->GetIScheme(scheme);
		if (pScheme)
		{
			m_hFont = pScheme->GetFont("DefaultFixedOutline", true);
		}
	}

	vgui::surface()->DrawSetTextFont(m_hFont);
	vgui::surface()->DrawSetTextColor(255, 255, 255, 255); // White text
	vgui::surface()->DrawSetTextPos(20, y);

	// Convert text to wide string for the Source surface printer
	wchar_t wmsg[1024];
	if (g_pVGuiLocalize)
	{
		g_pVGuiLocalize->ConvertANSIToUnicode(msg, wmsg, sizeof(wmsg));
		vgui::surface()->DrawPrintText(wmsg, wcslen(wmsg));
	}

	// Advance vertical line tracking
	y += vgui::surface()->GetFontTall(m_hFont) + 2;
}

