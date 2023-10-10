#include <windows.h>
#include <iostream>

// 定義計時器的ID，用於識別是哪一個計時器所觸發的事件
#define MY_TIMER_ID 1

LRESULT CALLBACK TestProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
    switch (uMsg) 
    {
    case WM_CREATE: 
    {   // 當窗口被創建時，我們設定一個計時器，每1000毫秒（即1秒）就觸發一次
        
        SetTimer(hwnd, MY_TIMER_ID, 1000, NULL);
    } break;

    case WM_TIMER: 
    {   // 當計時器觸發時，會收到此消息
        // 我們檢查是哪一個計時器，然後執行相對應的動作
        
        if (wParam == MY_TIMER_ID) {
            std::cout << "Timer ticked!" << std::endl;  // 輸出訊息表示計時器已觸發
        }
    } break;

    case WM_DESTROY: 
    {   // 窗口被銷毀前，銷毀我們之前創建的計時器，釋放資源
        
        KillTimer(hwnd, MY_TIMER_ID);
        PostQuitMessage(0);  // 發送結束消息，結束消息循環
        return 0;
    } break;

    default:
        // 其他消息，交由默認的窗口處理函數處理
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

int main() {
    // 註冊窗口類，為了創建窗口
    WNDCLASS wc = {};
    wc.lpfnWndProc = TestProc;  // 指定窗口消息處理函數
    wc.hInstance = GetModuleHandle(NULL);  // 獲取當前應用程式的實例句柄
    wc.lpszClassName = L"SampleTimerWindow";  // 指定窗口類的名稱

    RegisterClass(&wc);  // 註冊窗口類

    // 創建窗口
    HWND hwnd = CreateWindowEx(
        0,                              // 額外的窗口風格
        L"SampleTimerWindow",           // 窗口類名稱
        L"SetTimer Example",            // 窗口的標題
        WS_OVERLAPPEDWINDOW,            // 基本的窗口風格
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL,       // 父窗口的句柄
        NULL,       // 菜單的句柄
        GetModuleHandle(NULL),  // 應用程式的實例句柄
        NULL        // 額外的應用程式數據
    );

    if (hwnd == NULL) {
        return 0;  // 若窗口創建失敗，則結束程式
    }

    ShowWindow(hwnd, SW_SHOW);  // 顯示窗口

    // 消息循環，處理並分發窗口消息
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);  // 進行消息翻譯
        DispatchMessage(&msg);   // 分發消息至對應的窗口處理函數
    }

    return 0;  // 程式結束
}
