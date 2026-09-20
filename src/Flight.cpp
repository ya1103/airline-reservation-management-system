#include "Flight.hpp"
#include "CrewMember.hpp"
#include "Aircraft.hpp"
#include "Seat.hpp"
#include "Reservation.hpp"
#include "algorithm"
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

//Remover: Removes crew member from this flight
void Flight::removeCrewMember(std::shared_ptr<CrewMember> targetCrewMember){
    auto iterator = std::find_if(crewMembersReference.begin(), crewMembersReference.end(),
        [&targetCrewMember](const std::shared_ptr<CrewMember>& cm){
            return targetCrewMember == cm;
    });

    if(iterator != crewMembersReference.end()){
        crewMembersReference.erase(iterator);
        targetCrewMember->removeFlight(shared_from_this());
        //when removed successfully return
        std::cout << "Crew member removed from flight successfully";
        return;
    }
    std::cout << "\nCrew member is not assigned to flight, please try again!\n";
    return;
}   