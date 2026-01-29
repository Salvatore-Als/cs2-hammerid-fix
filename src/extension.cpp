/**
 * =============================================================================
 * HammerIdFix
 * Copyright (C) 2023-2024 Poggu
 * =============================================================================
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License, version 3.0, as published by the
 * Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include "extension.h"
#include "iserver.h"
#include <cstdint>
#include "utils/module.h"
#include "configmanager.h"

HammerIdFix g_hammerIdFix;
IServerGameDLL* server = NULL;
IServerGameClients* gameclients = NULL;
IVEngineServer* engine = NULL;
IGameEventManager2* gameevents = NULL;
ICvar* icvar = NULL;
IFileSystem* g_fileSystem = NULL;
CConfigManager* g_configManager = NULL;


class CGameEntitySystem;

CGameEntitySystem* GameEntitySystem()
{
	return nullptr;
}


// Should only be called within the active game loop (i e map should be loaded and active)
// otherwise that'll be nullptr!
CGlobalVars* GetGameGlobals()
{
	INetworkGameServer* server = g_pNetworkServerService->GetIGameServer();

	if (!server)
		return nullptr;

	return g_pNetworkServerService->GetIGameServer()->GetGlobals();
}

PLUGIN_EXPOSE(HammerIdFix, g_hammerIdFix);
bool HammerIdFix::Load(PluginId id, ISmmAPI* ismm, char* error, size_t maxlen, bool late)
{
	PLUGIN_SAVEVARS();

	GET_V_IFACE_CURRENT(GetEngineFactory, engine, IVEngineServer, INTERFACEVERSION_VENGINESERVER);
	GET_V_IFACE_CURRENT(GetEngineFactory, icvar, ICvar, CVAR_INTERFACE_VERSION);
	GET_V_IFACE_ANY(GetServerFactory, server, IServerGameDLL, INTERFACEVERSION_SERVERGAMEDLL);
	GET_V_IFACE_ANY(GetServerFactory, gameclients, IServerGameClients, INTERFACEVERSION_SERVERGAMECLIENTS);
	GET_V_IFACE_ANY(GetServerFactory, g_pSource2ServerConfig, ISource2ServerConfig, INTERFACEVERSION_SERVERCONFIG);
	GET_V_IFACE_ANY(GetEngineFactory, g_pNetworkServerService, INetworkServerService, NETWORKSERVERSERVICE_INTERFACE_VERSION);
	GET_V_IFACE_CURRENT(GetEngineFactory, g_pGameResourceServiceServer, IGameResourceService, GAMERESOURCESERVICESERVER_INTERFACE_VERSION);
	GET_V_IFACE_CURRENT(GetFileSystemFactory, g_fileSystem, IFileSystem, FILESYSTEM_INTERFACE_VERSION);

	g_SMAPI->AddListener(this, this);

	ConMsg("HammerIdFix loaded\n");

	g_pCVar = icvar;
	ConVar_Register(FCVAR_RELEASE | FCVAR_CLIENT_CAN_EXECUTE | FCVAR_GAMEDLL);

	g_configManager = new CConfigManager();

	CModule server(GAMEBIN, "server");
	auto CBaseEntityVTable = server.FindVirtualTable("CBaseEntity");

#ifdef WIN32
	uint16 offset = g_configManager->GetOffsetWindows();
#else
	uint16 offset = g_configManager->GetOffsetLinux();
#endif

	Plat_WriteMemory(*(void**)((uintptr_t*)CBaseEntityVTable + offset), (uint8_t*)"\xB0\x01", 2);
	return true;
}

bool HammerIdFix::Unload(char* error, size_t maxlen)
{
	delete g_configManager;
	return true;
}


void HammerIdFix::AllPluginsLoaded()
{
}

void HammerIdFix::OnLevelInit(char const* pMapName,
	char const* pMapEntities,
	char const* pOldLevel,
	char const* pLandmarkName,
	bool loadGame,
	bool background)
{
}

void HammerIdFix::OnLevelShutdown()
{
}

bool HammerIdFix::Pause(char* error, size_t maxlen)
{
	return true;
}

bool HammerIdFix::Unpause(char* error, size_t maxlen)
{
	return true;
}

const char* HammerIdFix::GetLicense()
{
	return "GPLv3";
}

const char* HammerIdFix::GetVersion()
{
	return "1.0.0";
}

const char* HammerIdFix::GetDate()
{
	return __DATE__;
}

const char* HammerIdFix::GetLogTag()
{
	return "HammerIdFix";
}

const char* HammerIdFix::GetAuthor()
{
	return "Poggu";
}

const char* HammerIdFix::GetDescription()
{
	return "Fixes hammerids not applying on entities outside of tools";
}

const char* HammerIdFix::GetName()
{
	return "HammerIdFix";
}

const char* HammerIdFix::GetURL()
{
	return "https://poggu.me/";
}