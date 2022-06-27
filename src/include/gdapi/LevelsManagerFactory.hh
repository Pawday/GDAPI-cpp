#pragma once

#include <gdapi/LevelsManager.hh>
class LevelsManagerFactory
{
public:
    static std::string getLocalManagerLocation();
    static const LevelsManager *getLocal();
};