#include <iostream>
#include <string>
#include <memory>
#include <limits>
#include "fleet.hpp"
#include "mobile_robot.hpp"
#include "cleaning_robot.hpp"
#include "cooking_robot.hpp"

void print_menu() {
    std::cout << "\n=== Robot Fleet Manager ===\n"
              << "1. Add robot\n"
              << "2. Remove robot\n"
              << "3. Show all robots\n"
              << "4. Work (single robot)\n"
              << "5. Work all\n"
              << "6. Charge all\n"
              << "7. Assign task to robot\n"
              << "8. Show task queue\n"
              << "9. Find first robot below 20% battery\n"
              << "10. Start timed work on a robot\n"
              << "0. Exit\n"
              << "Enter choice: ";
}

int main() {
    Fleet fleet;
    int choice = -1;

    while (choice != 0) {
        print_menu();
        
        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a valid menu number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1: { // Add robot
                int type_choice = 0;
                std::string id, name;
                int battery = 100;
                
                std::cout << "Select Robot Type (1: Mobile, 2: Cleaning, 3: Cooking): ";
                std::cin >> type_choice;
                std::cout << "Enter ID: "; std::cin >> id;
                std::cout << "Enter Name: "; std::cin >> name;
                std::cout << "Enter Battery (%): "; std::cin >> battery;

                switch (type_choice) {
                    case 1: { // Mobile robot
                        double speed;
                        std::string tool;
                        std::cout << "Enter Speed (m/s): "; std::cin >> speed;
                        fleet.add(std::make_shared<MobileRobot>(id, name, battery, speed));
                        break;
                    }
                    case 2: { // Cleaning robot
                        double speed;
                        std::string tool;
                        std::cout << "Enter Speed (m/s): "; std::cin >> speed;
                        std::cout << "Enter Cleaning Tool (vacuum/mop): "; std::cin >> tool;
                        fleet.add(std::make_shared<CleaningRobot>(id, name, battery, speed, tool));
                        break;
                    } case 3: { // Cooking robot
                        std::string cuisine;
                        std::cout << "Enter Cuisine Specialty: "; std::cin >> cuisine;
                        fleet.add(std::make_shared<CookingRobot>(id, name, battery, cuisine));
                        break;
                    } default: {
                        std::cout << "Invalid type choice selection.\n";
                        break;
                    }

                }
                break;
            }
            case 2: { // Remove robot
                std::string id;
                std::cout << "Enter Robot ID to remove: ";
                std::cin >> id;
                fleet.remove(id);
                break;
            }
            case 3: // Show all robots
                std::cout << fleet;
                break;

            case 4: { // Work (single robot)
                std::string id;
                std::cout << "Enter Robot ID to execute work: ";
                std::cin >> id;
                try {
                    auto robot = fleet.find(id);
                    robot->work();
                } catch (const std::runtime_error& e) {
                    std::cout << "Error: " << e.what() << "\n";
                }
                break;
            }
            case 5: // Work all
                fleet.work_all();
                break;

            case 6: // Charge all
                fleet.charge_all();
                break;

            case 7: { // Assign task to robot
                std::string id, task_name;
                int priority;
                std::cout << "Enter Robot ID: "; std::cin >> id;
                std::cout << "Enter Task Name: "; std::cin >> task_name;
                std::cout << "Enter Task Priority (1 (low) to 5 (high)): "; std::cin >> priority;
                std::cin.ignore();

                Task t{task_name, priority, id};
                fleet.assign_task(id, t);
                break;
            }
            case 8: // Show task queue
                fleet.show_tasks();
                break;

            case 9: // Find first robot below 20% battery
                fleet.find_low_battery();
                break;

            case 10: { // Start timed work on a robot
                std::string id;
                int seconds;
                std::cout << "Enter Robot ID for timed background execution: "; std::cin >> id;
                std::cout << "Enter working duration (seconds): "; std::cin >> seconds;

                try {
                    auto robot = fleet.find(id);
                    auto mobile_robot = std::dynamic_pointer_cast<MobileRobot>(robot);
                    
                    if (mobile_robot) {
                        std::cout << "Launching timed worker loop thread for " << mobile_robot->name() << "...\n";
                        mobile_robot->start_work(seconds);
                    } else {
                        std::cout << "Notice: Asynchronous timed loop targets are only supported by Mobile Robots.\n";
                        robot->work(); 
                    }
                } catch (const std::runtime_error& e) {
                    std::cout << "Error: " << e.what() << "\n";
                }
                break;
            }
            case 0:
                std::cout << "Exiting Fleet Command System Console.\n";
                break;

            default:
                std::cout << "Option unrecognized. Try again.\n";
                break;
        }
    }
    return 0;
}