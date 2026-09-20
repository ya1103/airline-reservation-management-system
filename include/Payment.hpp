#ifndef PAYMENT_HPP
#define PAYMENT_HPP

#include <string>
#include <memory>
#include <DateUtils.hpp>

//forward declaration
class Reservation;

class Payment{
    private:
        int id;
        inline static int nextID = 1;
        double amount;
        std::string method;
        std::string status;
        std::string paymentDate;
        std::weak_ptr<Reservation> reservationReference;
    public:

        //Parameterized constructor ONLY for creating new payments
        Payment(std::shared_ptr<Reservation> pointerToReservation, double amountToBeDeducted, std::string paymentMethod)
            :  Payment(nextID++, pointerToReservation, amountToBeDeducted, DateUtils::getCurrentDate(), std::move(paymentMethod), "Pending"){}
        
        //Parameterized constructor ONLY for rebuilding existing payments from memory during program startup
        Payment(int passedID, std::shared_ptr<Reservation> pointerToReservation, double amountToBeDeducted,
            std::string date, std::string paymentMethod, std::string status)
            : id(passedID), amount(amountToBeDeducted), method(std::move(paymentMethod)), status(std::move(status)),
                paymentDate(std::move(date)), reservationReference(pointerToReservation) {}
        //function which will start payment process and update status and returns it to caller
        std::string process(double amountToBeDeducted, const std::string& method);

        //function which starts refund process and update status and returns it to caller
        std::string refund(void);
};

#endif
