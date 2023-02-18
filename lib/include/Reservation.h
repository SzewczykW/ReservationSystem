#ifndef RESERVATIONS_H
#define RESERVATIONS_H

class Reservation {
    public:   
        static Reservation MakeReservation(void);
        static void PrintAvailableRooms();
        
        /**
         * @brief Getter methods for reservation details
         */
        unsigned int GetUserId() const;
        unsigned int GetRoomId() const { return _RoomId;}
        unsigned int GetStartDate() const;
        unsigned int GetEndDate() const;
        unsigned int GetPrice() const;
        unsigned int GetStatus() const;
        unsigned int GetType() const;

        /**
         * @brief Setter methods for reservation details
         */ 
        void SetUserId(unsigned int UserId);
        void SetRoomId(unsigned int RoomId);
        void SetStartDate(unsigned int StartDate);
        void SetEndDate(unsigned int EndDate);
        void SetPrice(unsigned int Price);
        void SetStatus(unsigned int Status);
        void SetType(unsigned int Type);

    private:
        /**
         * @brief Constructor for Reservation object
         * which contains informations about the reservation
         */
        Reservation (
            unsigned int UserId,
            unsigned int RoomId,
            unsigned int StartDate,
            unsigned int EndDate,
            unsigned int Price,
            unsigned int Status,
            unsigned int Type,
            unsigned int Size
        ) : _UserId(UserId), _RoomId(RoomId), _StartDate(StartDate), 
            _EndDate(EndDate), _Price(Price), _Status(Status), _Type(Type), _Size(Size) {}

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
};

#endif