#include "Passenger.hpp"
#include "AirlineOperations.hpp"
#include "Reservation.hpp"
#include <limits>
#include <iostream>

void Passenger::showMenu(){
    while (loggedIn) {
        std::cout << "\n====================================\n"
                  << "           PASSENGER MENU           \n"
                  << "====================================\n"
                  << "1. Search Flight\n"
                  << "2. View Available Seats\n"
                  << "3. Book Flight\n"
                  << "4. Check-In\n"
                  << "5. View Booking History\n"
                  << "6. Log Out\n"
                  << "Enter your choice: ";

        int choice;

        // Input validation for menu selection
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input! Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1: {
                bool processApproved = true;
                std::string departureDate, origin, destination;
                do{
                    if(!processApproved)
                    {
                        std::cout << "To return back to passenger menu enter '0', to try again enter any number: ";
                        int userInput;
                        std::cin >> userInput;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        if(userInput == 0) {break;}
                    }
                    std::cout << "Enter Departure Date (YYYY-MM-DD): ";
                    std::cin >> departureDate;

                    std::cout << "Enter Origin City: ";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::getline(std::cin, origin);

                    std::cout << "Enter Destination City: ";
                    std::getline(std::cin, destination);
                }
                while(!(processApproved = searchFlight(departureDate, origin, destination)));
                break;
            }
            case 2: {
                bool processApproved = true;
                std::string flightNumber, departureDate;
                do{
                    if(!processApproved)
                    {
                        std::cout << "To return back to passenger menu enter '0', to try again enter any number: ";
                        int userInput;
                        std::cin >> userInput;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        if(userInput == 0) {break;}
                    }
                    std::cout << "Enter Flight Number: ";
                    std::cin >> flightNumber;

                    std::cout << "Enter Departure Date (YYYY-MM-DD): ";
                    std::cin >> departureDate;
                }
                while(!(processApproved = availableSeats(flightNumber, departureDate)));
                break;
            }
            case 3: {
                bool processApproved = true;
                std::string flightNumber, seatNumber, departureDate;
                do{
                    if(!processApproved)
                    {
                        std::cout << "To return back to passenger menu enter '0', to try again enter any number: ";
                        int userInput;
                        std::cin >> userInput;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        if(userInput == 0) {break;}
                    }
                    std::cout << "Enter Flight Number: ";
                    std::cin >> flightNumber;

                    std::cout << "Enter Seat Number: ";
                    std::cin >> seatNumber;

                    std::cout << "Enter Departure Date (YYYY-MM-DD): ";
                    std::cin >> departureDate;
                }
                while(!(processApproved = bookFlight(flightNumber, seatNumber, departureDate)));
                if (processApproved) {
                    std::cout << "Booking process initiated successfully! Please proceed to payment.\n";
                }
                break;
            }
            case 4: {
                bool processApproved = true;
                int reservationID;
                do{
                    if(!processApproved)
                    {
                        std::cout << "To return back to passenger menu enter '0', to try again enter any number: ";
                        int userInput;
                        std::cin >> userInput;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        if(userInput == 0) {break;}
                    }
                    std::cout << "Enter Reservation ID for Check-In: ";
                    std::cin >> reservationID;
                }
                while(!(processApproved = checkIn(reservationID)));
                break;
            }
            case 5: {
                viewHistory();
                break;
            }
            case 6: {
                logOut();
                std::cout << "Logged out successfully.\n";
                break;
            }
            default: {
                std::cout << "Invalid option! Please try again.\n";
                break;
            }
        }
    }
}

bool Passenger::searchFlight(const std::string& departureDate, const std::string& origin, const std::string& destination)
{
    auto AirlineOperationsPtr = User::airlineOperationsReference; //Airline operations pointer which holds all flights and seats

    //Check nullability before dereferencing
    if(!AirlineOperationsPtr)
    {
        std::cout << "No airline operations reference found!\n";
        return false;
    }

    return AirlineOperationsPtr->searchFlight(departureDate, origin, destination);
}

bool Passenger::availableSeats(const std::string& flightNumber, const std::string& departureDate)
{
     auto AirlineOperationsPtr = User::airlineOperationsReference; //Airline operations pointer which holds all flights and seats

    //Check nullability before dereferencing
    if(!AirlineOperationsPtr)
    {
        std::cout << "No airline operations reference found!\n";
        return false;
    }

    //Call airline operations to perform seats search
    return AirlineOperationsPtr->searchAvailableSeats(flightNumber, departureDate);
    
}

bool Passenger::bookFlight(const std::string& flightNumber, const std::string& seatNumber, const std::string& departureDate)
{
    auto AirlineOperationsPtr = User::airlineOperationsReference; //Airline operations pointer which holds all flights and seats

    //Check nullability before dereferencing
    if(!AirlineOperationsPtr)
    {
        std::cout << "No airline operations reference found!\n";
        return false;
    }

    auto [flight, seat] = AirlineOperationsPtr->bookFlight(flightNumber, departureDate, seatNumber);
    
    //Check if process was sucessfull
    //If not, an error message should be already printed when bookFlight was called in AirlineOperationsPtr
    //Return false, indicating failed process
    if(!flight || !seat) {return false;}

    //Create a new reservation 
    auto newReservation = std::make_shared<Reservation>(shared_from_this(), flight, seat);
    newReservation->assignReservationToFlightAndSeat();
    makeReservation(std::move(newReservation));

    std::cout << "Seat " << seatNumber << " booked successfully on flight " << flightNumber << "!\n";
    return true;   
}