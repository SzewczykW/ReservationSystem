#ifndef RESERVATIONS_H
#define RESERVATIONS_H

#define RESERVATION_STATUS_AVAILABLE "Available"
#define RESERVATION_STATUS_RESERVED "Reserved"
#define RESERVATION_STATUS_OCCUPIED "Occupied"

class Reservation {
    public:
        /**
        *@brief Constructor for Reservation object
        * which contains informations about the reservation
        */
        Reservation(
            unsigned int UserId,
            unsigned int RoomId,
            unsigned int StartDate,
            unsigned int EndDate,
            unsigned int Price,
            unsigned int Status,
            unsigned int Type
        ): _UserId(UserId), _RoomId(RoomId), _StartDate(StartDate),
        _EndDate(EndDate), _Price(Price), _Status(Status), _Type(Type){}
        /**
         * @brief Getter methods for reservation details
         */
        unsigned int GetUserId() const              { return _UserId; }
        unsigned int GetRoomId() const              { return _RoomId; }
        unsigned int GetStartDate() const           { return _StartDate; }
        unsigned int GetEndDate() const             { return _EndDate; }
        unsigned int GetPrice() const               { return _Price; }
        unsigned int GetStatus() const              { return _Status; }
        unsigned int GetType() const                { return _Type; }

        /**
         * @brief Setter methods for reservation details
         */ 
        void SetUserId(unsigned int UserId)         { _UserId = UserId; }
        void SetRoomId(unsigned int RoomId)         { _RoomId = RoomId; }
        void SetStartDate(unsigned int StartDate)   { _StartDate = StartDate; }
        void SetEndDate(unsigned int EndDate)       { _EndDate = EndDate; }
        void SetPrice(unsigned int Price)           { _Price = Price; }
        void SetStatus(unsigned int Status)         { _Status = Status; }
        void SetType(unsigned int Type)             { _Type = Type; }

    private:
        /**
         * @brief Reservation details
         * @param _UserId, _RoomId, _StartDate, _EndDate, _Price, _Status, _Type
         */
        unsigned int _UserId;
        unsigned int _RoomId;
        unsigned int _StartDate;
        unsigned int _EndDate;
        unsigned int _Price;
        unsigned int _Status;
        unsigned int _Type;
};

#endif