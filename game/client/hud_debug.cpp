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

	// Dynamically size the panel to fill the entire screen viewport
	int wide, tall;
	vgui::surface()->GetScreenSize(wide, tall);
	SetBounds(0, 0, wide, tall);

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

	// --- Player Physics Telemetry ---
	Vector vel = pPlayer->GetAbsVelocity();
	float speed2D = vel.Length2D();

	DrawLine(y, "=== ReSource Debugger ===");
	DrawLine(y, "Speed: %.2f", speed2D);
	DrawLine(y, "Velocity Z: %.2f", vel.z);
	DrawLine(y, "Flags: %d", pPlayer->GetFlags());
	DrawLine(y, "On Ground: %d", (pPlayer->GetFlags() & FL_ONGROUND) != 0);

	// --- Weapon Telemetry ---
	DrawLine(y, " "); // Spacer line
	DrawLine(y, "=== Weapon Telemetry ===");

	C_BaseCombatWeapon *pWeapon = pPlayer->GetActiveWeapon();
	if (pWeapon)
	{
		// 1. Get Weapon Class Name (e.g., weapon_smg1)
		DrawLine(y, "Class: %s", pWeapon->GetClassname());

		// 2. Get Primary Clip (-1 means the weapon doesn't use clips, like grenades)
		int iClip1 = pWeapon->UsesClipsForAmmo1() ? pWeapon->Clip1() : -1;
		if (iClip1 >= 0)
		{
			DrawLine(y, "Clip 1: %d", iClip1);
		}
		else
		{
			DrawLine(y, "Clip 1: N/A");
		}

		// 3. Get Reserve Ammo Total
		int iAmmoType = pWeapon->GetPrimaryAmmoType();
		int iReserve = pPlayer->GetAmmoCount(iAmmoType);
		DrawLine(y, "Reserve Ammo: %d", iReserve);
	}
	else
	{
		DrawLine(y, "Active Weapon: None");
	}
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


