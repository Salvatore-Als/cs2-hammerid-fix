/**
 * =============================================================================
 * HammerIdFix
 * Copyright (C) 2023-2026 Poggu, Forked by Kriax
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

#include "configmanager.h"
#include "tier0/dbg.h"

void CConfigManager::Init()
{
	g_fileSystem->CreateDirHierarchy("addons/configs/hammerid_fix", "MOD");

	if (!g_fileSystem->FileExists(CONFIG_FILE, "MOD"))
	{
		ConMsg("HammerIdFix: Config file not found, creating default: %s\n", CONFIG_FILE);

		KeyValues *defaultKV = new KeyValues("Config");
		defaultKV->SetInt("offsetlinux", 117);
		defaultKV->SetInt("offsetwindow", 118);
		defaultKV->SaveToFile(g_fileSystem, CONFIG_FILE, "MOD");
		delete defaultKV;
	}

	// Load the config
	KeyValues *kv = new KeyValues("Config");

	if (!kv->LoadFromFile(g_fileSystem, CONFIG_FILE, "MOD"))
	{
		ConMsg("HammerIdFix: Failed to load config file: %s, using defaults\n", CONFIG_FILE);
		m_offsetLinux = 117;
		m_offsetWindows = 118;
		delete kv;
		return;
	}

	KeyValues::AutoDelete autoDelete(kv);

	m_offsetLinux = kv->GetInt("offsetlinux", 117);
	m_offsetWindows = kv->GetInt("offsetwindow", 118);

	ConMsg("HammerIdFix: Loaded config - offsetlinux: %d, offsetwindow: %d\n", m_offsetLinux, m_offsetWindows);
}
