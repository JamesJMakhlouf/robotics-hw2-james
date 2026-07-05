#include "cleaning_robot.hpp"
#include <iostream>

CleaningRobot::CleaningRobot(const std::string& id, const std::string& name, int battery, double speed, const std::string& tool) :
    MobileRobot(id, name, battery, speed), tool_(tool) {}

void CleaningRobot::work() {
    if (battery_ < 20) {
        status_ = "idle";
        throw std::runtime_error(name_ + " cannot work: low battery.");
    }
    battery_ -= 20;
    status_ = "working";
    std::cout << name_ << " is moving at " << speed_ << " m/s and cleaning with a " << tool_ << ". Remaining battery: " << battery_ << "%\n";
}

std::string CleaningRobot::type() const {
    return "Cleaning Robot";
}