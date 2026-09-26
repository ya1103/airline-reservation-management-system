#include "BookingAgent.hpp"
#include "UserManager.hpp"
#include <iostream>

void BookingAgent::showMenu()
{

}


std::shared_ptr<Passenger> BookingAgent::getPassengerByID(int passengerID)
{
    auto manager = allUsersReference.lock();

    //Check nullability before dereferencing
    if (!manager) {
        std::cout << "No user manager reference found!\n";
        return nullptr;
    }

    //Fetch passanger pointer
    auto passenger = manager->findPassengerByID(passengerID);
    //Retrun nevertheless what pointer holds
    //Caller should check the returned pointer
    return passenger;
}
