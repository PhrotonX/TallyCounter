#include <windows.h>
#include <iostream>
#include <string>
#include <tchar.h>
#include "resource.h"
const char g_szClassName[] = "windowClass";

int tally[5] = {0, 0, 0, 0, 0};

INT_PTR AboutProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
    switch(msg){
        case WM_CLOSE:
            EndDialog(hwnd, 0);
            break;
        case WM_INITDIALOG:
            break;
        case WM_COMMAND:
            switch(LOWORD(wParam)){
                case ID_C1_INS:
                    tally[0]++;
                    HWND hEdit_tally_1 = GetDlgItem(hwnd, IDC_C1_EDIT);
                    std::__cxx11::string str_tally_1 = std::__cxx11::to_string(tally[0]);
                    char const *char_tally_1 = str_tally_1.c_str();
                    TCHAR*pszTally1 = char_tally_1;
                    SendMessage(hEdit_tally_1, EM_REPLACESEL, 0, (LPARAM)pszTally1);
                    break;
                case ID_ABOUT_OK:
                    EndDialog(hwnd, 0);
                    break;
            }
            break;
        default:
            return FALSE;
    }
    return TRUE;
}

INT_PTR DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
    switch(msg){
        case WM_CLOSE:
            ShowWindow(GetConsoleWindow(), SW_SHOW);
            EndDialog(hwnd, 0);
            break;
        case WM_INITDIALOG:
            break;
        case WM_COMMAND:
            switch(LOWORD(wParam)){
                case ID_ABOUT:
                    DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG2), NULL, AboutProc);
                    break;
                case ID_CLOSE:
                    ShowWindow(GetConsoleWindow(), SW_SHOW);
                    EndDialog(hwnd, 0);
                    break;
            }
            break;
        default:
            return FALSE;
    }
    return TRUE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}
