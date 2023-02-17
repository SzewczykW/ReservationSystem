#ifndef USER_HPP
#define USER_HPP

#include <string>
#include "../include/Reservations/Reservations.hpp"

class User {
    public:
        /**
         * @brief Create User object
         * @return Pointer to User object
         */
        User* CreateUser ();
    protected:
        /**
         * @brief Constructor for User object 
         * which contains details about the user
         */
        User ();

        /**
         * @brief User details
         * @param _Id, _Name, _Surname, _PhoneNumber, _Login, _Email, _Password
         */
        unsigned int _Id;
        std::string _Name;
        std::string _Surname;
        std::string _PhoneNumber;
        std::string _Login;
        std::string _Email;
        std::string _Password;

        /**
         * @brief Getter methods for user details
         * login, email, phone number can be only provided
         * if password is provided or user is at least worker
         */
        unsigned int GetId () const;
        std::string GetName () const;
        std::string GetSurname () const;
        std::string GetPhoneNumber () const;
        std::string GetLogin () const;
        std::string GetPassword () const;
        std::string GetEmail () const;

        /**
         * @brief Editing user details can be done by user itself
         * only if password is provided
         * or if user is at least worker
         */
        void EditName ();
        void EditSurname ();
        void EditPhoneNumber ();
        void EditLogin ();
        void EditEmail ();
        void EditPassword ();

    private:

        /**
         * @brief Reservation object which contains details about user reservation
         * @param _Reservation
         */
        Reservation* _Reservation;
};

#endif