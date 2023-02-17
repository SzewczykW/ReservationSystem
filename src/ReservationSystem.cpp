#include "../include/ReservationSystem.hpp"

ReservationSystem::ReservationSystem() {
    unsigned int option = 0;
    while (option != 3) {

        std::cout   << "1. Log in"
                    << "2. Register"
                    << "3. Exit"
                    << "Choose option: ";
        std::cin >> option;

        switch (option) {
            case 1:
                if (Login() == 1) {
                    std::cout << "Logged in successfully" << std::endl;
                    _IsRunning = true;
                }
                else if (Login() == 2) {
                    std::cout << "You are banned for 5 minutes\nPlease wait and try again later." << std::endl;
                    _IsRunning = false;
                    return;
                }
                else if (Login() == 3) {
                    std::cout << "Error occured\nUnable to open Reservation System\n" << std::endl;
                    _IsRunning = false;
                    return;
                }
                else if (Login() == 0) {
                    std::cout << "Login failed. Wrong login or password\nPlease try again..." << std::endl;
                    _IsRunning = false;
                }
                break;
        }
        
    }

    
}