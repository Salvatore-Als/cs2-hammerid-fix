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

#pragma once
#include "KeyValues.h"
#include "filesystem.h"

#define CONFIG_FILE "addons/configs/hammerid_fix/config.ini"

extern IFileSystem *g_fileSystem;

class CConfigManager
{
public:
	CConfigManager()
	{
		Init();
	}

	uint16_t GetOffsetLinux() { return m_offsetLinux; }
	uint16_t GetOffsetWindows() { return m_offsetWindows; }

private:
	uint16_t m_offsetLinux;
	uint16_t m_offsetWindows;
	void Init();
};

extern CConfigManager *g_configManager;
