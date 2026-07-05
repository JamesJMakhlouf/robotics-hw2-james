#pragma once
#include "robot.hpp"
#include "task.hpp"
#include <memory>
#include <string>
#include <ostream>
#include <unordered_map>
#include <queue>

class Fleet {
public:
    void add(std::shared_ptr<Robot> robot);
    void remove(const std::string& id);
    std::shared_ptr<Robot> find(const std::string& id) const;

    // Stores the task in the priority queue and marks the robot as busy.
    void assign_task(const std::string& robot_id, const Task& t);
    void show_tasks()  const;  // prints the task queue in priority order

    void work_all()    const;  // calls work() on every robot
    void charge_all()  const;  // calls charge() on every robot

    std::size_t size()  const;
    bool        empty() const;

    Fleet& operator+=(std::shared_ptr<Robot> robot);
    Fleet& operator-=(const std::string& id);
    friend std::ostream& operator<<(std::ostream& os, const Fleet& f);

    void find_low_battery() const;

private:
    // std::unordered_map allows the fleet to find or remove any robot by its
    // unique id in constant time, without performing slow linear scans. 

    // we use std::shared_ptr instead of std::unique_ptr because multiple
    // parts of the program need access to the same robot at the same time.
    // for example, both the Fleet and active background threads need to reference
    // a robot without stripping ownership from one another.
    std::unordered_map<std::string, std::shared_ptr<Robot>> robots_;
    
    // std::priority_queue maintains elements sorted according to their
    // priority, guarateeing that the the highest priority tasks are
    // always placed at the start for instantaneous access.
    std::priority_queue<Task> tasks_;
};