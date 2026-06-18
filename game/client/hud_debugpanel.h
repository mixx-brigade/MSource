// (C) Valve Software, meowcat767 & MIXX Brigade 2026
// --------------------------------------------------
// Purpose: header for the debugging panel
// --------------------------------------------------

#ifndef HUD_DEBUGPANEL_H
#define HUD_DEBUGPANEL_H

#ifdef _WIN32
#pragma once
#endif

#include "hudelement.h"
#include <vgui_controls/Panel.h>


class CHuDebugPanel : public CHudElement, public vgui::Panel
{
	DECLARE_CLASS_SIMPLE(CHuDebugPanel, vgui::Panel);

public:
	CHuDebugPanel(const char *name);

	virtual void Init();
	virtual void VidInit();
	virtual void Paint();
};

#endif