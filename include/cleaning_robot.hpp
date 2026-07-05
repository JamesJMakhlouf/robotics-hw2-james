#pragma once
#include "mobile_robot.hpp"

class CleaningRobot : public MobileRobot {
public:
    CleaningRobot(const std::string& id, const std::string& name, int battery, double speed, const std::string& tool);

    void work() override;
    std::string type()  const override;

protected:
    std::string tool_;
};