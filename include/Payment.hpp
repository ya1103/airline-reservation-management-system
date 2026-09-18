#ifndef PAYMENT_HPP
#define PAYMENT_HPP

#include <string>
#include <memory>

//forward declaration
class Reservation;

class Payment{
    private:
        std::string id;
        double amount;
        std::string method;
        std::string status;
        std::weak_ptr<Reservation> reservationReference;
    public:

        //Parameterized constructor
        Payment(std::shared_ptr<Reservation> pointerToReservation, const double& amountToBeDeducted, const std::string& paymentMethod)
            : id("N/A"), amount(amountToBeDeducted), method(paymentMethod), status("Pending"),
            reservationReference(pointerToReservation) {}

        //function which will start payment process and update status and returns it to caller
        std::string process(double amountToBeDeducted, const std::string& method);

        //function which starts refund process and update status and returns it to caller
        std::string refund(void);
};

#endif
