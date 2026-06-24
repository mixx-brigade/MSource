#include "cbase.h"
#include "fxaa.h"
#include "materialsystem/imaterial.h"
#include "materialsystem/imaterialsystem.h"
#include "tier0/memdbgon.h"

ConVar mat_fxaa("mat_fxaa", "1", FCVAR_ARCHIVE, "Enable/disable FXAA post-processing effect");

CFXAAEffect::CFXAAEffect()	
{
	m_bEnabled = true;
}

void CFXAAEffect::Init(void)
{
}

void CFXAAEffect::Shutdown(void)
{
}

void CFXAAEffect::SetParameters(KeyValues* params)
{
}

void CFXAAEffect::Enable(bool bEnable)
{
	m_bEnabled = bEnable;
}

bool CFXAAEffect::IsEnabled(void)
{
	return m_bEnabled && mat_fxaa.GetBool();
}

void CFXAAEffect::Render(int x, int y, int w, int h)
{
	if (!IsEnabled())
		return;

	Msg("FXAA Render"); // just a test for now
}

// Register it
ADD_SCREENSPACE_EFFECT(CFXAAEffect, fxaa);
