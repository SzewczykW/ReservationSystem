#ifndef RESERVATION_SYSTEM_HPP
#define RESERVATION_SYSTEM_HPP

#include "../include/Users/User.hpp"

class ReservationSystem {
    public:

        /**
         * @brief Construct a ReservationSystem object
         * which contains informations about the user
         */
        ReservationSystem ();

        /**
         * @brief Log in to the system as a type user
         * used in ReservationSystem::ReservationSystem ()
         * @return 0 as fail, 1 as success, 2 as time ban (5 min), 3 error
         */
        unsigned int Login ();

        /**
         * @brief Register to the system as a type user
         * used in ReservationSystem::ReservationSystem ()
         * @return 0 as fail, 1 as success, 2 error, 3 as user already exists
         */
        unsigned int Register ();
    private:
        union{
            User* _User;
            Worker* _Worker;
            Admin* _Admin;
        }
        bool _IsRunning;
};

#endif