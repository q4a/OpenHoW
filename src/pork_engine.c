/* OpenHoW
 * Copyright (C) 2017-2018 Mark Sowden <markelswo@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <PL/platform_filesystem.h>

#include "pork_engine.h"
#include "pork_map.h"
#include "pork_language.h"
#include "pork_formats.h"
#include "pork_game.h"

#include "script/script.h"

#include "client/client.h"
#include "server/server.h"

EngineState g_state;

const char *GetBasePath(void) {
    pork_assert(cv_base_path);
    return cv_base_path->s_value;
}

const char *GetCampaignPath(void) {
    pork_assert(cv_campaign_path);
    return cv_campaign_path->s_value;
}

//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////

/* pork_extractor.c */
void ExtractGameData(const char *path);

/* pork_config.c */
void InitConfig(void);
void SaveConfig(const char *path);
void ReadConfig(const char *path);

void InitPlayers(void);
void InitModels(void);

void InitEngine(void) {
    LogInfo("initializing engine (%d.%d.%d)...\n",
            ENGINE_MAJOR_VERSION,
            ENGINE_MINOR_VERSION,
            ENGINE_PATCH_VERSION);

    memset(&g_state, 0, sizeof(EngineState));

    InitConsole();

    // check for any command line arguments

    const char *var;
    if((var = plGetCommandLineArgumentValue("-path")) != NULL) {
        if(!plPathExists(var)) {
            LogWarn("invalid path \"%s\", does not exist, ignoring!\n");
        }

        plSetConsoleVariable(cv_base_path, var);
    }

    InitScripting();
    InitConfig();

    RegisterFormatInterfaces();

    /* load in the manifests */

    RegisterLanguages();
    RegisterCampaigns();

    if((var = plGetCommandLineArgumentValue("-mod")) != NULL ||
       (var = plGetCommandLineArgumentValue("-campaign")) != NULL) {
        SetCampaign(var);
    }

    /* now initialize all other sub-systems */

    InitClient();
    InitServer();
    InitPlayers();
    InitModels();
    InitMaps();

    LogInfo("base path: \"%s\"\n", GetBasePath());
    LogInfo("campaign path: \"%s/campaigns/%s\"\n", GetBasePath(), GetCampaignPath());
    LogInfo("working directory: \"%s\"\n", plGetWorkingDirectory());
}

bool IsPorkRunning(void) {
    return true;
}

void SimulatePork(void) {
    g_state.sim_ticks = System_GetTicks();

    SimulateClient();
    SimulateServer();

    g_state.last_sim_tick = System_GetTicks();
}

void ShutdownEngine(void) {
    ClearPlayers();

    ShutdownClient();

    ShutdownServer();
    ShutdownScripting();

    SaveConfig(g_state.config_path);

    plShutdown();
}