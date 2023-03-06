#include <Windows.h>
#include <iostream>

struct SharedData {
    float HMDx;
    float HMDy;
    float HMDz;

    float HMDrotX;
    float HMDrotY;
    float HMDrotZ;

};


int main()
{
    HANDLE hMapFile = OpenFileMapping(
        FILE_MAP_ALL_ACCESS,   // read/write permission
        FALSE,                 // do not inherit name
        TEXT("SharedMemory")); // name of mapping object

    if (hMapFile == NULL)
    {
        std::cout << "Could not open file mapping object: " << GetLastError() << std::endl;
        return 1;
    }

    LPCTSTR pBuf = (LPTSTR)MapViewOfFile(
        hMapFile,            // handle to map object
        FILE_MAP_ALL_ACCESS, // read/write permission
        0,
        0,
        sizeof(SharedData));

    if (pBuf == NULL)
    {
        std::cout << "Could not map view of file: " << GetLastError() << std::endl;
        CloseHandle(hMapFile);
        return 1;
    }

    SharedData* pData = (SharedData*)pBuf;

    float HMDx;
    float HMDy;
    float HMDz;

    float HMDrotX;
    float HMDrotY;
    float HMDrotZ;

    while (true)
    {


        HMDx = pData->HMDx;
        HMDy = pData->HMDy;
        HMDz = pData->HMDz;

        HMDrotX = pData->HMDrotX;
        HMDrotY = pData->HMDrotY;
        HMDrotZ = pData->HMDrotZ;





        std::cout << "Read value HMDx : " << HMDx << " from shared memory" << std::endl;
        std::cout << "Read value HMDy: " << HMDy << " from shared memory" << std::endl;
        std::cout << "Read value HMDz :" << HMDz << " from shared memory" << std::endl;
        std::cout << "Read value HMDrotX :" << HMDrotX << " from shared memory" << std::endl;
        std::cout << "Read value HMDrotY : " << HMDrotY << " from shared memory" << std::endl;
        std::cout << "Read value HMDrotZ :" << HMDrotZ << " from shared memory" << std::endl;

        Sleep(10); // sleep for 1 second
    }

    UnmapViewOfFile(pBuf);
    CloseHandle(hMapFile);

    return 0;
}
