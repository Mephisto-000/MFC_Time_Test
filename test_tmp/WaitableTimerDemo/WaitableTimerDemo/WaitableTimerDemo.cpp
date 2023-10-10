#include <windows.h>
#include <iostream>
#include <thread>

// 這個執行緒將等待計時器
void TimerThread(HANDLE hTimer) 
{   // 等待計時器信號，這將使執行緒暫停，直到計時器被觸發
    
    if (WaitForSingleObject(hTimer, INFINITE) != WAIT_OBJECT_0) {
        std::cerr << "WaitForSingleObject failed!" << std::endl;  // 等待失敗時輸出錯誤信息
    }
    else {
        std::cout << "Thread 1: Timer was signaled!" << std::endl;  // 計時器被觸發時，輸出提示信息
    }
}

// 這是另一個將等待計時器的執行緒
void AnotherTimerThread(HANDLE hTimer) 
{   // 與上面的執行緒功能相同，只是用於展示多個執行緒可以等待同一個計時器

    if (WaitForSingleObject(hTimer, INFINITE) != WAIT_OBJECT_0) {
        std::cerr << "WaitForSingleObject failed!" << std::endl;
    }
    else {
        std::cout << "Thread 2: Timer was signaled!" << std::endl;
    }
}

int main() {
    HANDLE hTimer = NULL;  // 定義一個計時器控制代碼
    LARGE_INTEGER liDueTime;  // 用於設置計時器的時間

    liDueTime.QuadPart = -100000000LL; // 設置計時器為10秒。負值表示相對時間。

    // 創建一個未命名的可等待計時器
    hTimer = CreateWaitableTimer(NULL, TRUE, NULL);
    if (NULL == hTimer) {
        std::cerr << "CreateWaitableTimer failed!" << std::endl;  // 創建計時器失敗時輸出錯誤信息
        return 1;
    }

    // 啟動兩個執行緒，它們都將等待上面創建的計時器
    std::thread t1(TimerThread, hTimer);  // 第一個執行緒
    std::thread t2(AnotherTimerThread, hTimer);  // 第二個執行緒

    std::cout << "Main thread: Waiting for 10 seconds..." << std::endl;  // 主執行緒輸出等待信息

    // 啟動計時器。當計時器過了10秒後，它將發出信號。
    if (!SetWaitableTimer(hTimer, &liDueTime, 0, NULL, NULL, 0)) {
        std::cerr << "SetWaitableTimer failed!" << std::endl;  // 啟動計時器失敗時輸出錯誤信息
        return 2;
    }

    // 主執行緒將等待上面創建的兩個執行緒完成它們的任務
    t1.join();  // 等待第一個執行緒完成
    t2.join();  // 等待第二個執行緒完成

    CloseHandle(hTimer);  // 關閉計時器控制代碼

    return 0;  // 主執行緒結束
}

