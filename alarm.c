#include <stdio.h>
#include <windows.h>

void trigger_alarm() {
    // Play a sound (simple beep)
    Beep(1000, 1000);  // Frequency 1000 Hz, duration 1000 ms

    // Display a simple message box as an alarm
    MessageBox(NULL, "Time's up!", "Alarm", MB_OK);
}

int main() {
    int seconds;

    // Ask the user for the alarm time (in seconds)
    printf("Enter time for alarm (in seconds): ");
    scanf("%d", &seconds);

    // Sleep for the specified time
    Sleep(seconds * 1000);  // Convert seconds to milliseconds

    // Trigger the alarm
    trigger_alarm();

    return 0;
}
