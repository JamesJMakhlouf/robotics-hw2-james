#pragma once
#include "robot.hpp"
#include <thread>
#include <atomic>

class CookingRobot : public Robot {
public:
    CookingRobot(const std::string& id, const std::string& name,
                int battery, const std::string& cuisine);

    void work() override;
    std::string type() const override;

protected:
    std::string cuisine_;
};