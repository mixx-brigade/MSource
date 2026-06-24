#ifndef TRIGGER_ASSERT_H
#define TRIGGER_ASSERT_H
#ifdef _WIN32
#pragma once
#endif

#include "triggers.h"

class CTriggerAssert : public CBaseTrigger
{
public:
	DECLARE_CLASS(CTriggerAssert, CBaseTrigger);
	DECLARE_DATADESC();

	void Spawn(void) override;
	void StartTouch(CBaseEntity* pOther) override;
};

#endif // TRIGGER_ASSERT_H