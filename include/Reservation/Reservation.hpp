#ifndef RESERVATIONS_H
#define RESERVATIONS_H

class Reservation {
    public:
        /**
         * @brief Create Reservation object
         * @return Pointer to Reservation object
         */
        Reservation* CreateReservation ();
    private:
        /**
         * @brief Constructor for Reservation object
         * which contains informations about the reservation
         */
        Reservation ();

        /**
         * @brief Reservation details
         * @param _UserId, _RoomId, _StartDate, _EndDate, _Price, _Status, _Type, _Size
         */
        unsigned int _UserId;
        unsigned int _RoomId;
        unsigned int _StartDate;
        unsigned int _EndDate;
        unsigned int _Price;
        unsigned int _Status;
        unsigned int _Type;
        unsigned int _Size;

        /**
         * @brief Getter methods for reservation details
         */
        unsigned int GetUserId () const;
        unsigned int GetRoomId () const;
        unsigned int GetStartDate () const;
        unsigned int GetEndDate () const;
        unsigned int GetPrice () const;
        unsigned int GetStatus () const;
        unsigned int GetType () const;
        unsigned int GetSize () const;
};

#endif