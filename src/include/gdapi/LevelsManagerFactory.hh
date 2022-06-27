#pragma once

#include <gdapi/LevelsManager.hh>
class LevelsManagerFactory
{
public:
    static const LevelsManager *getLocal();
};