#include "Administrator.hpp"
#include "Flight.hpp"
#include "AirlineOperations.hpp"
#include "Aircraft.hpp"
#include <exception>
#include <iostream>
#include <limits>

//Function which will print down the menu choices for user
void Administrator::showMenu() {
    while (loggedIn) {
        std::cout << "\n====================================\n"
                  << "        ADMINISTRATOR MENU          \n"
                  << "====================================\n"
                  << "1. Create User\n"
                  << "2. Update User\n"
                  << "3. Delete User\n"
                  << "4. Manage Flights\n"
                  << "5. Log Out\n"
                  << "Enter your choice: ";

        int choice;

        //Safety check to prevent bad user input
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input! Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1: {
                std::string name, role, email, password;

                std::cout << "Enter Name: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, name);

                std::cout << "Enter Role (Passenger / BookingAgent / Administrator): ";
                std::cin >> role;

                std::cout << "Enter Email: ";
                std::cin >> email;

                std::cout << "Enter Password: ";
                std::cin >> password;

                createUser(name, role, email, password);
                break;
            }
            case 2: {                
                int targetId;
                std::string targetRole;

                std::cout << "Enter User ID to update: ";
                std::cin >> targetId;

                std::cout << "Enter Role of the user: ";
                std::cin >> targetRole;

                std::string newName;
                std::cout << "Enter New Name: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, newName);

                updateUserName(targetId, targetRole, newName);
                break;
            }
            case 3: {
                int targetId;
                std::string targetRole;

                std::cout << "Enter User ID to delete: ";
                std::cin >> targetId;

                std::cout << "Enter Role of the user: ";
                std::cin >> targetRole;

                deleteUser(targetId, targetRole);
                break;
            }
            case 4:
                manageFlights();
                break;

            case 5:
                loggedIn = false;
                std::cout << "Logged out successfully.\n";
                break;

            default:
                std::cout << "Invalid option! Please try again.\n";
                break;
        }
    }
}


//Function which will trigger creation of new flight
//If there is a flight number on the same date this will throw an error and must be catched
bool Administrator::createNewFlight(std::string newFlightNumber, std::string newOrigin, std::string newDestination,
                std::string newDepartureDate, std::string newDepartureTime, int newDuration){
          try{
            auto airlineOperationsPtr = User::getAirlineOperations();
            
            //check nullability before dereferencing
            if(airlineOperationsPtr){
                airlineOperationsPtr->checkFlightContradiction(newFlightNumber, newDepartureDate);
                (airlineOperationsPtr->allFlights).push_back(std::make_shared<Flight>(Flight(std::move(newFlightNumber), std::move(newOrigin), 
                                                                                        std::move(newDestination), std::move(newDepartureDate),
                                                                                         std::move(newDepartureTime), newDuration)));
                //return indicating successfull operation
                return true;
            }else{
                std::cout << "No airlines reference found!";
                return false;
            }
          } catch(std::exception& e){
            std::cout << std::endl << e.what() << std::endl;
            //indicating failed operation
            return false;
          } 
        }


//Function which updates flight status
//Should be either "Scheduled" or "Delayed" or "Cancelleed" or "Departured"
bool Administrator::updateFlightStatus(const std::string& targetFlightNumber, const std::string& targetFlightDeparture,
                        std::string flightNewStatus){
            auto airlineOperationsPtr = User::getAirlineOperations();
            
            //check nullability before dereferencing
            if(airlineOperationsPtr)
            {
                //Loop and search for target flight
                for(auto eachFlight: airlineOperationsPtr->allFlights)
                {
                    //if target flight found, check if new status is same as flight current status
                    if(eachFlight->getFlightNumber() == targetFlightNumber
                        && eachFlight->getDepartureDate() == targetFlightDeparture)
                        {
                            if(eachFlight->getFlightStatus() == flightNewStatus)
                            {
                                std::cout << "Flight status is already " << flightNewStatus << std::endl;
                                eachFlight->printFlightInfo();
                                return true;
                            } else{
                                //update status
                                eachFlight->setFlightStatus(std::move(flightNewStatus));
                                std::cout << "Flight updated successfully!\n";
                                eachFlight->printFlightInfo();
                                return true;
                            }
                        }
                }
                //if there is no any flight found based on criteria, then return false
                std::cout << "No flights found based on entered criteria, please try again!\n";
                return false;
            }
        }

//Function which affects flight status and departure time, by passing delay in hours and in mins
bool Administrator::delayFlight(const std::string& targetFlightNumber,
                                const std::string& targetFlightDepartureDate, int hours, int mins){
    if(hours > 24)
    {
        std::cout << "Invalid hours, should be between 0 and 24 hours, please try again\n";
        return false;
    }else if(mins > 60)
    {
        std::cout <<"Invalid minutes, should be between 0 and 60 mins, please try again\n";
        return false;
    }else
    {
        //Assign delay to flight, first get airlines reference

        auto airlineOperationsPtr = User::getAirlineOperations();
        
        //check nullability before dereferencing
        if(airlineOperationsPtr)
        {
            //Loop and search for target flight
            for(auto eachFlight : airlineOperationsPtr->allFlights)
            {
                //if target flight found, check if new status is same as flight current status
                if(eachFlight->getFlightNumber() == targetFlightNumber
                    && eachFlight->getDepartureDate() == targetFlightDepartureDate)
                    {
                        eachFlight->setDelay(hours, mins);
                        //indicating successfull operation
                        std::cout << "Delay for flight was set successfully!\n";
                        eachFlight->printFlightInfo();
                        return true;
                    }

            }
            //else if target flight was not found inform user and return
            std::cout << "Flight not found, please double check criteria and try again!\n";
            return false;
        } else{
            std::cout << "No airlines reference found!";
            return false;
        }
        
    }

}

//Function which creates new aircraft and add it to aircrafts list
//Aircraft tail number should be unique
bool Administrator::createNewAircraft(std::string tailNumber, std::string model, int capacity, bool isAvailable = true)
{
    //get reference to airline operations
    auto airlineOperationsPtr = User::getAirlineOperations();

    //Check for nullability
    if(airlineOperationsPtr)
    {
        //search if there is existing tailNumber in one of aircrafts
        //loop on each aircraft
        for(auto eachAircraft: airlineOperationsPtr->allAircrafts)
        {
            if(eachAircraft->getTailNumber() == tailNumber)
            {
                //return safely indicating existing aircraft with same tail number exists
                std::cout << "Tail number already exists, it cannot duplicate, please try again!\n";
                return false;
            }
        }
        //if tail number didn't contradict then add new aircraft
        airlineOperationsPtr->allAircrafts.push_back(std::make_shared<Aircraft>(std::move(tailNumber), std::move(model), capacity, isAvailable));
        return true;
    } else{
        std::cout << "No airlines reference found!";
        return false;
    }
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

