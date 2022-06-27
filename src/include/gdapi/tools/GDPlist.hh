#pragma once
#include "gdapi/tools/MemoryBlock.hh"

#include <string>

class GDPlist
{
    std::string _gjVersion;
    std::string _version;

    GDPlist *root = nullptr;
public:
    explicit GDPlist(MemoryBlock& xml);
};

class GDPlistValue
{
    
};