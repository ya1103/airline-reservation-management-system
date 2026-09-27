#include <iostream>
#include <memory>
#include <limits>
#include "User.hpp"
#include "UserManager.hpp"
#include "AirlineOperations.hpp"

int main() {
    std::cout << "Airline System Starting...\n";

    // Create the two shared "hub" objects. Both MUST be make_shared to be in heap not stack
    //  and every User subclass needs a valid AirlineOperations to book/search flights.
    auto airlineOps = std::make_shared<AirlineOperations>();
    auto userManager = std::make_shared<UserManager>();

    //Wire the static reference BEFORE any user tries to search/book —
    //  this is the "must happen before any Passenger/BookingAgent method touches flights" step.
    User::setFlightsReference(airlineOps);

    //TEMPORARY: seed one Administrator so the system is usable on a fresh run.
    //  Once file loading from data exists, this should only run if no users were loaded.
    userManager->createUser("System Admin", "Administrator", "admin@airline.com", "admin123");

    bool programRunning = true;
    while (programRunning) {
        std::cout << "\n====================================\n"
                  << "     AIRLINE RESERVATION SYSTEM     \n"
                  << "====================================\n"
                  << "1. Log In\n"
                  << "2. Register as Passenger\n"
                  << "3. Exit\n"
                  << "Enter your choice: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: {
                std::string email, password;
                std::cout << "Email: ";    std::cin >> email;
                std::cout << "Password: "; std::cin >> password;

                auto loggedInUser = userManager->logIn(email, password);
                if (!loggedInUser) {
                    std::cout << "Invalid email or password, please try again.\n";
                    break;
                }
                std::cout << "\nLogged in successfully\n" 
                            << "Welcome Back " << loggedInUser->getName() << "\nYour role is " << loggedInUser->getRole() << std::endl;


                loggedInUser->showMenu(); // polymorphic — runs the right menu for whatever role this is
                break;
            }
            case 2: {
                std::string name, email, password;
                std::cout << "Name: ";     
                std::getline(std::cin, name);
                std::cout << "Email: ";    std::cin >> email;
                std::cout << "Password: "; std::cin >> password;

                userManager->createUser(name, "Passenger", email, password);
                break;
            }
            case 3:
                programRunning = false;
                std::cout << "Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice, please try again.\n";
        }
    }

    return 0;
}