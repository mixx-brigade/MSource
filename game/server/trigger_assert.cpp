#include "cbase.h"
#include "trigger_assert.h"

LINK_ENTITY_TO_CLASS(trigger_assert, CTriggerAssert);

BEGIN_DATADESC(CTriggerAssert)
END_DATADESC()

void CTriggerAssert::Spawn(void)
{
	InitTrigger();
}

void CTriggerAssert::StartTouch(CBaseEntity* pOther)
{
	AssertMsg(false, "trigger_assert was touched!");

	BaseClass::StartTouch(pOther);
}