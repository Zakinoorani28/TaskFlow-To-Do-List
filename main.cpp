// =====================================================
//   Simple To-Do List
//   Programming Fundamentals - Final Project
//   Salim Habib University
// =====================================================

#include <iostream> // cin, cout
#include <fstream>  // file read/write
#include <cstring>  // strcpy, strcmp, strlen
using namespace std;

// ─── CONSTANTS ──────────────────────────────────────
const int MAX_TASKS = 100;            // Maximum number of tasks
const char FILE_NAME[] = "tasks.txt"; // File to save tasks

// ─── STRUCTURE ──────────────────────────────────────
// A struct groups all the info about ONE task together
struct Task
{
    int id;            // Task number (1, 2, 3...)
    char title[100];   // Task description
    char priority[10]; // "High", "Medium", "Low"
    char category[20]; // "Study", "Work", "Personal"
    int completed;     // 0 = not done, 1 = done
};

// ─── GLOBAL VARIABLES ───────────────────────────────
Task tasks[MAX_TASKS]; // Array of tasks
int taskCount = 0;     // How many tasks we have right now
int nextId = 1;        // Next available ID

// =====================================================
//   UDF: showMenu
//   Displays the main menu options
// =====================================================
void showMenu()
{
    cout << "\n";
    cout << "  ================================\n";
    cout << "        SIMPLE TO-DO LIST         \n";
    cout << "  ================================\n";
    cout << "  1. Add a new task               \n";
    cout << "  2. View all tasks               \n";
    cout << "  3. Mark task as done            \n";
    cout << "  4. Delete a task                \n";
    cout << "  5. View only pending tasks      \n";
    cout << "  6. View completed tasks         \n";
    cout << "  0. Exit                         \n";
    cout << "  ================================\n";
    cout << "  Your choice: ";
}

// =====================================================
//   UDF: printLine
//   Prints a divider line (reusable helper)
// =====================================================
void printLine()
{
    cout << "  --------------------------------\n";
}

// =====================================================
//   UDF: addTask
//   Asks user for task details and adds to array
// =====================================================
void addTask()
{
    // Check if array is full
    if (taskCount >= MAX_TASKS)
    {
        cout << "\n  [!] Task list is full!\n";
        return;
    }

    cout << "\n  --- ADD NEW TASK ---\n";

    // Get task title from user
    cout << "  Task title : ";
    cin.ignore(); // Clear leftover newline from cin
    cin.getline(tasks[taskCount].title, 100);

    // Get priority
    int priChoice;
    cout << "  Priority   :\n";
    cout << "    1. High\n";
    cout << "    2. Medium\n";
    cout << "    3. Low\n";
    cout << "  Choose (1/2/3): ";
    cin >> priChoice;

    // Set priority string based on choice
    if (priChoice == 1)
        strcpy(tasks[taskCount].priority, "High");
    else if (priChoice == 3)
        strcpy(tasks[taskCount].priority, "Low");
    else
        strcpy(tasks[taskCount].priority, "Medium");

    // Get category
    int catChoice;
    cout << "  Category   :\n";
    cout << "    1. Study\n";
    cout << "    2. Work\n";
    cout << "    3. Personal\n";
    cout << "  Choose (1/2/3): ";
    cin >> catChoice;

    if (catChoice == 1)
        strcpy(tasks[taskCount].category, "Study");
    else if (catChoice == 2)
        strcpy(tasks[taskCount].category, "Work");
    else
        strcpy(tasks[taskCount].category, "Personal");

    // Set the rest of the fields
    tasks[taskCount].id = nextId;
    tasks[taskCount].completed = 0; // New task = not done

    // Move to next slot in array
    taskCount++;
    nextId++;

    cout << "\n  [+] Task added successfully!\n";
}

// =====================================================
//   UDF: displayOneTask
//   Prints a single task's details nicely
// =====================================================
void displayOneTask(int index)
{
    // Pick a symbol based on completion
    char status[10];
    if (tasks[index].completed == 1)
        strcpy(status, "[DONE]");
    else
        strcpy(status, "[    ]");

    cout << "  " << status << " #" << tasks[index].id
         << " - " << tasks[index].title << "\n";
    cout << "        Priority : " << tasks[index].priority
         << "   |   Category: " << tasks[index].category << "\n";
}

// =====================================================
//   UDF: viewAllTasks
//   Shows every task in the array
// =====================================================
void viewAllTasks()
{
    cout << "\n  --- ALL TASKS ---\n";
    printLine();

    // If no tasks yet
    if (taskCount == 0)
    {
        cout << "  No tasks found. Add one first!\n";
        return;
    }

    // Loop through each task and display it
    for (int i = 0; i < taskCount; i++)
    {
        displayOneTask(i);
        printLine();
    }

    cout << "  Total: " << taskCount << " task(s)\n";
}

// =====================================================
//   UDF: viewPendingTasks
//   Shows only tasks that are NOT done yet
// =====================================================
void viewPendingTasks()
{
    cout << "\n  --- PENDING TASKS ---\n";
    printLine();

    int count = 0; // Count how many pending tasks we find

    for (int i = 0; i < taskCount; i++)
    {
        // Only show if NOT completed
        if (tasks[i].completed == 0)
        {
            displayOneTask(i);
            printLine();
            count++;
        }
    }

    if (count == 0)
        cout << "  No pending tasks! All done!\n";
    else
        cout << "  Pending: " << count << " task(s)\n";
}

// =====================================================
//   UDF: viewCompletedTasks
//   Shows only tasks that ARE done
// =====================================================
void viewCompletedTasks()
{
    cout << "\n  --- COMPLETED TASKS ---\n";
    printLine();

    int count = 0;

    for (int i = 0; i < taskCount; i++)
    {
        if (tasks[i].completed == 1)
        {
            displayOneTask(i);
            printLine();
            count++;
        }
    }

    if (count == 0)
        cout << "  No completed tasks yet.\n";
    else
        cout << "  Completed: " << count << " task(s)\n";
}

// =====================================================
//   UDF: markDone
//   Finds a task by ID and marks it as completed
// =====================================================
void markDone()
{
    if (taskCount == 0)
    {
        cout << "\n  [!] No tasks to mark. Add some first!\n";
        return;
    }

    viewAllTasks(); // Show tasks so user can pick one

    int id;
    cout << "\n  Enter task ID to mark as done: ";
    cin >> id;

    // Search for the task with matching ID
    for (int i = 0; i < taskCount; i++)
    {
        if (tasks[i].id == id)
        {
            if (tasks[i].completed == 1)
            {
                cout << "\n  [!] Task is already marked as done!\n";
            }
            else
            {
                tasks[i].completed = 1;
                cout << "\n  [+] Task #" << id << " marked as done!\n";
            }
            return; // Stop searching once found
        }
    }

    // If we get here, ID was not found
    cout << "\n  [!] Task with ID " << id << " not found.\n";
}

// =====================================================
//   UDF: deleteTask
//   Removes a task from the array by shifting elements
// =====================================================
void deleteTask()
{
    if (taskCount == 0)
    {
        cout << "\n  [!] No tasks to delete.\n";
        return;
    }

    viewAllTasks();

    int id;
    cout << "\n  Enter task ID to delete: ";
    cin >> id;

    // Find the task position
    int position = -1; // -1 means not found yet
    for (int i = 0; i < taskCount; i++)
    {
        if (tasks[i].id == id)
        {
            position = i;
            break; // Stop loop once found
        }
    }

    if (position == -1)
    {
        cout << "\n  [!] Task with ID " << id << " not found.\n";
        return;
    }

    // Shift all tasks after this one, one position left
    // This "fills the gap" left by the deleted task
    for (int i = position; i < taskCount - 1; i++)
    {
        tasks[i] = tasks[i + 1];
    }

    taskCount--; // One fewer task now
    cout << "\n  [-] Task #" << id << " deleted.\n";
}

// =====================================================
//   UDF: saveToFile
//   Writes all tasks to tasks.txt
//   Format: id,title,priority,category,completed
// =====================================================
void saveToFile()
{
    ofstream file(FILE_NAME); // Open file for writing

    if (!file)
    {
        cout << "\n  [!] Error: Could not open file to save.\n";
        return;
    }

    // Write nextId on first line
    file << nextId << "\n";
    file << taskCount << "\n";

    // Write each task as one line, fields separated by |
    for (int i = 0; i < taskCount; i++)
    {
        file << tasks[i].id << "|"
             << tasks[i].title << "|"
             << tasks[i].priority << "|"
             << tasks[i].category << "|"
             << tasks[i].completed << "\n";
    }

    file.close(); // Always close the file!
}

// =====================================================
//   UDF: loadFromFile
//   Reads tasks from tasks.txt when program starts
// =====================================================
void loadFromFile()
{
    ifstream file(FILE_NAME); // Open file for reading

    if (!file)
    {
        // File doesn't exist yet — that's okay!
        return;
    }

    // Read nextId and taskCount from first two lines
    file >> nextId;
    file >> taskCount;
    file.ignore(); // Skip the newline after taskCount

    // Read each task line by line
    for (int i = 0; i < taskCount; i++)
    {
        char line[200];
        file.getline(line, 200); // Read full line

        // Parse the line: split by '|' manually
        // We use a position pointer to walk through the string
        int len = strlen(line);
        int field = 0; // Which field we're filling (0=id, 1=title...)
        char buffer[100];
        int bufIdx = 0;

        for (int j = 0; j <= len; j++)
        {
            // When we hit '|' or end of string, save the buffer to a field
            if (line[j] == '|' || line[j] == '\0')
            {
                buffer[bufIdx] = '\0'; // Null-terminate our buffer

                if (field == 0)
                    tasks[i].id = atoi(buffer);
                if (field == 1)
                    strcpy(tasks[i].title, buffer);
                if (field == 2)
                    strcpy(tasks[i].priority, buffer);
                if (field == 3)
                    strcpy(tasks[i].category, buffer);
                if (field == 4)
                    tasks[i].completed = atoi(buffer);

                field++;
                bufIdx = 0; // Reset buffer for next field
            }
            else
            {
                buffer[bufIdx++] = line[j];
            }
        }
    }

    file.close();

    if (taskCount > 0)
        cout << "  [+] Loaded " << taskCount << " saved task(s).\n";
}

// =====================================================
//   MAIN FUNCTION
//   The program starts here. Shows menu in a loop.
// =====================================================
int main()
{
    cout << "\n  Welcome to Simple To-Do List!\n";
    cout << "  Salim Habib University — PF Final Project\n";

    // Load any previously saved tasks
    loadFromFile();

    int choice;

    // Keep showing the menu until user chooses 0 (exit)
    do
    {
        showMenu();
        cin >> choice;

        // Use switch to call the right function
        switch (choice)
        {
        case 1:
            addTask();
            saveToFile(); // Save after every change
            break;

        case 2:
            viewAllTasks();
            break;

        case 3:
            markDone();
            saveToFile();
            break;

        case 4:
            deleteTask();
            saveToFile();
            break;

        case 5:
            viewPendingTasks();
            break;

        case 6:
            viewCompletedTasks();
            break;

        case 0:
            cout << "\n  Goodbye! Tasks saved.\n\n";
            break;

        default:
            cout << "\n  [!] Invalid choice. Enter 0-6.\n";
        }

    } while (choice != 0); // Loop until user exits

    return 0;
}
