# Robot Fleet Manager

An object-oriented C++ application designed to manage a diverse fleet of autonomous engineering assets (Mobile, Cleaning, and Cooking robots). The system handles real-time task allocation using a priority-driven scheduler, tracks telemetry data (such as battery and status), and utilizes advanced paradigms like multi-threaded background workers, and smart pointers.

## Features & System Capabilities
* **Polymorphic Architecture:** Leverages a base `Robot` template to derive specific subsystems (`MobileRobot`, `CleaningRobot`, `CookingRobot`) with specialized class methods.
* **Priority Task Scheduling:** Manages task assignments using a `std::priority_queue` to ensure high-priority directives are prioritized automatically.
* **Encapsulated Memory Management:** Utilizes modern `std::shared_ptr` mechanics to eliminate manual memory leaks or standard pointer tracking complications.
* **Advanced Filtering:** Integrates `std::find_if` directly over map collections to trace active fleet units experiencing low-battery states.

---

## How to Compile and Run

This workspace includes an automated compilation shell control script configuring strict compiler feedback flags (`-Wall -Wextra`) to guarantee a production-ready, zero-warning environment.

### Prerequisites
Ensure you have a modern GCC compiler toolchain installed on your environment (supporting C++17 or greater).

### 1. Compilation
Execute the automated build control script from your root directory terminal:
```bash
./compile.sh
```

### 2. Execution

Run the compiled application binary:
Bash
```bash
./fleet_app
```