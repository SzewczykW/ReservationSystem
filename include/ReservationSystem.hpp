#ifndef RESERVATION_SYSTEM_HPP
#define RESERVATION_SYSTEM_HPP

#include "../include/Users/User.h"

class ReservationSystem {
    public:
        /**
         * @brief opening the reservation system
         */
        ReservationSystem();
        /**
         * @brief Log in to the system as a type user
         * used in ReservationSystem::ReservationSystem()
         * @return 0 as fail, 1 as success, 2 as time ban (5 min), 3 error
         */
        unsigned int login();
    private:
        User* _user;
};

#endif