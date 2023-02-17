#ifndef ADMIN_HPP
#define ADMIN_HPP

#include "../include/Workers/Worker.hpp"

class Admin : private User {
    public:
        /**
         * @brief Create Admin object
         * @return Pointer to Admin object
         */
        Admin* CreateAdmin ();

    private:
        /**
         * @brief Constructor for Admin object
         * which contains details about the admin
         */
        Admin ();

        /**
         * @brief Workers details
         * @param _Workers
         */
        Worker* _Workers;

        /**
        * @brief methods for adding and removing workers
        */
        void AddWorker ();
        void RemoveWorker ();
}

#endif