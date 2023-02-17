#ifndef WORKER_HPP
#define WORKER_HPP

#include "../include/Users/User.hpp"

class Worker : protected User {
    public:

        Worker();

    protected:

        /**
         * @brief Users and reservations details
         * @param Reservations, Users
         */
        Reservation* _Reservations;
        User* _Users;

        /**
         * @brief methods for adding, removing and banning users
         *
         */
        void AddUser();
        void RemoveUser();
        void BanUser();

        /**
         * @brief methods for adding, removing and editing reservations
         *
         */
        void AddReservation();
        void RemoveReservation();
        void EditReservation();
};

#endif