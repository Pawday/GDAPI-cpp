#pragma once

#include <gdapi/LevelsManager.hh>
#include <gdapi/tools/GDPlist.hh>

class LevelsManager
{
    std::string _rawXml;
public:
    LevelsManager();
    LevelsManager(GDPlist plist);
};
