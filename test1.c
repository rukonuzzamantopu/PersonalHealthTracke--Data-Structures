#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <shellapi.h>

// Health Data structure using linked list
typedef struct HealthData {
    char date[20];
    float waterIntake;
    int exerciseMinutes;
    float sleepHours;
    float weight;
    struct HealthData* next;
} HealthData;

// Reminder structure using a queue
typedef struct Reminder {
    char message[256];
    struct Reminder* next;
} Reminder;

// Graph Node structure for displaying health metrics in graph form
typedef struct GraphNode {
    char date[20];
    float dataValue; // This can represent water intake, exercise minutes, etc.
    struct GraphNode* left;
    struct GraphNode* right;
} GraphNode;

// Stack for undo operations
#define MAX_STACK_SIZE 100
HealthData* undoStack[MAX_STACK_SIZE];
int top = -1;

// Function Prototypes
HealthData* addRecord(HealthData* head);
void displayRecords(HealthData* head);
void setGoal(float* waterGoal, int* exerciseGoal, float* sleepGoal);
void checkProgress(HealthData* head, float waterGoal, int exerciseGoal, float sleepGoal);
void saveRecordsToFile(HealthData* head);
HealthData* loadRecordsFromFile();
void deleteRecord(HealthData** head, const char* date);
void addReminderWithNotification(Reminder** front, Reminder** rear);
void show_notification(const char* message);
GraphNode* insertGraphNode(GraphNode* root, const char* date, float dataValue);
void displayGraph(GraphNode* root);
GraphNode* createGraphFromHealthData(HealthData* head, const char* metric);
void pushUndoStack(HealthData* head);
HealthData* popUndoStack();
void trigger_alarm();

int main() {
    HealthData* head = loadRecordsFromFile();
    Reminder* reminderFront = NULL;
    Reminder* reminderRear = NULL;

    int choice;
    float waterGoal = 2.0; // Default daily goal for water intake in liters
    int exerciseGoal = 30; // Default daily goal for exercise in minutes
    float sleepGoal = 8.0; // Default daily goal for sleep in hours

    do {
        printf("\nPersonal Health Tracker\n");
        printf("1. Add Daily Health Record\n");
        printf("2. Display All Records\n");
        printf("3. Set Health Goals\n");
        printf("4. Check Progress\n");
        printf("5. Delete a Record\n");
        printf("6. Save Records to File\n");
        printf("7. Add Reminder\n");
        printf("8. Display Graph for Health Metric\n");
        printf("9. Undo Last Operation\n");
        printf("10. Set Alarm\n");
        printf("11. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character

        switch (choice) {
            case 1:
                pushUndoStack(head);
                head = addRecord(head);
                break;
            case 2:
                displayRecords(head);
                break;
            case 3:
                setGoal(&waterGoal, &exerciseGoal, &sleepGoal);
                break;
            case 4:
                checkProgress(head, waterGoal, exerciseGoal, sleepGoal);
                break;
            case 5: {
                pushUndoStack(head);
                char date[20];
                printf("Enter the date of the record to delete (dd-mm-yyyy): ");
                fgets(date, 20, stdin);
                date[strcspn(date, "\n")] = 0; // Remove newline character
                deleteRecord(&head, date);
                break;
            }
            case 6:
                saveRecordsToFile(head);
                break;
            case 7:
                Reminder* reminderFront = NULL;
                Reminder* reminderRear = NULL;

                // Call the function to add a reminder and show the notification
                addReminderWithNotification(&reminderFront, &reminderRear);

                break;                
            case 8: {
                char metric[20];
                printf("Enter the health metric to graph (options: water, exercise, sleep, weight): ");
                fgets(metric, 20, stdin);
                metric[strcspn(metric, "\n")] = 0; // Remove newline character
                GraphNode* graphRoot = createGraphFromHealthData(head, metric);
                if (graphRoot) {
                    displayGraph(graphRoot);
                } else {
                    printf("Invalid metric or no data available for graphing.\n");
                }
                break;
            }
            case 9:
                head = popUndoStack();
                if (head != NULL) {
                    printf("Last operation undone successfully!\n");
                }
                break;
            case 10: {
                int seconds;
                printf("Enter time for alarm (in seconds): ");
                scanf("%d", &seconds);
                Sleep(seconds * 1000);  // Wait for the specified time
                trigger_alarm(); // Trigger alarm after sleep
                break;
            }
            case 11:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 14);

    return 0;
}

// Function to add a new health record
HealthData* addRecord(HealthData* head) {
    HealthData* newRecord = (HealthData*)malloc(sizeof(HealthData));
    if (newRecord == NULL) {
        printf("Memory allocation failed.\n");
        return head;
    }

    printf("Enter date (dd-mm-yyyy): ");
    fgets(newRecord->date, 20, stdin);
    newRecord->date[strcspn(newRecord->date, "\n")] = 0; // Remove newline character

    printf("Enter water intake (in liters): ");
    scanf("%f", &newRecord->waterIntake);
    printf("Enter exercise duration (in minutes): ");
    scanf("%d", &newRecord->exerciseMinutes);
    printf("Enter sleep duration (in hours): ");
    scanf("%f", &newRecord->sleepHours);
    printf("Enter weight (in kg): ");
    scanf("%f", &newRecord->weight);
    getchar(); // Consume newline character

    newRecord->next = head;
    head = newRecord;

    printf("Record added successfully!\n");
    return head;
}

// Function to display all health records
void displayRecords(HealthData* head) {
    if (head == NULL) {
        printf("No records to display.\n");
        return;
    }
    HealthData* temp = head;
    while (temp != NULL) {
        printf("Date: %s, Water Intake: %.2f L, Exercise: %d min, Sleep: %.2f hrs, Weight: %.2f kg\n", 
                temp->date, temp->waterIntake, temp->exerciseMinutes, temp->sleepHours, temp->weight);
        temp = temp->next;
    }
}

// Function to set health goals
void setGoal(float* waterGoal, int* exerciseGoal, float* sleepGoal) {
    printf("Enter daily water intake goal (in liters): ");
    scanf("%f", waterGoal);
    printf("Enter daily exercise goal (in minutes): ");
    scanf("%d", exerciseGoal);
    printf("Enter daily sleep goal (in hours): ");
    scanf("%f", sleepGoal);
    getchar(); // Consume newline character
    printf("Goals updated successfully!\n");
}

// Function to check progress against goals
void checkProgress(HealthData* head, float waterGoal, int exerciseGoal, float sleepGoal) {
    if (head == NULL) {
        printf("No records to check progress.\n");
        return;
    }
    HealthData* temp = head;
    while (temp != NULL) {
        printf("\nDate: %s\n", temp->date);
        printf("Water Intake: %.2f L (%s)\n", temp->waterIntake, temp->waterIntake >= waterGoal ? "Goal Met" : "Goal Not Met");
        printf("Exercise: %d min (%s)\n", temp->exerciseMinutes, temp->exerciseMinutes >= exerciseGoal ? "Goal Met" : "Goal Not Met");
        printf("Sleep: %.2f hrs (%s)\n", temp->sleepHours, temp->sleepHours >= sleepGoal ? "Goal Met" : "Goal Not Met");
        temp = temp->next;
    }
}

// Function to save records to file
void saveRecordsToFile(HealthData* head) {
    FILE* file = fopen("health_records.txt", "w");
    if (file == NULL) {
        printf("Error opening file for saving.\n");
        return;
    }
    HealthData* temp = head;
    while (temp != NULL) {
        fprintf(file, "%s %.2f %d %.2f %.2f\n", temp->date, temp->waterIntake, temp->exerciseMinutes, temp->sleepHours, temp->weight);
        temp = temp->next;
    }
    fclose(file);
    printf("Records saved successfully!\n");
}

// Function to load records from file
HealthData* loadRecordsFromFile() {
    FILE* file = fopen("health_records.txt", "r");
    if (file == NULL) {
        printf("No existing records found. Starting fresh.\n");
        return NULL;
    }
    HealthData* head = NULL;
    HealthData* temp = NULL;
    while (!feof(file)) {
        HealthData* newRecord = (HealthData*)malloc(sizeof(HealthData));
        if (fscanf(file, "%s %f %d %f %f", newRecord->date, &newRecord->waterIntake, &newRecord->exerciseMinutes, &newRecord->sleepHours, &newRecord->weight) == 5) {
            newRecord->next = NULL;
            if (head == NULL) {
                head = newRecord;
                temp = newRecord;
            } else {
                temp->next = newRecord;
                temp = newRecord;
            }
        } else {
            free(newRecord);
        }
    }
    fclose(file);
    return head;
}

// Function to delete a record
void deleteRecord(HealthData** head, const char* date) {
    HealthData* temp = *head;
    HealthData* prev = NULL;
    while (temp != NULL && strcmp(temp->date, date) != 0) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Record not found.\n");
        return;
    }
    if (prev == NULL) {
        *head = temp->next;
    } else {
        prev->next = temp->next;
    }
    free(temp);
    printf("Record deleted successfully!\n");
}

// Function to add a reminder
void addReminderWithNotification(Reminder** front, Reminder** rear) {
    char message[256];
    int duration;
    NOTIFYICONDATA nid;

    // Prompt user for notification message
    printf("Enter your notification message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = 0;  // Remove newline character

    // Prompt user for duration in seconds
    printf("Enter the duration in seconds: ");
    while (scanf("%d", &duration) != 1 || duration < 1) {
        printf("Invalid input. Please enter a positive number: ");
        while (getchar() != '\n'); // Clear the input buffer
    }
    getchar(); // Consume any leftover newline character

    // Add the reminder to the linked list
    Reminder* newReminder = (Reminder*)malloc(sizeof(Reminder));
    if (newReminder == NULL) {
        printf("Memory allocation failed for reminder.\n");
        return;
    }
    strcpy(newReminder->message, message);
    newReminder->next = NULL;
    if (*rear == NULL) {
        *front = *rear = newReminder;
    } else {
        (*rear)->next = newReminder;
        *rear = newReminder;
    }
    printf("Reminder added successfully!\n");

    // Initialize NOTIFYICONDATA structure
    ZeroMemory(&nid, sizeof(nid));
    nid.cbSize = sizeof(nid);
    nid.uID = 1;
    nid.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
    nid.hWnd = NULL;
    nid.uCallbackMessage = WM_USER + 1;
    nid.hIcon = LoadIcon(NULL, IDI_INFORMATION);
    lstrcpy(nid.szTip, message);  // Set message as the tooltip

    // Wait for the user-specified duration before showing the notification
    printf("Waiting for %d seconds before showing the message...\n", duration);
    Sleep(duration * 1000);  // Convert seconds to milliseconds

    // Add the notification icon to the system tray
    Shell_NotifyIcon(NIM_ADD, &nid);

    // Show the notification message in a MessageBox
    MessageBox(NULL, message, "Notification", MB_OK);

    // Wait for the same duration before removing the notification icon
    printf("Notification will disappear in %d seconds...\n", duration);
    Sleep(duration * 1000);  // Wait for the same duration before removing the icon

    // Remove the notification icon from the system tray
    Shell_NotifyIcon(NIM_DELETE, &nid);
}
// Function to show reminde
// Function to delete a reminder

// Function to trigger an alarm with a beep and message box
void trigger_alarm() {
    Beep(1000, 10000);  // Frequency 1000 Hz, duration 1000 ms
    MessageBox(NULL, "Time's up!", "Alarm", MB_OK);
}

// Function to show a system tray notification
void show_notification(const char* message) {
    NOTIFYICONDATA nid;
    ZeroMemory(&nid, sizeof(nid));
    nid.cbSize = sizeof(nid);
    nid.uID = 1;
    nid.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
    nid.hWnd = NULL;
    nid.uCallbackMessage = WM_USER + 1;
    nid.hIcon = LoadIcon(NULL, IDI_INFORMATION);
    lstrcpy(nid.szTip, "Health Tracker Notification");

    // Add the notification icon to the system tray
    Shell_NotifyIcon(NIM_ADD, &nid);

    // Show the notification
    MessageBox(NULL, message, "Reminder", MB_OK);

    // Remove the icon after use
    Shell_NotifyIcon(NIM_DELETE, &nid);
}
// Function to push the current head into the undo stack
void pushUndoStack(HealthData* head) {
    if (top >= MAX_STACK_SIZE - 1) {
        printf("Undo stack is full. Cannot save state.\n");
        return;
    }
    top++;
    undoStack[top] = head;
}

// Function to pop from the undo stack
HealthData* popUndoStack() {
    if (top < 0) {
        printf("No operations to undo.\n");
        return NULL;
    }
    return undoStack[top--];
}

// Function to insert a node into the graph tree
GraphNode* insertGraphNode(GraphNode* root, const char* date, float dataValue) {
    if (root == NULL) {
        GraphNode* newNode = (GraphNode*)malloc(sizeof(GraphNode));
        if (newNode == NULL) {
            printf("Memory allocation failed for graph node.\n");
            return NULL;
        }
        strcpy(newNode->date, date);
        newNode->dataValue = dataValue;
        newNode->left = newNode->right = NULL;
        return newNode;
    }
    if (strcmp(date, root->date) < 0) {
        root->left = insertGraphNode(root->left, date, dataValue);
    } else {
        root->right = insertGraphNode(root->right, date, dataValue);
    }
    return root;
}

// Function to display the graph tree (in-order traversal)
void displayGraph(GraphNode* root) {
    if (root == NULL) {
        return;
    }
    displayGraph(root->left);
    printf("Date: %s, Value: %.2f\n", root->date, root->dataValue);
    displayGraph(root->right);
}

// Function to create a graph tree from health data based on a selected metric
GraphNode* createGraphFromHealthData(HealthData* head, const char* metric) {
    GraphNode* root = NULL;
    HealthData* temp = head;

    while (temp != NULL) {
        float value = 0;
        if (strcmp(metric, "water") == 0) {
            value = temp->waterIntake;
        } else if (strcmp(metric, "exercise") == 0) {
            value = temp->exerciseMinutes;
        } else if (strcmp(metric, "sleep") == 0) {
            value = temp->sleepHours;
        } else if (strcmp(metric, "weight") == 0) {
            value = temp->weight;
        } else {
            return NULL; // Invalid metric
        }
        root = insertGraphNode(root, temp->date, value);
        temp = temp->next;
    }

    return root;
}
