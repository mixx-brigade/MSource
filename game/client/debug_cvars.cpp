// (C) Valve Software, meowcat767 & MIXX Brigade
// ---------------------------------------------
// Purpose: hold ConVars for the debugging hud
// ---------------------------------------------
#include "cbase.h"
#include "tier1/convar.h"

ConVar cl_debug_hud("cl_debug_hud", "0", FCVAR_CLIENTDLL | FCVAR_ARCHIVE, "Toggles debug HUD");