#include "cbase.h"
#include "fxaa.h"
#include "materialsystem/imaterial.h"
#include "materialsystem/imaterialsystem.h"
#include "tier0/memdbgon.h"

ConVar mat_fxaa("mat_fxaa", "1", FCVAR_ARCHIVE, "Enable/disable FXAA post-processing effect");

IMaterial* g_pFXAAMaterial = nullptr;

CFXAAEffect::CFXAAEffect()	
{
	m_bEnabled = true;
}

void CFXAAEffect::Init(void)
{
	g_pFXAAMaterial = materials->FindMaterial("effects/fxaa", TEXTURE_GROUP_OTHER, true);
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
	if (!IsEnabled() || !g_pFXAAMaterial)
		return;

	IMatRenderContext* pRenderContext = materials->GetRenderContext();

	pRenderContext->PushRenderTargetAndViewport();

	pRenderContext->Bind(g_pFXAAMaterial);

	// Fullscreen quad
	CMatRenderContextPtr pRC(materials);
	pRC->DrawScreenSpaceQuad(g_pFXAAMaterial);

	pRenderContext->PopRenderTargetAndViewport();
}

// Register it
ADD_SCREENSPACE_EFFECT(CFXAAEffect, fxaa);
