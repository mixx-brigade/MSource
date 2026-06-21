#include "cbase.h"
#include "env_timescale.h";

LINK_ENTITY_TO_CLASS(env_timescale, CEnvTimescale);

extern ConVar host_timescale;

BEGIN_DATADESC(CEnvTimescale)
DEFINE_KEYFIELD(m_flScale, FIELD_FLOAT, "scale"),
DEFINE_INPUTFUNC(FIELD_FLOAT, "SetScale", InputSetScale),
DEFINE_INPUTFUNC(FIELD_VOID, "Reset", InputReset),

END_DATADESC()

void CEnvTimescale::Spawn()
{
	BaseClass::Spawn();

	SetSolid(SOLID_NONE);
	AddEffects(EF_NODRAW);

}

void CEnvTimescale::InputSetScale(inputdata_t &inputdata)
{
	float scale = inputdata.value.Float();

	if (scale <= 0.0f)
		scale = m_flScale;

	if (scale <= 0.0f)
		scale = 1.0f;

	host_timescale.SetValue(scale);

	Msg("[env_timescale] host_timescale = %.2f\n", scale);

}

void CEnvTimescale::InputReset(inputdata_t &inputdata)
{
	host_timescale.SetValue(1.0f);

	Msg("[env_timescale] Reset Timescale.\n")
}