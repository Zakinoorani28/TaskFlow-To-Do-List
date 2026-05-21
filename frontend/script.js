// Data
// Load tasks from browser storage (like C++ loads from file)
let tasks = JSON.parse(localStorage.getItem("pf-tasks") || "[]");
let nextId = parseInt(localStorage.getItem("pf-nextid") || "1", 10);
let filter = "all";

// Save
// Like saveTasks() in C++, persist to storage
function save() {
  localStorage.setItem("pf-tasks", JSON.stringify(tasks));
  localStorage.setItem("pf-nextid", nextId);
}

// Add task
// Mirrors addTask() UDF in C++
function addTask() {
  const titleInput = document.getElementById("title");
  const title = titleInput.value.trim();

  if (!title) {
    titleInput.focus();
    return;
  }

  // Create a task object (like filling a C++ struct)
  const task = {
    id: nextId++,
    title,
    priority: document.getElementById("priority").value,
    category: document.getElementById("category").value,
    completed: false,
  };

  tasks.push(task);
  save();
  render();

  titleInput.value = "";
  titleInput.focus();
}

// Toggle done
// Mirrors markDone() UDF in C++
function toggleDone(id) {
  // Find the matching task by ID
  for (let i = 0; i < tasks.length; i++) {
    if (tasks[i].id === id) {
      tasks[i].completed = !tasks[i].completed;
      break;
    }
  }

  save();
  render();
}

// Delete task
// Mirrors deleteTask() UDF in C++
function deleteTask(id) {
  tasks = tasks.filter((t) => t.id !== id);
  save();
  render();
}

// Filter
function setFilter(nextFilter, btn) {
  filter = nextFilter;
  document.querySelectorAll(".f-btn").forEach((b) => b.classList.remove("on"));
  btn.classList.add("on");
  render();
}

// Render
// Builds the task list on screen, like viewAllTasks() in C++
function render() {
  // Priority to border color map
  const priColor = { High: "#fca5a5", Medium: "#fde68a", Low: "#6ee7b7" };

  // Filter tasks based on current tab
  const visible = tasks.filter((t) => {
    if (filter === "pending") return !t.completed;
    if (filter === "done") return t.completed;
    if (filter === "Study" || filter === "Work" || filter === "Personal") {
      return t.category === filter;
    }
    return true;
  });

  const list = document.getElementById("list");
  const empty = document.getElementById("empty");

  // Show empty state if nothing to display
  if (visible.length === 0) {
    list.innerHTML = "";
    empty.classList.add("show");
  } else {
    empty.classList.remove("show");

    list.innerHTML = visible
      .map(
        (t) => `
      <div class="card ${t.completed ? "done" : ""}"
           style="--pc: ${priColor[t.priority] || "#818cf8"}">
        <div class="chk" onclick="toggleDone(${t.id})">
          ${t.completed ? "&#10003;" : ""}
        </div>
        <div class="card-body">
          <div class="card-title">${esc(t.title)}</div>
          <div class="card-meta">
            <span class="badge p-${t.priority}">${t.priority}</span>
            <span class="badge c-${t.category}">${t.category}</span>
          </div>
        </div>
        <button class="del-btn" onclick="deleteTask(${t.id})" title="Delete">&#10005;</button>
      </div>
    `,
      )
      .join("");
  }

  // Update stats
  const done = tasks.filter((t) => t.completed).length;
  document.getElementById("s-total").textContent = tasks.length;
  document.getElementById("s-done").textContent = done;
  document.getElementById("s-left").textContent = tasks.length - done;
}

// Utility
// Escape HTML for safety
function esc(str) {
  return str
    .replace(/&/g, "&amp;")
    .replace(/</g, "&lt;")
    .replace(/>/g, "&gt;");
}

document.getElementById("title").addEventListener("keydown", (e) => {
  if (e.key === "Enter") {
    addTask();
  }
});

render();
