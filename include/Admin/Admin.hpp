#ifndef ADMIN_HPP
#define ADMIN_HPP

#include "../include/Users/User.hpp"
#include "../include/Workers/Worker.hpp"

class Admin : private User {
    public:
        Admin();
    private:
        /**
         * @brief Workers details
         * @param Workers
         */
        Worker* _Workers;

        /**
        * @brief methods for adding and removing workers
        */
        void AddWorker();
        void RemoveWorker();
}

#endif