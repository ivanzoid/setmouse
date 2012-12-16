#include <windows.h>
#include <iostream>

int wmain(int argc, const wchar_t * argv[])
{
    int mouseSpeed = 0;
    int mouseSettings[3] = {0};

    if (argc == 1) {
        int result = 0;
        if (!SystemParametersInfo(SPI_GETMOUSESPEED, 0, &mouseSpeed, 0)) {
            std::wcerr << L"Failed to get mouse speed.\n"
                << L"Error code: " << GetLastError() << std::endl;
            result = -1;
        }
        if (!SystemParametersInfo(SPI_GETMOUSE, 0, mouseSettings, 0)) {
            std::wcerr << L"Failed to get mouse acceleration settings.\n"
                << L"Error code: " << GetLastError() << std::endl;
            result = -1;
        }
        if (result == 0) {
            std::wcout << mouseSpeed << L" " << mouseSettings[0] << L" " << mouseSettings[1]
                << L" " << mouseSettings[2] << std::endl;
        }
        return result;
    } else if (argc == 2 && wcscmp(argv[1], L"-h") == 0) {
        std::wcout << L"Usage: " << argv[0] << L" spd acc1 acc2 acc3\n"
            << L"   spd: mouse speed\n"
            << L"   acc1-acc3: mouse acceleration values\n"
            << L"Copyright © 2009 Ivan Zezyulya." << std::endl;
        return 0;
    } else if (argc == 5) {
        mouseSpeed = _wtoi(argv[1]);
        mouseSettings[0] = _wtoi(argv[2]);
        mouseSettings[1] = _wtoi(argv[3]);
        mouseSettings[2] = _wtoi(argv[4]);
        int result = 0;
        if (!SystemParametersInfo(SPI_SETMOUSESPEED, 0, PVOID(mouseSpeed), SPIF_SENDCHANGE)) {
            std::wcerr << L"Failed to set mouse speed.\n"
                << L"Error code: " << GetLastError() << std::endl;
            result = -1;
        }
        if (!SystemParametersInfo(SPI_SETMOUSE, 0, mouseSettings, SPIF_SENDCHANGE)) {
            std::wcerr << L"Failed to set mouse acceleration settings.\n"
                << L"Error code: " << GetLastError() << std::endl;
            result = -1;
        }
        return result;
    } else {
        std::wcout << L"Incorrect parameters. Try \"" << argv[0] << L" -h\" for help."
            << std::endl;
        return 1;
    }

    return 0;
}