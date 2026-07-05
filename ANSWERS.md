# Homework 2 Answers

### 1. Why shared_ptr and not unique_ptr?
* **Why shared_ptr:** Multiple parts of the program need to look at and use the same robot at the same time (the Fleet list, the Task queue, and the background thread).
* **What breaks:** A `unique_ptr` allows only one owner. If you switch, you cannot safely share a robot across different lists or hand it over to a background thread without destroying it elsewhere.

### 2. The robots_ container
* **Container Used:** `std::unordered_map`.
* **Why & Lookup Cost:** It maps a Robot's ID string directly to the robot object, making it easy to find a robot instantly. For `std::unordered_map`, searching takes Constant time ($O(1)$) on average.

### 3. The Task Queue container
* **Container Used:** `std::priority_queue`
* **Data Structure & Fit:** It is built on a **Max-Heap** structure. It is the perfect fit because every time you push a task into it, it automatically bubbles the task with the highest priority number to the very top. Getting the most urgent task is always instant.

### 4. What does friend do for operator<<?
* **What friend does:** It allows an outside function to peek inside a class and read its `private` variables (like name or battery) without needing public getter functions.
* **Why it cannot be a regular method:** When you type `std::cout << robot`, `std::cout` is on the left side. Regular class methods only work if the object itself is on the left side (like `robot << std::cout`, which looks wrong and doesn't compile).

### 5. Why use std::find_if instead of a loop?
* **Why it's better:** It tells anyone reading your code exactly what your goal is ("find a specific item") rather than how to do it step-by-step. It makes the code cleaner, shorter, and less prone to typing mistakes.

### 6. Why use exceptions instead of returning false?
* **Why exceptions:** A dead battery is a critical error. If a function just returns `false` or prints a message, the program can easily ignore it and keep trying to run a dead robot. An exception forces the program to stop and handle the crash immediately.

### 7. Is the fleet state consistent after an exception?
* **Yes:** The exception is thrown at the very beginning of the function before any task is actually added to the queue. Because nothing was modified yet, the fleet data remains perfectly safe and unchanged.

### 8. What happens to stop_ and worker_?
* **What I did:** `stop_` is an atomic flag that tells the background loop when to pack up and stop running. `worker_` is the actual thread handle. We join the thread to make sure it shuts down cleanly when the robot is deleted, preventing background crashes.

### 9. The Diamond Problem
* **Why it fails:** `MobileRobot` and `CookingRobot` both get their own separate copy of `Robot` when they inherit it. When `MaintenanceRobot` combines them both, it ends up with two separate copies of `name_`. The compiler gets confused because it doesn't know which `name_` you want to print.
* **The Solution:** Use the `virtual` keyword when inheriting. It tells C++ to share a single copy of the base `Robot` class among all grandchildren.

#### Corrected Code:
```cpp
class Robot { 
public: 
    std::string name_ = "base"; 
};

// Adding "virtual" fixes the double-copy issue
class MobileRobot      : virtual public Robot {};
class CookingRobot     : virtual public Robot {};
class MaintenanceRobot : public MobileRobot, public CookingRobot {};

int main() {
    MaintenanceRobot m;
    std::cout << m.name_; // Works perfectly! Prints "base"
}
```