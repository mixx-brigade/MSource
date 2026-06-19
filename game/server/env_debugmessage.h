#ifndef ENV_DEBUGMESSAGE_H
#define ENV_DEBUGMESSAGE_H

#ifdef _WIN32
#pragma once
#endif

#include "cbase.h"

class CEnvDebugMessage : public CPointEntity
{
public:
	DECLARE_CLASS(CEnvDebugMessage, CPointEntity);
	DECLARE_DATADESC();

	CEnvDebugMessage();

	void Spawn() OVERRIDE;
	void InputShow(inputdata_t &inputdata);
private:
	string_t m_Message;
};
#endif