#include <string>

#include <gdapi/tools/GDPlist.hh>


static const char testXmlInput[] = R"(<?xml version="1.0"?><plist version="1.0" gjver="2.0"><dict><k>LLM_01</k><d><k>_isArr</k><t /><k>k_0</k><d><k>kCEK</k><i>4</i><k>k2</k><s>Hello CPP</s><k>k5</k><s>Player</s><k>k13</k><t /><k>k21</k><i>2</i><k>k16</k><i>1</i><k>k50</k><i>35</i><k>kI1</k><r>0</r><k>kI2</k><r>0</r><k>kI3</k><r>0</r><k>kI6</k><d /></d></d><k>LLM_02</k><i>35</i></dict></plist>)";

int main()
{
    MemoryBlock inputBlock(sizeof(testXmlInput));
    memcpy_s(inputBlock.getPtr(), inputBlock.getSize(), testXmlInput, sizeof(testXmlInput));

    GDPlist plist(inputBlock);
}