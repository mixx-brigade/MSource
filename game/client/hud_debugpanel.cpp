#include "cbase.h"
#include "hud_debugpanel.h"

#include "iclientmode.h"
#include "hud_macros.h"
#include "c_baseplayer.h"
#include <vgui/IScheme.h>

DECLARE_HUDELEMENT(CHudDebugPanel);

static void OnDebugPanelChanged(IConVar *var, const char *pOldValue, float flOldValue);

ConVar cl_debug_panel("cl_debug_panel", "0", 0, "Toggles the HUD Debug Panel", OnDebugPanelChanged);

using namespace vgui;

CHudDebugPanel::CHudDebugPanel(const char *pElementName)
	: CHudElement(pElementName),
	BaseClass(NULL, "DebugPanel")
{
	SetParent(g_pClientMode->GetViewport());

	// Safely load and assign the standard system scheme
	SetScheme(vgui::scheme()->LoadSchemeFromFile("resource/ClientScheme.res", "ClientScheme"));

	SetTitle("Debug Panel", true);

	SetPos(50, 50);
	SetSize(250, 150);

	SetMoveable(true);
	SetSizeable(false);
	SetCloseButtonVisible(false);
	SetMinimizeButtonVisible(false);
	SetMaximizeButtonVisible(false);

	m_pSpeedLabel = new Label(this, "SpeedLabel", "");
	m_pSpeedLabel->SetPos(10, 30);
	m_pSpeedLabel->SetSize(200, 20);

	m_pFPSLabel = new Label(this, "FPSLabel", "");
	m_pFPSLabel->SetPos(10, 50);
	m_pFPSLabel->SetSize(200, 20);

	SetVisible(false);
}

// CRITICAL FIX: This intercepts VGUI after schemes load to remove missing frame border styles
void CHudDebugPanel::ApplySchemeSettings(vgui::IScheme *pScheme)
{
	BaseClass::ApplySchemeSettings(pScheme);

	// Strip default frame border/styling that enforces the checkerboard texture
	SetBorder(NULL);
	SetPaintBorderEnabled(false);

	// Force plain-color canvas background rendering instead
	SetPaintBackgroundEnabled(true);
	SetBgColor(Color(0, 0, 0, 180)); // 180 alpha clean solid dark plate
}

void CHudDebugPanel::Init()
{
	ToggleVisibility(cl_debug_panel.GetBool());
}

void CHudDebugPanel::VidInit()
{
	ToggleVisibility(cl_debug_panel.GetBool());
}

void CHudDebugPanel::ToggleVisibility(bool bShow)
{
	if (bShow)
	{
		SetVisible(true);
		Activate();
	}
	else
	{
		SetVisible(false);
	}
}

void CHudDebugPanel::OnThink()
{
	C_BasePlayer *player = C_BasePlayer::GetLocalPlayer();
	if (!player)
		return;

	float speed = player->GetAbsVelocity().Length2D();
	float fps = 1.0f / gpGlobals->frametime;

	wchar_t buffer[64]; // Fixed: Re-added buffer size to avoid build exceptions

	swprintf(buffer, ARRAYSIZE(buffer), L"Speed: %.0f", speed);
	m_pSpeedLabel->SetText(buffer);

	swprintf(buffer, ARRAYSIZE(buffer), L"FPS: %.0f", fps);
	m_pFPSLabel->SetText(buffer);
}

static void OnDebugPanelChanged(IConVar *var, const char *pOldValue, float flOldValue)
{
	CHudDebugPanel *pPanel = (CHudDebugPanel *)gHUD.FindElement("CHudDebugPanel");
	if (pPanel)
	{
		ConVar *pConVar = (ConVar *)var;
		pPanel->ToggleVisibility(pConVar->GetBool());
	}
}
