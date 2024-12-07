#include <windows.h>
#include <shellapi.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    // Declare necessary variables
    NOTIFYICONDATA nid;
    char message[256];
    int duration;

    // Prompt user for notification message
    printf("Enter your notification message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = 0;  // Remove the newline character at the end if present

    // Prompt user for duration in seconds
    printf("Enter the duration in seconds: ");
    while (scanf("%d", &duration) != 1 || duration < 1) {
        // If input is invalid or negative, ask again
        printf("Invalid input. Please enter a positive number: ");
        while (getchar() != '\n'); // Clear the input buffer
    }

    // Initialize NOTIFYICONDATA structure
    ZeroMemory(&nid, sizeof(nid));
    nid.cbSize = sizeof(nid);
    nid.uID = 1;
    nid.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
    nid.hWnd = NULL;
    nid.uCallbackMessage = WM_USER + 1;
    nid.hIcon = LoadIcon(NULL, IDI_INFORMATION);
    lstrcpy(nid.szTip, message);  // Set message as the tooltip

    // Wait for the user-specified duration (before showing the notification)
    printf("Waiting for %d seconds before showing the message...\n", duration);
    Sleep(duration * 1000);  // Convert seconds to milliseconds

    // Add the notification icon to the system tray
    Shell_NotifyIcon(NIM_ADD, &nid);

    // Show the notification message in a MessageBox
    MessageBox(NULL, message, "Notification", MB_OK);

    // Wait for the user-specified duration before removing the notification icon
    printf("Notification will disappear in %d seconds...\n", duration);
    Sleep(duration * 1000);  // Wait for the same duration before removing the icon

    // Remove the notification icon from the system tray
    Shell_NotifyIcon(NIM_DELETE, &nid);

    return 0;
}
