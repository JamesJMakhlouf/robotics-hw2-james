#include "fleet.hpp"
#include <stdexcept>
#include <iostream>

void Fleet::add(std::shared_ptr<Robot> robot) {
    if (!robot) return;
    robots_[robot->id()] = robot;
}

void Fleet::remove(const std::string& id) {
    robots_.erase(id);
}

std::shared_ptr<Robot> Fleet::find(const std::string& id) const {
    auto it = robots_.find(id);
    if (it != robots_.end()) return it->second;
    throw std::runtime_error("No robot with id: " + id);
}

// Stores the task in the priority queue and marks the robot as busy.
void Fleet::assign_task(const std::string& robot_id, const Task& t) {
    try {
        auto robot = find(robot_id);
        robot->set_status("busy");

        Task task = t;
        task.assigned_to = robot_id;
        tasks_.push(task);
    } catch(const std::runtime_error& e) {
        std::cout << "Error: " << e.what() << "\n";
    }
}

void Fleet::show_tasks()  const {
    if (tasks_.empty()) {
        std::cout << "No assigned tasks in the queue.\n";
        return;
    }

    auto temp_queue = tasks_;
    std::cout << "--- Fleet Task Queue ---\n";
    while (!temp_queue.empty()) {
        std::cout << temp_queue.top() << "\n";
        temp_queue.pop();
    }
}

void Fleet::work_all() const {
    for (const auto& [id, robot] : robots_) {
        try {
            robot->work();
        } catch (const std::runtime_error& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }
}

void Fleet::charge_all() const {
    for (const auto& [id, robot] : robots_) {
        robot->charge();
    }
}

std::size_t Fleet::size() const {
    return robots_.size();
}

bool Fleet::empty() const {
    return robots_.empty();
}

Fleet& Fleet::operator+=(std::shared_ptr<Robot> robot) {
    this->add(robot);
    return *this;
}

Fleet& Fleet::operator-=(const std::string& id) {
    this->remove(id);
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Fleet& f) {
    os << "Fleet Status Summary (" << f.size() << " active robots):\n";
    for (const auto& [id, robot] : f.robots_) {
        os << " - " << *robot << "\n";
    }
    return os;
}
