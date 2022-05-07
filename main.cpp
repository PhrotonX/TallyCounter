#include <windows.h>
#include <iostream>
#include <string>
#include <sstream>
#include <tchar.h>
#include "resource.h"
const char g_szClassName[] = "windowClass";

int tally[5] = {0, 0, 0, 0, 0};
//char aboutText[0xFFF];
std::string tally_buffer = "";
std::stringstream aboutStringSS("Tally Counter\nVersion ", std::ios_base::app | std::ios_base::out | std::ios_base::trunc);
std::string aboutString;
const char* aboutText;

void countValue(HWND hwnd, int htally){
    //Set window focus to edit box
    SetFocus(hwnd);

    //Clear edit box contents
    SetWindowText(hwnd, "");

    //Convert int to string
    tally_buffer = std::__cxx11::to_string(htally);

    //Insert tally string
    SendMessage(hwnd, EM_SETSEL, (WPARAM)GetWindowTextLength(hwnd), (LPARAM)GetWindowTextLength(hwnd));
    SendMessage(hwnd, EM_REPLACESEL, 0, (LPARAM)tally_buffer.c_str());
}

INT_PTR AboutProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
    switch(msg){
    case WM_CLOSE:
        EndDialog(hwnd, 0);
        break;
    case WM_INITDIALOG:
        SetDlgItemText(hwnd, IDS_ABOUT, aboutText);
        break;
    case WM_COMMAND:
        switch(LOWORD(wParam)){
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

INT_PTR EditProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
    switch(msg){
    case WM_CLOSE:
        EndDialog(hwnd, 0);
        break;
    case WM_INITDIALOG:
        break;
    case WM_COMMAND:
        switch(LOWORD(lParam)){
        case ID_CLOSE:
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
    //Edit box
    HWND hEdit_tally[5] = {NULL, NULL, NULL, NULL, NULL};

    hEdit_tally[0] = GetDlgItem(hwnd, IDC_C1_EDIT);
    hEdit_tally[1] = GetDlgItem(hwnd, IDC_C2_EDIT);
    hEdit_tally[2] = GetDlgItem(hwnd, IDC_C3_EDIT);
    hEdit_tally[3] = GetDlgItem(hwnd, IDC_C4_EDIT);
    hEdit_tally[4] = GetDlgItem(hwnd, IDC_C5_EDIT);

    switch(msg){
        case WM_CLOSE:
            ShowWindow(GetConsoleWindow(), SW_SHOW);
            EndDialog(hwnd, 0);
            break;
        case WM_INITDIALOG:
            //Set strings for about dialog box
            aboutStringSS << VER_MAJOR << "." << VER_MINOR << "." << VER_REV << "." << VER_DEV << " build " << BUILD << "\n"
            << "Developer: Phroton\nAlpha Development Phase 1\nFor more info, click the debug button.";
            aboutString = aboutStringSS.str();
            aboutText = aboutString.c_str();

            //Set debug info on console window
            std::cout << "Version: " << VER_MAJOR << "." << VER_MINOR << "." << VER_REV << "." << VER_DEV << std::endl;
            std::cout << "Build No: " << BUILD << std::endl;
            std::cout << "Compiled: " << __DATE__ << ", " << __TIME__ << std::endl;
            break;
        case WM_COMMAND:
            switch(LOWORD(wParam)){
                case ID_C1_INS:
                    tally[0]++;
                    countValue(hEdit_tally[0], tally[0]);
                    break;
                case ID_C1_DEL:
                    tally[0]--;
                    countValue(hEdit_tally[0], tally[0]);
                    break;
                case ID_C2_INS:
                    tally[1]++;
                    countValue(hEdit_tally[1], tally[1]);
                    break;
                case ID_C2_DEL:
                    tally[1]--;
                    countValue(hEdit_tally[1], tally[1]);
                    break;
                case ID_C3_INS:
                    tally[2]++;
                    countValue(hEdit_tally[2], tally[2]);
                    break;
                case ID_C3_DEL:
                    tally[2]--;
                    countValue(hEdit_tally[2], tally[2]);
                    break;
                case ID_C4_INS:
                    tally[3]++;
                    countValue(hEdit_tally[3], tally[3]);
                    break;
                case ID_C4_DEL:
                    tally[3]--;
                    countValue(hEdit_tally[3], tally[3]);
                    break;
                case ID_C5_INS:
                    tally[4]++;
                    countValue(hEdit_tally[4], tally[4]);
                    break;
                case ID_C5_DEL:
                    tally[4]--;
                    countValue(hEdit_tally[4], tally[4]);
                    break;
                case ID_EDIT:
                    DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG3), NULL, EditProc);
                    break;
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
    //ShowWindow(GetConsoleWindow(), SW_HIDE);
    return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}
