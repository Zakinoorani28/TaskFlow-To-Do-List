# Simple To-Do List

## Programming Fundamentals — Final Project

### Salim Habib University

---

## How to Run the C++ Program

```bash
make          # compile
make run      # compile + run
```

Or manually:

```bash
g++ -std=c++17 -o simpletodo main.cpp
./simpletodo
```

## How to Open the UI

Just open `frontend/index.html` in any browser.  
No server needed — it runs directly in the browser.

---

## C++ Concepts Used (from our syllabus)

| Concept       | Where used in main.cpp                        |
| ------------- | --------------------------------------------- |
| `struct`      | `Task` struct — groups all task data together |
| `array`       | `Task tasks[100]` — stores all tasks          |
| `string/char` | `char title[100]`, `strcpy`, `strcmp`         |
| UDFs          | `addTask()`, `deleteTask()`, `markDone()` etc |
| `for` loop    | Searching and displaying tasks                |
| `if / else`   | Conditions for priority, status checks        |
| `switch`      | Menu selection                                |
| File I/O      | `saveToFile()` / `loadFromFile()`             |

---

## Files

```text
simpletodo/
├── main.cpp           ← C++ program (the main part)
├── Makefile           ← type "make" to compile
├── tasks.txt          ← auto-created when you save tasks
└── frontend/
    └── index.html     ← open in browser for the UI
```
