#ifndef WORKER_HPP
#define WORKER_HPP

#include "../include/Users/User.hpp"

class Worker : protected User {
    public:
        /**
         * @brief Create Worker object
         * @return Pointer to Worker object
         */
        Worker* CreateWorker ();

    protected:
        /**
         * @brief Constructor for Worker object 
         * which contains details about the worker
         */
        Worker ();

        /**
         * @brief Users and reservations details
         * @param _Reservations, _Users
         */
        Reservation* _Reservations;
        User* _Users;

        /**
         * @brief methods for adding, removing and banning users
         */
        void AddUser ();
        void RemoveUser ();
        void BanUser ();

        /**
         * @brief methods for adding, removing and editing reservations
         */
        void AddReservation ();
        void RemoveReservation ();
        void EditReservation ();
};



#endif