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



    HANDLE hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE,   // use paging file
        NULL,                   // default security
        PAGE_READWRITE,         // read/write access
        0,                      // maximum object size (high-order DWORD)
        sizeof(SharedData),            // maximum object size (low-order DWORD)
        TEXT("SharedMemory"));  // name of mapping object

    if (hMapFile == NULL)
    {
        std::cout << "Could not create file mapping object: " << GetLastError() << std::endl;
        return 1;
    }

    LPCTSTR pBuf = (LPTSTR)MapViewOfFile(
        hMapFile,          // handle to map object
        FILE_MAP_ALL_ACCESS,  // read/write permission
        0,
        0,
        sizeof(int));

    if (pBuf == NULL)
    {
        std::cout << "Could not map view of file: " << GetLastError() << std::endl;
        CloseHandle(hMapFile);
        return 1;
    }

    SharedData* pData = (SharedData*)pBuf;

    float value = 0.f;
    while (true)
    {
        value++;
        pData->HMDx = value;
        pData->HMDy = value;
        pData->HMDz = value;
        pData->HMDrotX = value;
        pData->HMDrotY = value;
        pData->HMDrotZ = value;
        std::cout << "Wrote value " << pData->HMDx << " to shared memory" << std::endl;
        std::cout << "Wrote value " << pData->HMDy << " to shared memory" << std::endl;
        std::cout << "Wrote value " << pData->HMDz << " to shared memory" << std::endl;
        std::cout << "Wrote value " << pData->HMDrotX << " to shared memory" << std::endl;
        std::cout << "Wrote value " << pData->HMDrotY << " to shared memory" << std::endl;
        std::cout << "Wrote value " << pData->HMDrotZ << " to shared memory" << std::endl;

        Sleep(10); // sleep for 1 second

        value = pData->HMDrotX;
        std::cout << "Read value " << value << " from shared memory" << std::endl;

    }

    UnmapViewOfFile(pBuf);
    CloseHandle(hMapFile);

    return 0;
}