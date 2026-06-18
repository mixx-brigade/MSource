// (C) Valve Software, meowcat767 & MIXX Brigade 2026
// --------------------------------------------------
// Purpose: hud that shows collision and stuff
// --------------------------------------------------

#include "cbase.h"
#include  "debug_trace.h"
#include "c_baseplayer.h"
#include "debugoverlay_shared.h"

CON_COMMAND(rs_trace, "Perform a debug eye trace")
{
	C_BasePlayer *pPlayer = C_BasePlayer::GetLocalPlayer();

	if (!pPlayer)
		return;

	Vector start = pPlayer->EyePosition();

	Vector forward;
	AngleVectors(pPlayer->EyeAngles(), &forward);

	Vector end = start + forward * 4096.0f;

	trace_t tr;

	UTIL_TraceLine(
		start,
		end,
		MASK_SOLID,
		pPlayer,
		COLLISION_GROUP_NONE,
		&tr
		);

	Msg("Hit: %s\n",
		tr.m_pEnt ? tr.m_pEnt->GetClassname() : "NONE");

	NDebugOverlay::Line(
		start,
		tr.endpos,
		0, 255, 0,
		true,
		10.0f
		);

	NDebugOverlay::Cross3D(
		tr.endpos,
		4,
		255, 0, 0,
		true,
		10.0f
		);

}