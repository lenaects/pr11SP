// pr11_2.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "pr11_2.h"


#define MAX_LOADSTRING 100
#define IDC_PROGRESS1 2001
#define IDC_BUTTON1 2002
#define IDC_HOTKEY 2003
#define IDC_LIST 2004

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PR112, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PR112));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW|CS_DBLCLKS;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PR112));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PR112);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{


   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }
   CreateWindowEx(0, TEXT("Button"), TEXT("Кнопка"),
       BS_CENTER | WS_CHILD | WS_VISIBLE,
       220, 10, 100, 25,
       hWnd, (HMENU)IDC_BUTTON1, hInstance, NULL);
  HWND hProgress= CreateWindowEx(0,TEXT("msctls_progress32"), NULL,
       BS_CENTER | WS_CHILD | WS_VISIBLE,
       220, 50, 200, 30,
       hWnd,(HMENU)IDC_PROGRESS1 , hInstance, NULL);
  HWND hHotKey = CreateWindowEx(0, HOTKEY_CLASS, NULL,
      BS_CENTER | WS_CHILD | WS_VISIBLE,
      220, 90, 100, 25,
      hWnd, (HMENU)IDC_HOTKEY, hInstance, NULL);
  HWND hList = CreateWindowEx(0,TEXT("LISTBOX") , NULL,
      BS_CENTER | WS_CHILD | WS_VISIBLE,
      10, 10, 200, 150,
      hWnd, (HMENU)IDC_LIST, hInstance, NULL);
  SendMessage(hProgress, PBM_SETPOS, 50, 0);
  SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)L"text1");
  SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)L"text2"); 
  SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)L"text3");
  ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
// 
  
FINDREPLACE fr;
TCHAR szFindWhat[80] = TEXT("");    
TCHAR szReplaceWhat[80] = TEXT("");   
BOOL showMasag = FALSE;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    OPENFILENAME  ofn;
   
  
    static TCHAR szFileName[MAX_PATH];
   
    switch (message)
    {
    case WM_CREATE:{
        SetTimer(hWnd, 1, 1000, NULL);//установка таймера
        }  
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_SAVEAS:
                ZeroMemory(&ofn,sizeof(ofn));
                ofn.lStructSize = sizeof(ofn);
                ofn.hwndOwner = NULL;
                ofn.lpstrFile = szFileName;
                ofn.lpstrFile[0] = '\0';
                ofn.nMaxFile = sizeof(szFileName);
                ofn.lpstrFilter = TEXT("All Files\0*.*\0");
                ofn.nFilterIndex = 1;
                ofn.lpstrFileTitle = NULL;
                ofn.nMaxFileTitle = 0;
                ofn.lpstrInitialDir = NULL;
                ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
                if (GetSaveFileName(&ofn) == TRUE) {
                    MessageBox(hWnd, szFileName, TEXT("Выберите файл"), MB_OK);
                }

                break;
            case Replase:
                ZeroMemory(&fr, sizeof(fr));
                fr.lStructSize = sizeof(fr);
                fr.hwndOwner = hWnd;               
                fr.wFindWhatLen = sizeof(szFindWhat);
                fr.wReplaceWithLen = sizeof(szReplaceWhat);
                fr.Flags = FR_DOWN;                
                fr.lpstrFindWhat = szFindWhat;
                fr.lpstrReplaceWith = szReplaceWhat;
                if (ReplaceText(&fr)!=FALSE)
                {
                   
                }
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
        //таймер
    case WM_TIMER: {
        if (wParam == 1 && !showMasag) {
            showMasag = TRUE;
            KillTimer(hWnd, 1);
            MessageBox(hWnd, L"Сработал таймер после 5 секунд, после запуска", L"Информация", MB_OK | MB_ICONINFORMATION);                       
        }
    }
     break;
    case WM_CHAR: {
        TCHAR chars = static_cast<TCHAR>(wParam);
        TCHAR text[64];
        wsprintf(text, L"Был нажат символ:%C", chars);
        MessageBox(hWnd, text, L"WM_CHAR message", MB_OK | MB_ICONINFORMATION);
    }
     break;
    case WM_KEYUP: {
        TCHAR text[64];
        wsprintf(text, L"Клавиша с кодом %d была отпущена", wParam);
        MessageBox(hWnd, text, L"WM_KEYUP message", MB_OK | MB_ICONINFORMATION);
    }
      break;
    case WM_MBUTTONDBLCLK: {
        MessageBox(hWnd, L"Произведен двойной щелчок средней кнопкой мыши", L"WM_MBUTTONDBLCLK message", MB_OK | MB_ICONINFORMATION); 
        break;
    }
              
    case WM_MBUTTONDOWN: {
        MessageBox(hWnd, L"Произведен щелчок средней кнопкой мыши", L"WM_MBUTTONDOWN", MB_OK | MB_ICONINFORMATION);
    }
                 break;
    case WM_MBUTTONUP: {
        MessageBox(hWnd, L"Произведен щелчок средней кнопкой мыши", L"WM_MBUTTONUP", MB_OK | MB_ICONINFORMATION);
    }
                 break;
    case WM_MOUSEWHEEL: {
        
        MessageBox(hWnd, L"Колесо мыши прокуричиваеться", L"WM_MOUSEWHEEL message", MB_OK | MB_ICONINFORMATION);
    }
                 break;
    case WM_MOVING: {
        MessageBox(hWnd, L"Окно переместилось", L"WM_MOVINGL message", MB_OK | MB_ICONINFORMATION);
    }
                      break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
            EndPaint(hWnd, &ps);
        }
        break;
    
    case WM_DESTROY:
        if (!showMasag) {
            KillTimer(hWnd, 1);
        }
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
