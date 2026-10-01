#include "Administrator.hpp"
#include "Flight.hpp"
#include "AirlineOperations.hpp"
#include "Aircraft.hpp"
#include "UserManager.hpp"
#include "InputUtils.hpp"
#include <iomanip>
#include <exception>
#include <iostream>
#include <limits>

//Function which will print down the menu choices for user
void Administrator::showMenu() {
    bool exitMenu = false;
    while (!exitMenu) {
        std::cout << "\n====================================\n"
                  << "        ADMINISTRATOR MENU          \n"
                  << "====================================\n"
                  << "1. Manage Flights\n"
                  << "2. Manage Aircraft\n"
                  << "3. Manage Users\n"
                  << "4. Generate Reports\n"
                  << "5. Log Out\n";

        int choice = InputUtils::readInt("Enter your choice: ");
        switch (choice) {
            case 1: manageFlights(); break;
            case 2: manageAircraft(); break;
            case 3: manageUsers(); break;
            case 4: generateReports(); break;
            case 5:
                logOut();
                std::cout << "\nLogged out successfully.\n";
                exitMenu = true;
                break;
            default:
                std::cout << "\nInvalid choice, please try again.\n";
        }
    }
}

void Administrator::generateReports() {
    bool exitSubmenu = false;
    while (!exitSubmenu) {
        std::cout << "\n--- Generate Reports ---\n"
                  << "1. Operational Reports\n"
                  << "2. Maintenance Reports\n"
                  << "3. User Activity Reports\n"
                  << "4. Back to Main Menu\n";

        int choice = InputUtils::readInt("Enter choice: ");
        switch (choice) {
            case 1: {
                std::cout << "\n--- Operational Reports ---\n";
                std::string yearMonth;
                std::cout << "Enter Month and Year for Report (YYYY-MM): ";
                std::getline(std::cin, yearMonth);
                generateOperationalReport(yearMonth);
                break;
            }
            case 2: {
                std::cout << "\n--- Maintenance Reports ---\n";
                std::string yearMonth;
                std::cout << "Enter Month and Year for Report (YYYY-MM): ";
                std::getline(std::cin, yearMonth);
                generateMaintenanceReport(yearMonth);
                break;
            }
            case 3: {
                std::cout << "\n--- User Activity Reports ---\n";
                std::cout << "Under Development.\n";
                break;
            }
            case 4:
                exitSubmenu = true;
                break;
            default:
                std::cout << "Invalid choice, please try again.\n";
        }
    }
}

void Administrator::manageFlights() {
    bool exitSubmenu = false;
    while (!exitSubmenu) {
        std::cout << "\n====================================\n"
                  << "         FLIGHT MANAGEMENT          \n"
                  << "====================================\n"
                  << "1. View All Flights\n"
                  << "2. Create New Flight\n"
                  << "3. Update Flight Status\n"
                  << "4. Delay Flight\n"
                  << "5. Assign Gate\n"
                  << "6. Create New Crew Member\n"
                  << "7. Assign Crew Member to Flight\n"
                  << "8. Remove Crew Member from Flight\n"
                  << "9. Back to Main Menu\n";

        int choice = InputUtils::readInt("Enter your choice: ");
        switch (choice) {
            case 1:
                viewAllFlights();
                break;
            case 2: {
                //Creating new flight

                bool processApproved = true; //Initialized to true, it will be used to save return status from called function
                std::string flightNumber, origin, destination, departureDate, departureTime;
                int duration;
                do{
                    //If process failed and rentered the loop, ask user if he wants to abort operation
                    if(!processApproved)
                    {
                        int userInput = InputUtils::readInt("To return back to main menu enter '0', to try again enter any number: ");
                        if(userInput == 0) {break;}

                    }
                    std::cout << "\nFlight number: ";    std::getline(std::cin, flightNumber);
                    std::cout << "Origin: ";            std::getline(std::cin, origin);
                    std::cout << "Destination: ";       std::getline(std::cin, destination);
                    std::cout << "Departure date (YYYY-MM-DD): ";    std::getline(std::cin, departureDate);
                    std::cout << "Departure time (HH:MM): ";    std::getline(std::cin, departureTime);
                    duration = InputUtils::readInt("Duration (Hours): ");
                }
                while(!(processApproved = createNewFlight(flightNumber, origin, destination, departureDate, departureTime, duration)));
                break;
            }

            case 3: {
                //Updating flight status

                bool processApproved = true;
                std::string flightNumber, departureDate, newStatus;
                do{
                    if(!processApproved)
                    {
                        int userInput = InputUtils::readInt("To return back to main menu enter '0', to try again enter any number: ");
                        if(userInput == 0) {break;}
                    }
                    std::cout << "\nFlight number: ";  std::getline(std::cin, flightNumber);
                    std::cout << "Departure date: "; std::getline(std::cin, departureDate);
                    std::cout << "New status: ";     std::getline(std::cin, newStatus);
                }
                while(!(processApproved = updateFlightStatus(flightNumber, departureDate, newStatus)));
                break;
            }

            case 4: {
                // Delay flights

                bool processApproved = true;
                std::string flightNumber, departureDate;
                int hours, mins;
                do{
                    if(!processApproved)
                    {
                        int userInput = InputUtils::readInt("To return back to main menu enter '0', to try again enter any number: ");
                        if(userInput == 0) {break;}
                    }
                    std::cout << "\nFlight number: ";   std::getline(std::cin, flightNumber);
                    std::cout << "Departure date: ";  std::getline(std::cin, departureDate);
                    hours = InputUtils::readInt("Delay hours: ");
                    mins = InputUtils::readInt("Delay minutes: ");
                }
                while(!(processApproved = delayFlight(flightNumber, departureDate, hours, mins)));
                break;
            }

            case 5: {
                //Assign gates

                bool processApproved = true;
                std::string flightNumber, departureDate, gate;
                do{
                    if(!processApproved)
                    {
                        int userInput = InputUtils::readInt("To return back to main menu enter '0', to try again enter any number: ");
                        if(userInput == 0) {break;}
                    }
                    std::cout << "\nFlight number: ";   std::getline(std::cin, flightNumber);
                    std::cout << "Departure date (YYYY-MM-DD): ";  std::getline(std::cin, departureDate);
                    std::cout << "Gate (e.g. B12): "; std::getline(std::cin, gate);
                }
                while(!(processApproved = assignGate(flightNumber, departureDate, gate)));
                break;
            }
            case 6: {
                //Create new crew member

                bool processApproved = true;
                std::string name, role;
                do{
                    if(!processApproved)
                    {
                        int userInput = InputUtils::readInt("To return back to main menu enter '0', to try again enter any number: ");
                        if(userInput == 0) {break;}
                    }
                    std::cout << "\nName: ";
                    std::getline(std::cin, name);
                    std::cout << "Role (Pilot/CoPilot/FlightAttendant): ";
                    std::getline(std::cin, role);
                }
                while(!(processApproved = createNewCrewMember(name, role)));
                break;
            }
            case 7: {
                //Assign crew member to flight

                bool processApproved = true;
                int targetID;
                std::string flightNumber, departureDate;

                //First print all crew members info, sorted by pilots, copilots and flight attendants
                //So admin can choose the required by his ID
                //If returned false, this means no crew members on airline, so inform user and skip operation
                if(!(printAllCrewMembers()))
                {
                    std::cout << "\nNo crew members on airline!\nReturning back to menu...\n";
                    continue;
                }
                do{
                    if(!processApproved)
                    {
                        int userInput = InputUtils::readInt("To return back to main menu enter '0', to try again enter any number: ");
                        if(userInput == 0) {break;}
                    }
                    targetID = InputUtils::readInt("\nCrew member ID: ");
                    std::cout << "Flight number: ";   std::getline(std::cin, flightNumber);
                    std::cout << "Departure date: ";  std::getline(std::cin, departureDate);
                }
                while(!(processApproved = assignCrewMemberToFlight(targetID, flightNumber, departureDate)));
                break;
            }
            case 8: {
                //Remove crew member from flight

                bool processApproved = true;
                int targetID;
                std::string flightNumber, departureDate;
                
                //First print all crew members info, sorted by pilots, copilots and flight attendants
                //So admin can choose the required by his ID
                //If returned false, this means no crew members on airline, so inform user and skip operation
                if(!(printAllCrewMembers()))
                {
                    std::cout << "\nNo crew members on airline!\nReturning back to menu...\n";
                    continue;
                }
                do{
                    if(!processApproved)
                    {
                        int userInput = InputUtils::readInt("To return back to main menu enter '0', to try again enter any number: ");
                        if(userInput == 0) {break;}
                    }
                    targetID = InputUtils::readInt("\nCrew member ID: ");
                    std::cout << "Flight number: ";   std::getline(std::cin, flightNumber);
                    std::cout << "Departure date: ";  std::getline(std::cin, departureDate);
                }
                while(!(processApproved = removeCrewMemberFromFlight(targetID, flightNumber, departureDate)));
                break;
            }
            case 9: exitSubmenu = true; break;
            default: std::cout << "Invalid choice, please try again.\n";
        }
    }
}

void Administrator::manageAircraft() {
    bool exitSubmenu = false;
    while (!exitSubmenu) {
        std::cout << "\n====================================\n"
                  << "         AIRCRAFT MANAGEMENT        \n"
                  << "====================================\n"
                  << "1. Create New Aircraft\n"
                  << "2. Assign Aircraft to Flight\n"
                  << "3. Schedule Maintenance\n"
                  << "4. Back to Main Menu\n";

        int choice = InputUtils::readInt("Enter your choice: ");
        switch (choice) {
            case 1: {
                //Creating new aircraft

                bool processApproved = true;
                std::string tailNumber, model;
                int capacity;
                bool isAvailable;
                do{
                    if(!processApproved)
                    {
                        int userInput = InputUtils::readInt("To return back to main menu enter '0', to try again enter any number: ");
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        if(userInput == 0) {break;}
                    }
                    std::cout << "\nTail number: ";       std::getline(std::cin, tailNumber);
                    std::cout << "Model: ";             std::getline(std::cin, model);
                    std::cout << "Capacity: ";          std::cin >> capacity;
                    isAvailable = InputUtils::readInt("Available? (1/0): ") != 0;
                }
                while(!(processApproved = createNewAircraft(tailNumber, model, capacity, isAvailable)));
                break;
            }
            case 2: {
                //Assign aircraft to flight

                bool processApproved = true;
                std::string tailNumber, flightNumber, departureDate;
                do{
                    if(!processApproved)
                    {
                        int userInput = InputUtils::readInt("To return back to main menu enter '0', to try again enter any number: ");
                        if(userInput == 0) {break;}
                    }
                    std::cout << "\nTail number: ";    std::getline(std::cin, tailNumber);
                    std::cout << "Flight number: ";  std::getline(std::cin, flightNumber);
                    std::cout << "Departure date: "; std::getline(std::cin, departureDate);
                }
                while(!(processApproved = assignAircraftToFlight(tailNumber, flightNumber, departureDate)));
                break;
            }
            case 3: {
                //Create new maintenance schedule

                bool processApproved = true;
                std::string tailNumber, dateScheduled, description;
                do{
                    if(!processApproved)
                    {
                        int userInput = InputUtils::readInt("To return back to main menu enter '0', to try again enter any number: ");
                        if(userInput == 0) {break;}
                    }
                    std::cout << "\nTail number: ";     std::getline(std::cin, tailNumber);
                    std::cout << "Scheduled date: ";  std::getline(std::cin, dateScheduled);
                    std::cout << "Description: ";     std::getline(std::cin, description);
                }
                while(!(processApproved = newAircraftMaintenance(tailNumber, dateScheduled, description)));
                break;
            }
            case 4:
                exitSubmenu = true;
                break;
            default:
                std::cout << "Invalid choice, please try again.\n";
        }
    }
}

void Administrator::manageUsers() {
    bool exitSubmenu = false;
    while (!exitSubmenu) {
        std::cout << "\n====================================\n"
                  << "           USER MANAGEMENT          \n"
                  << "====================================\n"
                  << "1. Create User\n"
                  << "2. Update User\n"
                  << "3. Deactivate User\n"
                  << "4. Back to Main Menu\n";

        int choice = InputUtils::readInt("Enter your choice: ");
        switch (choice) {
            case 1: {
                //Creating new user

                bool processApproved = true;
                std::string name, role, email, password;
                do{
                    if(!processApproved)
                    {
                        int userInput = InputUtils::readInt("To return back to main menu enter '0', to try again enter any number: ");
                        if(userInput == 0) {break;}
                    }
                    std::cout << "\nEnter Name: ";
                    std::getline(std::cin, name);

                    std::cout << "Enter Role (Passenger / BookingAgent / Administrator): ";
                    std::cin >> role;

                    std::cout << "Enter Email: ";
                    std::cin >> email;

                    std::cout << "Enter Password: ";
                    std::cin >> password;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                while(!(processApproved = createUser(name, role, email, password)));
                break;
            }
            case 2: {
                //Updating user name

                bool processApproved = true;
                int targetId;
                std::string targetRole, newName;
                do{
                    if(!processApproved)
                    {
                        int userInput = InputUtils::readInt("To return back to main menu enter '0', to try again enter any number: ");
                        if(userInput == 0) {break;}
                    }

                    targetId = InputUtils::readInt("\nEnter User ID to update: ");

                    std::cout << "Enter Role of the user: ";
                    std::cin >> targetRole;

                    std::cout << "Enter New Name: ";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // needed: previous read was cin >>
                    std::getline(std::cin, newName);
                }
                while(!(processApproved = updateUserName(targetId, targetRole, newName)));
                break;
            }
            case 3: {
                // Deactivating user

                bool processApproved = true;
                int targetId;
                std::string targetRole;
                do{
                    if(!processApproved)
                    {
                        int userInput = InputUtils::readInt("To return back to main menu enter '0', to try again enter any number: ");
                        if(userInput == 0) {break;}
                    }

                   	targetId = InputUtils::readInt("Enter User ID to deactivate: ");

                    std::cout << "Enter Role of the user: ";
                    std::cin >> targetRole;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                while(!(processApproved = deactivateUser(targetId, targetRole)));
                break;
            }
            case 4:
                exitSubmenu = true;
                break;
            default:
                std::cout << "Invalid choice, please try again.\n";
        }
    }
}


//Function which will trigger creation of new flight
//If there is a flight number on the same date this will throw an error and must be catched
bool Administrator::createNewFlight(std::string newFlightNumber, std::string newOrigin, std::string newDestination,
                                     std::string newDepartureDate, std::string newDepartureTime, int newDuration) {
    try {
        auto ops = User::getAirlineOperations();
        if (!ops) {
            std::cout << "No airline operations reference found!\n";
            return false;
        }
        bool result = ops->createFlight(std::move(newFlightNumber), std::move(newOrigin), std::move(newDestination),
                                  std::move(newDepartureDate), std::move(newDepartureTime), newDuration);
        if(result) {std::cout << "\nFlight added successfully!\n";}
        return result;
    } catch (std::exception& e) {
        std::cout << std::endl << e.what() << std::endl;
        return false;
    }
}


//Function which updates flight status
//Should be either "Scheduled" or "Delayed" or "Cancelleed" or "Departured"
bool Administrator::updateFlightStatus(const std::string& targetFlightNumber, const std::string& targetFlightDeparture,
                                        std::string flightNewStatus) {
    auto ops = User::getAirlineOperations();
    if (!ops) {
        std::cout << "No airline operations reference found!\n";
        return false;
    }
    return ops->updateFlightStatus(targetFlightNumber, targetFlightDeparture, std::move(flightNewStatus));
}

//Function which affects flight status and departure time, by passing delay in hours and in mins
bool Administrator::delayFlight(const std::string& targetFlightNumber, const std::string& targetFlightDepartureDate,
                                 int hours, int mins) {
    if (hours < 0 || hours > 23) {
        std::cout << "Invalid hours, should be between 0 and 23 hours, please try again\n";
        return false;
    }
    if (mins < 0 || mins > 59) {
        std::cout << "Invalid minutes, should be between 0 and 59 mins, please try again\n";
        return false;
    }

    auto ops = User::getAirlineOperations();
    if (!ops) {
        std::cout << "No airline operations reference found!\n";
        return false;
    }
    return ops->delayFlight(targetFlightNumber, targetFlightDepartureDate, hours, mins);
}

//Function which creates new aircraft and add it to aircrafts list
//Aircraft tail number should be unique
bool Administrator::createNewAircraft(std::string tailNumber, std::string model, int capacity, bool isAvailable) {
    if (capacity <= 0) {
        std::cout << "Capacity must be greater than zero, please try again!\n";
        return false;
    }

    auto ops = User::getAirlineOperations();
    if (!ops) {
        std::cout << "No airline operations reference found!\n";
        return false;
    }
    return ops->createAircraft(std::move(tailNumber), std::move(model), capacity, isAvailable);
}

//Function which assigns aircraft to a flight
//Aircraft should not have any flights on the same day of the targetted flight
bool Administrator::assignAircraftToFlight(const std::string& tailNumber, const std::string& flightNumber, const std::string& departureDate)
{
    auto ops = User::getAirlineOperations();
    if (!ops) {
        std::cout << "No airline operations reference found!\n";
        return false;
    }
    return ops->assignAircraftToFlight((tailNumber), flightNumber, departureDate);
}

bool Administrator::createNewCrewMember(std::string name, std::string role) {
    // Validate role is one of the accepted values — input sanity check, belongs here
    if (role != "Pilot" && role != "CoPilot" && role != "FlightAttendant") {
        std::cout << "Invalid role, must be Pilot, CoPilot, or FlightAttendant. Please try again!\n";
        return false;
    }

    if (name.empty()) {
        std::cout << "Name cannot be empty, please try again!\n";
        return false;
    }

    auto ops = User::getAirlineOperations();
    if (!ops) {
        std::cout << "No airline operations reference found!\n";
        return false;
    }

    return ops->createCrewMember(std::move(name), std::move(role));
}

bool Administrator::assignCrewMemberToFlight(int targetID, const std::string& flightNumber, const std::string& departureDate) {
    auto ops = User::getAirlineOperations();
    if (!ops) {
        std::cout << "No airline operations reference found!\n";
        return false;
    }
    return ops->assignCrewMemberToFlight(targetID, flightNumber, departureDate);
}

bool Administrator::removeCrewMemberFromFlight(int targetID, const std::string& flightNumber, const std::string& departureDate) {
    auto ops = User::getAirlineOperations();
    if (!ops) {
        std::cout << "No airline operations reference found!\n";
        return false;
    }
    return ops->removeCrewMemberFromFlight(targetID, flightNumber, departureDate);
}

bool Administrator::newAircraftMaintenance(const std::string& tailNumber, std::string dateScheduled, std::string caseDescription) {
    if (dateScheduled.empty()) {
        std::cout << "Scheduled date cannot be empty, please try again!\n";
        return false;
    }
    if (caseDescription.empty()) {
        std::cout << "Description cannot be empty, please try again!\n";
        return false;
    }

    auto ops = User::getAirlineOperations();
    if (!ops) {
        std::cout << "No airline operations reference found!\n";
        return false;
    }
    return ops->newAircraftMaintenance(tailNumber, std::move(dateScheduled), std::move(caseDescription));
}

//Function which creates user based on criteria
//User's role must be either: Passenger, BookingAgent or Administrator
//If passed argument is neither of them it should print error message and abort creation
//If all arguments are valid, print successfull message
bool Administrator::createUser(const std::string& passedName, const std::string& passedRole, const std::string& passedEmail, const std::string& password)
{
        auto manager = allUsersReference.lock();
    if (!manager) {
        std::cout << "No user manager reference found!\n";
        return false;
    }
    return manager->createUser(passedName, passedRole, passedEmail, password);
}

//Function which deletes user by id and role (Passenger, BookingAgent or Administrator)
//If id not found print error message and abort process
//If user found print successfull message
//Note: an admin can not delete him self 
bool Administrator::deactivateUser(int id, const std::string& role)
{
    //Self check
    if((id == this->id) && (role == this->role))
    {
        std::cout << "You cannot delete your own account.\n";
        return false;
    }

    //Check if user manager is available
    auto manager = allUsersReference.lock();
    if (!manager) {
        std::cout << "No user manager reference found!\n";
        return false;
    }

    return manager->deactivateUser(id, role);
}

bool Administrator::updateUserName(int id, const std::string& role, std::string newName)
{
    //Check if user manager is available
    auto manager = allUsersReference.lock();
    if (!manager) {
        std::cout << "No user manager reference found!\n";
        return false;
    }

    //Pass parameters to UserManager to handle process
   return manager->updateUserName(id, role, std::move(newName));
}

bool Administrator::assignGate(const std::string& flightNumber, const std::string& departureDate, std::string gate)
{
    if (gate.empty()) {
        std::cout << "Gate cannot be empty, please try again!\n";
        return false;
    }
    auto ops = User::getAirlineOperations();
    if (!ops) {
        std::cout << "No airline operations reference found!\n";
        return false;
    }
    return ops->assignGate(flightNumber, departureDate, std::move(gate));
}

bool Administrator::viewAllFlights()
{
    auto ops = User::getAirlineOperations();
    if (!ops) {
        std::cout << "No airline operations reference found!\n";
        return false;
    }
    return ops->viewAllFlights();
}

bool Administrator::printAllCrewMembers()
{
    auto ops = User::getAirlineOperations();
    if (!ops) {
        std::cout << "No airline operations reference found!\n";
        return false;
    }
    
    return ops->printAircrewEmployees();
}


void Administrator::generateOperationalReport(const std::string& yearMonth)
{
    auto ops = User::getAirlineOperations();
    if (!ops) {
        std::cout << "No airline operations reference found!\n";
        return;
    }
    ops->generateOperationalReport(yearMonth);
}

void Administrator::generateMaintenanceReport(const std::string& yearMonth) {
    auto ops = User::getAirlineOperations();
    if (!ops) {
        std::cout << "No airline operations reference found!\n";
        return;
    }
    ops->generateMaintenanceReport(yearMonth);
}