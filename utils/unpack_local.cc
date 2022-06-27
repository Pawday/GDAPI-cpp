#include <string>
#include <fstream>
#include <iostream>

#include <gdapi/LevelsManagerFactory.hh>
#include <gdapi/tools/crypt/GDCoder.hh>

void printMsgAndExitIfFalse(bool status, const std::string& message)
{
    if (status)
    {
        std::cout << message;
        std::exit(1);
    }
}

int main()
{
    std::string location = LevelsManagerFactory::getLocalManagerLocation();

    std::fstream file;

    file.open(location, std::ios::in | std::ifstream::binary | std::ifstream::ate);

    printMsgAndExitIfFalse(!file, ((std::string) "Error opening file: ").append(location));

    MemoryBlock block(file.tellg());

    file.seekg(0);

    file.read((char*) block.getPtr(), block.getSize());

    printMsgAndExitIfFalse(!file, ((std::string) "Error reading file: ").append(location));

    file.close();

    printMsgAndExitIfFalse(!GDCoder::decode(block), "Error decoding file");

    std::ofstream xmlOut;

    xmlOut.open("./CCLocalLevels.xml", std::ios::out | std::ifstream::binary);

    printMsgAndExitIfFalse(!xmlOut, "Error opening output file");

    xmlOut.write((char*)block.getPtr(), block.getSize());

    printMsgAndExitIfFalse(!xmlOut, "Error writing to output file");
    xmlOut.flush();
    xmlOut.close();
}