#include "cooking_robot.hpp"
#include <iostream>

CookingRobot::CookingRobot(const std::string& id, const std::string& name, int battery, const std::string& cuisine) :
    Robot(id, name, battery), cuisine_(cuisine) {}

void CookingRobot::work() {
        if (battery_ < 30) {
        status_ = "idle";
        throw std::runtime_error(name_ + " cannot work: low battery.");
    }
    battery_ -= 30;
    status_ = "working";
    std::cout << name_ << " is cooking a " << cuisine_ << " dish. Remaining battery: " << battery_ << "%\n";
}
std::string CookingRobot::type() const {
    return "Cooking Robot";
}