#include "mobile_robot.hpp"
#include <iostream>
#include <chrono>
#include <stdexcept>

MobileRobot::MobileRobot(const std::string& id, const std::string& name, int battery, double speed) : Robot(id, name, battery), speed_(speed) {}

void MobileRobot::work() {
    if (battery_ < 20) {
        status_ = "idle";
        throw std::runtime_error(name_ + " cannot work: low battery.");
    }
    battery_ -= 20;
    status_ = "working";
    std::cout << name_ << " is moving at " << speed_ << " m/s. Remaining battery: " << battery_ << "%\n";
}

std::string MobileRobot::type() const {
    return "Mobile Robot";
}

void MobileRobot::start_work(int seconds) {
    stop_ = true;
    if (worker_.joinable()) worker_.join();

    stop_ = false;

    worker_ = std::thread([this, seconds]() {
        for (int i = 0; i < seconds; ++i) {
            if (stop_) break;

            try {
                this->work();
            } catch (const std::runtime_error& e) {
                std::cout << "Error: " << e.what() << "\n";
                break;
            }
            std::cout << "-> Current status: " << status_ << "\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        status_ = "idle";
    });
}

MobileRobot::~MobileRobot() {
    stop_ = true;
    if (worker_.joinable()) worker_.join();
}