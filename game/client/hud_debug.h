// (C) Valve Software, meowcat767 & MIXX Brigade 2026
// --------------------------------------------------
// Purpose: header file for the debugging hud
// --------------------------------------------------

#ifndef HUD_DEBUG_H
#define HUD_DEBUG_H

#ifdef _WIN32
#pragma once
#endif

#include "hudelement.h"
#include "vgui_controls\Panel.h"

class CHudDebug : public CHudElement, public vgui::Panel
{
	DECLARE_CLASS_SIMPLE(CHudDebug, vgui::Panel);

public:
	CHudDebug(const char *pElementName);

	virtual void Init();
	virtual void VidInit();
	virtual void Paint();

private:
	void DrawLine(int &y, const char *fmt, ...);

	vgui::HFont m_hFont;
	bool m_Enabled;

};

#endif // HUD_DEBUG_H