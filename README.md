# Personal Health Tracker

This project is a Personal Health Tracker application written in C that helps users track their daily health metrics, set goals, monitor progress, and get reminders for their health-related activities. It includes functionalities such as adding daily health records, setting and checking health goals, displaying health metrics in a graphical format, and showing reminders as system notifications.

## Features

- **Add Daily Health Record**: Users can add health records such as water intake, exercise duration, sleep hours, and weight for a specific date.
- **Display All Records**: View all health records in a tabular format.
- **Set Health Goals**: Set daily health goals for water intake, exercise, and sleep.
- **Check Progress**: Compare the user's health data against set goals.
- **Delete a Record**: Delete a health record by entering the date.
- **Save Records to File**: Save the health records to a text file for future reference.
- **Show Reminders**: Display a list of all reminders.
- **Add Reminder**: Add a custom reminder message to be shown to the user.
- **Delete Reminder**: Delete the most recent reminder.
- **Display Graph for Health Metric**: View graphs for metrics such as water intake, exercise, sleep, or weight.
- **Undo Last Operation**: Undo the last health record addition or deletion.
- **Set Alarm**: Set a timer to trigger an alarm (beep sound) after a specified number of seconds.
- **Show Reminder Notification**: Display a system tray notification with a reminder message.

## Requirements

- C compiler (e.g., GCC, MinGW)
- Windows OS (for system tray notifications and `Beep` functionality)
- Standard C libraries (stdio.h, stdlib.h, string.h, time.h, windows.h, shellapi.h)

## Installation

1. Clone or download the repository.
2. Compile the program using your preferred C compiler. For example, using GCC:
    ```bash
    gcc -o health_tracker health_tracker.c
    ```
3. Run the compiled executable:
    ```bash
    ./health_tracker
    ```

## Usage

### Main Menu Options

Once the program is executed, you will see the following main menu options:

1. **Add Daily Health Record**: Add a new health record for a specific date.
2. **Display All Records**: View all stored health records.
3. **Set Health Goals**: Set daily health goals for water intake, exercise, and sleep.
4. **Check Progress**: Check how your daily records compare to the set goals.
5. **Delete a Record**: Delete a health record by specifying the date.
6. **Save Records to File**: Save the health records to a text file.
7. **Show Reminders**: Display all reminders.
8. **Add Reminder**: Add a new reminder message.
9. **Delete Reminder**: Delete the most recent reminder.
10. **Display Graph for Health Metric**: View graphs for health metrics such as water intake, exercise, sleep, or weight.
11. **Undo Last Operation**: Undo the most recent record addition or deletion.
12. **Set Alarm**: Set an alarm that triggers a beep and message box after a specified duration.
13. **Show Reminder Notification**: Display a reminder notification in the system tray.
14. **Exit**: Exit the application.

### Graphing Health Metrics

The program allows you to graph health metrics such as water intake, exercise minutes, sleep hours, or weight. Choose the metric from the following options:
- Water intake
- Exercise duration
- Sleep hours
- Weight

The data will be displayed in a tree format sorted by date.

### Reminder System

You can set reminders that show up as system tray notifications or pop-up message boxes after a specific time delay. Additionally, you can delete or view all existing reminders.

### Alarm System

An alarm (beep sound and message box) can be triggered after a certain amount of time (in seconds). The alarm will beep for 10 seconds.

## Code Structure

The project consists of the following main components:

1. **HealthData Structure**: Represents a health record with fields such as date, water intake, exercise minutes, sleep hours, and weight.
2. **Reminder Structure**: Used for managing reminders in a queue format.
3. **GraphNode Structure**: Represents the graph nodes used to display health metrics.
4. **Undo Stack**: A stack to store previous health data records for undo functionality.
5. **Functions**:
   - **addRecord**: Adds a new health record to the linked list.
   - **displayRecords**: Displays all stored health records.
   - **setGoal**: Sets the user's health goals.
   - **checkProgress**: Checks progress based on health records and goals.
   - **saveRecordsToFile**: Saves records to a file.
   - **loadRecordsFromFile**: Loads records from a file.
   - **addReminder**: Adds a reminder message.
   - **deleteReminder**: Deletes the most recent reminder.
   - **trigger_alarm**: Triggers an alarm (beep and message box).
   - **show_notification**: Shows a system tray notification with a reminder message.
   - **insertGraphNode**: Inserts a new node into the graph tree.
   - **displayGraph**: Displays the graph of health data.
   - **createGraphFromHealthData**: Creates a graph from health data based on the selected metric.

## Example Output

```bash
Personal Health Tracker
1. Add Daily Health Record
2. Display All Records
3. Set Health Goals
4. Check Progress
5. Delete a Record
6. Save Records to File
7. Show Reminders
8. Add Reminder
9. Delete Reminder
10. Display Graph for Health Metric
11. Undo Last Operation
12. Set Alarm
13. Show Reminder Notification
14. Exit
Enter your choice: 1
Enter date (dd-mm-yyyy): 25-09-2025
Enter water intake (in liters): 2.5
Enter exercise duration (in minutes): 45
Enter sleep duration (in hours): 7.5
Enter weight (in kg): 70.0
Record added successfully!
