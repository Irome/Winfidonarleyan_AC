/*
 * Copyright (C) 2016+     AzerothCore <www.azerothcore.org>, released under GNU GPL v2 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-GPL2
 * Copyright (C) 2008-2016 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 */

#ifndef __WHOLISTCACHE_H
#define __WHOLISTCACHE_H

#include "Common.h"
#include "SharedDefines.h"

class WhoListPlayerInfo
{
public:
    WhoListPlayerInfo(uint64 guid, TeamId team, AccountTypes security, uint8 level, uint8 clss, uint8 race, uint32 zoneid, uint8 gender, bool visible, std::wstring const& widePlayerName,
        std::wstring const& wideGuildName, std::string const& playerName, std::string const& guildName) :
        _guid(guid), _team(team), _security(security), _level(level), _class(clss), _race(race), _zoneid(zoneid), _gender(gender), _visible(visible),
        _widePlayerName(widePlayerName), _wideGuildName(wideGuildName), _playerName(playerName), _guildName(guildName) {}

    uint64 GetGuid() const { return _guid; }
    TeamId GetTeamId() const { return _team; }
    AccountTypes GetSecurity() const { return _security; }
    uint8 GetLevel() const { return _level; }
    uint8 GetClass() const { return _class; }
    uint8 GetRace() const { return _race; }
    uint32 GetZoneId() const { return _zoneid; }
    uint8 GetGender() const { return _gender; }
    bool IsVisible() const { return _visible; }
    std::wstring const& GetWidePlayerName() const { return _widePlayerName; }
    std::wstring const& GetWideGuildName() const { return _wideGuildName; }
    std::string const& GetPlayerName() const { return _playerName; }
    std::string const& GetGuildName() const { return _guildName; }

private:
    uint64 _guid;
    TeamId _team;
    AccountTypes _security;
    uint8 _level;
    uint8 _class;
    uint8 _race;
    uint32 _zoneid;
    uint8 _gender;
    bool _visible;
    std::wstring _widePlayerName;
    std::wstring _wideGuildName;
    std::string _playerName;
    std::string _guildName;
};

typedef std::vector<WhoListPlayerInfo> WhoListInfoVector;

class WhoListStorageMgr
{
private:
    WhoListStorageMgr() { };
    ~WhoListStorageMgr() { };

public:

    void Update();
    WhoListInfoVector const& GetWhoList() const { return _whoListStorage; }

protected:
    WhoListInfoVector _whoListStorage;
};

#define sWhoListStorageMgr ACE_Singleton<WhoListStorageMgr, ACE_Null_Mutex>::instance()

#endif
