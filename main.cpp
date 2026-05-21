#include <iostream> // cin, cout
#include <fstream>  // file read/write
#include <cstring>  // strcpy, strcmp, strlen
using namespace std;

const int MAX_TASKS = 100;            // Maximum number of tasks
const char FILE_NAME[] = "tasks.txt"; // File to save tasks

// A struct groups all the info about one task together
struct Task
{
    int id;            // Task number (1, 2, 3...)
    char title[100];   // Task description
    char priority[10]; // "High", "Medium", "Low"
    char category[20]; // "Study", "Work", "Personal"
    int completed;     // 0 = not done, 1 = done
};

Task tasks[MAX_TASKS]; // Array of tasks
int taskCount = 0;     // How many tasks we have right now
int nextId = 1;        // Next available ID

// Displays the main menu options
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

// Prints a divider line
void printLine()
{
    cout << "  --------------------------------\n";
}

// Asks user for task details and adds to array
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
    cin.ignore();
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
    tasks[taskCount].completed = 0;

    // Move to next slot in array
    taskCount++;
    nextId++;

    cout << "\n  [+] Task added successfully!\n";
}

// Prints one task
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

// Shows every task in the array
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

// Shows only tasks that are not done yet
void viewPendingTasks()
{
    cout << "\n  --- PENDING TASKS ---\n";
    printLine();

    int count = 0;

    for (int i = 0; i < taskCount; i++)
    {
        // Only show if not completed
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

// Shows only completed tasks
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

// Finds a task by ID and marks it as completed
void markDone()
{
    if (taskCount == 0)
    {
        cout << "\n  [!] No tasks to mark. Add some first!\n";
        return;
    }

    viewAllTasks();

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
            return;
        }
    }

    cout << "\n  [!] Task with ID " << id << " not found.\n";
}

// Removes a task from the array by shifting elements
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
    int position = -1;
    for (int i = 0; i < taskCount; i++)
    {
        if (tasks[i].id == id)
        {
            position = i;
            break;
        }
    }

    if (position == -1)
    {
        cout << "\n  [!] Task with ID " << id << " not found.\n";
        return;
    }

    // Shift all tasks after this one one position left
    for (int i = position; i < taskCount - 1; i++)
    {
        tasks[i] = tasks[i + 1];
    }

    taskCount--;
    cout << "\n  [-] Task #" << id << " deleted.\n";
}

// Writes all tasks to tasks.txt
void saveToFile()
{
    ofstream file(FILE_NAME);

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

    file.close();
}

// Reads tasks from tasks.txt when the program starts
void loadFromFile()
{
    ifstream file(FILE_NAME);

    if (!file)
    {
        return;
    }

    // Read nextId and taskCount from first two lines
    file >> nextId;
    file >> taskCount;
    file.ignore();

    // Read each task line by line
    for (int i = 0; i < taskCount; i++)
    {
        char line[200];
        file.getline(line, 200);

        // Parse the line by splitting on '|'
        int len = strlen(line);
        int field = 0;
        char buffer[100];
        int bufIdx = 0;

        for (int j = 0; j <= len; j++)
        {
            // When we hit '|' or end of string, save the current field
            if (line[j] == '|' || line[j] == '\0')
            {
                buffer[bufIdx] = '\0';

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
                bufIdx = 0;
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

// The program starts here and shows the menu in a loop
int main()
{
    cout << "\n  Welcome to Simple To-Do List!\n";
    cout << "  Salim Habib University - PF Final Project\n";

    // Load any previously saved tasks
    loadFromFile();

    int choice;

    // Keep showing the menu until user chooses 0
    do
    {
        showMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
            addTask();
            saveToFile();
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

    } while (choice != 0);

    return 0;
}
