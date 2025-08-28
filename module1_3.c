// CreateProcess example (MinGW / Win32)
#include <windows.h>
#include <stdio.h>

int main() {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // เปลี่ยน commandLine เป็น URL ของ YouTube
   char commandLine[] = "\"C:\\Program Files\\Google\\Chrome\\Application\\chrome.exe\" https://www.youtube.com";

    printf("Parent PID: %lu\n", GetCurrentProcessId());

    BOOL ok = CreateProcessA(
        NULL, // Application name (NULL -> use commandLine)
        commandLine, // Command line (mutable buffer)
        NULL, NULL, // Process/Thread security
        FALSE, // Inherit handles
        0, // Creation flags
        NULL, // Environment
        NULL, // Current directory
        &si, &pi);

    if (!ok) {
        DWORD e = GetLastError();
        printf("CreateProcess failed (error %lu)\n", e);
        return 1;
    }

    printf("Child PID: %lu\n", pi.dwProcessId);

    // รอจนกว่าโปรแกรมจะปิด
    WaitForSingleObject(pi.hProcess, INFINITE);

    // ปิด handle ของ process และ thread
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}
    