#include <windows.h>
#include <shellapi.h>

int main() {
    NOTIFYICONDATA nid;
    ZeroMemory(&nid, sizeof(nid));
    nid.cbSize = sizeof(nid);
    nid.uID = 1;
    nid.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
    nid.hWnd = NULL;
    nid.uCallbackMessage = WM_USER + 1;
    nid.hIcon = LoadIcon(NULL, IDI_INFORMATION);
    lstrcpy(nid.szTip, "Test Notification");

    // Add the notification icon to the system tray
    Shell_NotifyIcon(NIM_ADD, &nid);

    // Show the notification
    MessageBox(NULL, "This is a test notification", "Notification", MB_OK);

    // Remove the icon after use
    Shell_NotifyIcon(NIM_DELETE, &nid);

    return 0;
}
