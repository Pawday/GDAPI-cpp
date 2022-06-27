#include <string>
#include <memory>
#include <cassert>

#include <Windows.h>
#include <gdapi/tools/crypt/GDCoder.hh>

#include "gdapi/LevelsManagerFactory.hh"


const LevelsManager *LevelsManagerFactory::getLocal()
{
    std::string lmPath = getLocalManagerLocation();

    HANDLE datFile = CreateFileA
    (
        lmPath.c_str(),
        GENERIC_READ,
        0,
        nullptr,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        nullptr
    );

    if (datFile == INVALID_HANDLE_VALUE) return nullptr;

    DWORD fileSize;
    fileSize = GetFileSize
    (
        datFile,
        &fileSize
    );

    MemoryBlock fileData(fileSize);

    {
        DWORD written;
        ReadFile
        (
            datFile,
            fileData.getPtr(),
            fileData.getSize(),
            &written,
            nullptr
        );

        assert(written == fileData.getSize());
    }

    CloseHandle(datFile);

    GDCoder::decode(fileData);

    GDPlist gdPlist(fileData);

    return new LevelsManager(gdPlist);;
}

std::string LevelsManagerFactory::getLocalManagerLocation()
{
    std::string lmPath;

    {
        DWORD appDataPathSize = GetEnvironmentVariableA("LOCALAPPDATA", nullptr, 0);
        lmPath.reserve(appDataPathSize);

        char* path_cstr = new char[appDataPathSize];
        GetEnvironmentVariableA("LOCALAPPDATA", path_cstr, appDataPathSize);
        lmPath.append(path_cstr);
        delete[] path_cstr;
    }

    lmPath.append(R"(\GeometryDash\CCLocalLevels.dat)");

    return lmPath;
}
