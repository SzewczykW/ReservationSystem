#ifndef RESERVATIONS_H
#define RESERVATIONS_H

class Reservation {
    public:
        Reservation();
    private:
        /**
         * @brief Reservation details
         * @param UserId, RoomId, StartDate, EndDate, Price, Status, Type, Size
         */
        unsigned int UserId;
        unsigned int RoomId;
        unsigned int StartDate;
        unsigned int EndDate;
        unsigned int Price;
        unsigned int Status;
        unsigned int Type;
        unsigned int Size;

        /**
         * @brief Getter methods for reservation details
         */
        unsigned int GetUserId() const;
        unsigned int GetRoomId() const;
        unsigned int GetStartDate() const;
        unsigned int GetEndDate() const;
        unsigned int GetPrice() const;
        unsigned int GetStatus() const;
        unsigned int GetType() const;
        unsigned int GetSize() const;
};


Reservation* MakeReservation();

#endif