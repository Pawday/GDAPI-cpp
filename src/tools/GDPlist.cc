#include "gdapi/tools/GDPlist.hh"

#include <cinttypes>
#include <cassert>

static bool seekXmlHeader(MemoryBlock& xml, size_t &seekAmRef)
{
    assert(seekAmRef < xml.getSize());

    char *ptr = static_cast<char *>(xml.getPtr());
    bool tagStarted = false;
    bool tagEnded = false;

    if (ptr[seekAmRef] == '<') tagStarted = true;
    seekAmRef++;

    while (tagStarted && !tagEnded)
        tagEnded = ptr[seekAmRef++] == '>';

    return tagStarted && tagEnded;
}

static bool parseTopPlistTag(MemoryBlock& xml, size_t &seekAmRef)
{

}

GDPlist::GDPlist(MemoryBlock& xml)
{
    size_t parseOffset = 0;
    if (!seekXmlHeader(xml, parseOffset)) return;




}
