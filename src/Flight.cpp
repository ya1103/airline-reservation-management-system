#include "Flight.hpp"
#include "CrewMember.hpp"
#include "Aircraft.hpp"
#include "Seat.hpp"
#include "Reservation.hpp"
#include "algorithm"
#include <iomanip>
#include <iostream>


//Function which must be called after constructing each flight
//Unless no seats are assigned to this flight
void Flight::initializeSeats() {
    const char columns[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
    seatsReference.reserve(210);

    for (int r = 1; r <= 30; ++r) {
        for (int c = 0; c < 7; ++c) {
            std::string seatNumberStr = std::to_string(r) + columns[c];
            
            //Assigns seats to flight eg. "1A" "21B" and so on
            seatsReference.push_back(std::make_shared<Seat>(shared_from_this(), seatNumberStr, "Economy", 50.00));
        }
    }
}

//Helper function to print flight details
void Flight::printFlightInfo() const {
    std::cout << "========================================\n";
    std::cout << "           FLIGHT INFORMATION           \n";
    std::cout << "========================================\n";
    std::cout << " Flight Number : " << flightNumber << "\n";
    std::cout << " Status        : " << flightStatus << "\n";
    std::cout << " Route         : " << origin << " -> " << destination << "\n";
    std::cout << " Date          : " << departureDate << "\n";
    std::cout << " Departure     : " << departureTime << "\n";
    std::cout << " Duration      : " << duration << " mins\n";

    if (hoursDelay > 0 || minsDelay > 0) {
        std::cout << " Delay         : " << hoursDelay << "h " << minsDelay << "m\n";
    }

    std::cout << "----------------------------------------\n";
    std::cout << " Aircraft      : " << (aircraftReference ? "Assigned" : "Not Assigned") << "\n";
    std::cout << " Crew Count    : " << crewMembersReference.size() << "\n";
    std::cout << " Reservations  : " << reservationsReference.size() << "\n";
    std::cout << " Seats Loaded  : " << seatsReference.size() << " / " << numberOfSeats << "\n";
    std::cout << "========================================\n";
}

void Flight::removeCrewMember(std::shared_ptr<CrewMember> crewMember) {
    auto it = std::find_if(crewMembersReference.begin(), crewMembersReference.end(),
        [&](const std::shared_ptr<CrewMember>& c) { return c->getId() == crewMember->getId(); });

    if (it != crewMembersReference.end()) {
        crewMembersReference.erase(it);
    }
}

void Flight::printSeatMap() const {
    std::cout << "\n=========================================\n";
    std::cout << "              FLIGHT SEAT MAP              \n";
    std::cout << "=========================================\n\n";

    int seatIndex = 0;
    
    for (int r = 1; r <= 30; ++r) {

        for (int c = 0; c < 7; ++c) {
            auto& seat = seatsReference[seatIndex++];
            
            // Print the seat number or a "-" if booked
            if (seat->getIsAvailable()) {
                std::cout << std::setw(3) << seat->getSeatNumber();
            } else {
                std::cout << std::setw(3) << "-";
            }
            
            // Insert spaces to create aisles
            if (c == 1 || c == 4) {
                std::cout << "      "; // Wide space for aisles (After B and E)
            } else {
                std::cout << " ";      // Normal space between adjacent seats
            }
        }
        std::cout << "\n"; // Next row
    }
    std::cout << "\n=========================================\n";
}

std::shared_ptr<Seat> Flight::bookSeat(const std::string& seatNumber)
{
    //Find seat
    auto it = std::find_if(seatsReference.begin(), seatsReference.end(),
                    [&](const auto& s) { return s->getSeatNumber() == seatNumber; });

    //Check if seat number found before dereferencing
    if(it == seatsReference.end())
    {
        std::cout << "Seat number not found, please try again!\n";
        return nullptr;
    }

    //Check seat availability
    if(!(*it)->getIsAvailable())
    {
        std::cout << "Seat number is already booked, please view available seats and try again!\n";
        return nullptr;
    }    
    
    //If all constraints passsed, reserve the seat safely and return a pointer to it
    (*it)->setIsAvailable(false);
    return *it;
}


void releaseSeat(std::shared_ptr<Seat> seat)
{
    //Check nullability before dereferencing
    if (seat) {
        seat->setIsAvailable(true);
    }
}