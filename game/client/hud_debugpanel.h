#ifndef HUD_DEBUGPANEL_H
#define HUD_DEBUGPANEL_H

#ifdef _WIN32
#pragma once
#endif

#include "hudelement.h"
#include <vgui_controls/Frame.h>
#include <vgui_controls/Label.h>

class CHudDebugPanel : public CHudElement, public vgui::Frame
{
	DECLARE_CLASS_SIMPLE(CHudDebugPanel, vgui::Frame);

public:
	CHudDebugPanel(const char *pElementName);

	virtual void Init();
	virtual void VidInit();
	virtual void OnThink();

	// Added: Required override declaration to block frame assets
	virtual void ApplySchemeSettings(vgui::IScheme *pScheme);

	void ToggleVisibility(bool bShow);

private:
	vgui::Label *m_pSpeedLabel;
	vgui::Label *m_pFPSLabel;
};

#endif
