#include <windows.h>
#include <powrprof.h>
#include <strsafe.h>

#pragma comment(lib, "PowrProf.lib")

#define BUTTON_ID 1
#define LABEL_ID 2

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    static bool isPowerSaver = false;
    static HWND hButton, hLabel;

    switch (msg) {
    case WM_CREATE:
        hButton = CreateWindow(
            L"BUTTON", L"Switch to Power Saver",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            10, 10, 200, 30,
            hwnd, (HMENU)BUTTON_ID,
            (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);

        hLabel = CreateWindow(
            L"STATIC", L"Current Mode: Balanced",
            WS_VISIBLE | WS_CHILD,
            10, 50, 200, 30,
            hwnd, (HMENU)LABEL_ID,
            (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
        break;

    case WM_COMMAND:
        if (LOWORD(wParam) == BUTTON_ID) {
            if (isPowerSaver) {
                // Run the command to switch to Balanced mode
                ShellExecute(NULL, L"open", L"cmd.exe", L"/C powercfg /setactive SCHEME_BALANCED", NULL, SW_HIDE);
                SetWindowText(hButton, L"Switch to Power Saver");
                SetWindowText(hLabel, L"Current Mode: Balanced");
                isPowerSaver = false;
            }
            else {
                // Run the command to switch to Power Saver mode
                ShellExecute(NULL, L"open", L"cmd.exe", L"/C powercfg /setactive SCHEME_MAX", NULL, SW_HIDE);
                SetWindowText(hButton, L"Switch to Balanced");
                SetWindowText(hLabel, L"Current Mode: Power Saver");
                isPowerSaver = true;
            }
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const wchar_t className[] = L"PowerSwitcher";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProcedure;
    wc.hInstance = hInstance;
    wc.lpszClassName = className;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0, className, L"Power Mode Switcher",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 250, 150,
        NULL, NULL, hInstance, NULL);

    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}