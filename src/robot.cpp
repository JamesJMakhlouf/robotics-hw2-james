#include "robot.hpp"
#include <iostream>
#include <algorithm>

Robot::Robot(const std::string& id, const std::string& name, int battery) : id_(id), name_(name), status_("idle") {
    battery_ = std::max(0, std::min(100, battery));
}

void Robot::charge() {
    if (battery_ == 100) {
        std::cout << "Battery full.\n";
        return;
    }
    battery_ = 100;
    status_ = "charging";
}

std::string Robot::id() const {
    return id_;
}
    
std::string Robot::name() const {
    return name_;
}

int Robot::battery() const {
    return battery_;
}

std::string Robot::status() const {
    return status_;
}

void Robot::set_status(const std::string& status) {
    status_ = status;
}

bool Robot::operator==(const Robot& other) const {
    return id_ == other.id();
}

std::string Robot::operator+(const Robot& other) const {
    return name_ + " + " + other.name();
}

// In `std::coud << robot`, the left-hand operand is an `srd::ostream`,
// not a Robot object. C++ member function require the host class
// object to be on the left side, so this must be a non-member free
// function
// Because it is a free function standing outside the class, it would
// normally be blocked from accessing proteeected or private members.
// Marking it as `friend` inside the header grants it explicit permission
// to look inside.
std::ostream& operator<<(std::ostream& os, const Robot& r) {
    os << "[" << r.type() << "] ID: " << r.id() 
       << ", Name: " << r.name_ 
       << ", Battery: " << r.battery_ << "%"
       << ", Status: " << r.status_;
    return os;
}
