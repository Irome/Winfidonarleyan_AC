/*
 * Copyright (C) 2016+     AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-GPL2
 * Copyright (C) 2008-2016 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 */

#include "WhoListCache.h"
#include "World.h"
#include "ObjectAccessor.h"
#include "Player.h"
#include "GuildMgr.h"

void WhoListStorageMgr::Update()
{
    // clear current list
    _whoListStorage.clear();
    _whoListStorage.reserve(sWorld->GetPlayerCount() + 1);

    HashMapHolder<Player>::MapType const& m = ObjectAccessor::GetPlayers();
    for (HashMapHolder<Player>::MapType::const_iterator itr = m.begin(); itr != m.end(); ++itr)
    {
        if (!itr->second->FindMap() || itr->second->GetSession()->PlayerLoading())
            continue;

        std::string playerName = itr->second->GetName();
        std::wstring widePlayerName;
        if (!Utf8toWStr(playerName, widePlayerName))
            continue;

        wstrToLower(widePlayerName);

        std::string guildName = sGuildMgr->GetGuildNameById(itr->second->GetGuildId());
        std::wstring wideGuildName;
        if (!Utf8toWStr(guildName, wideGuildName))
            continue;

        wstrToLower(wideGuildName);

        _whoListStorage.emplace_back(itr->second->GetGUID(), itr->second->GetTeamId(), itr->second->GetSession()->GetSecurity(), itr->second->getLevel(),
            itr->second->getClass(), itr->second->getRace(), itr->second->GetZoneId(), itr->second->getGender(), itr->second->IsVisible(),
            widePlayerName, wideGuildName, playerName, guildName);
    }
}
