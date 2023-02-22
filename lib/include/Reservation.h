#ifndef RESERVATIONS_H
#define RESERVATIONS_H

#include <cstdio>

#define RESERVATION_STATUS_AVAILABLE "Available"
#define RESERVATION_STATUS_RESERVED "Reserved"
#define RESERVATION_STATUS_OCCUPIED "Occupied"

class Reservation {
    public:
        //static Reservation* MakeReservation( int UserId,  int RoomId);
        static Reservation* MakeReservation( int UserId,  int RoomId, FILE *pFile);
        /**
         * @brief Getter methods for reservation details
         */
        int GetUserId() const              { return _UserId; }
        int GetRoomId() const              { return _RoomId; }
        int GetStartDate() const           { return _StartDate; }
        int GetEndDate() const             { return _EndDate; }
        int GetPrice() const               { return _Price; }
        char* GetStatus() const              { return _Status; }
        char* GetType() const                { return _Type; }
        static int GetPrice( int RoomId, FILE* pFile);
        static char* GetType( int RoomId, FILE* pFile);

        /**
         * @brief Setter methods for reservation details
         */ 
        void SetUserId( int UserId)         { _UserId = UserId; }
        void SetRoomId( int RoomId)         { _RoomId = RoomId; }
        void SetStartDate( int StartDate)   { _StartDate = StartDate; }
        void SetEndDate( int EndDate)       { _EndDate = EndDate; }
        void SetPrice( int Price)           { _Price = Price; }
        void SetStatus( char* Status)         { _Status = Status; }
        void SetType( char* Type)             { _Type = Type; }

    private:
        /**
        *@brief Constructor for Reservation object
        * which contains informations about the reservation
        */
        Reservation(
            int UserId,
            int RoomId,
            int StartDate,
            int EndDate,
            int Price,
            char* Status,
            char* Type
        ): _UserId(UserId), _RoomId(RoomId), _StartDate(StartDate),
            _EndDate(EndDate), _Price(Price), _Status(Status), _Type(Type) {}
        /**
         * @brief Reservation details
         * @param _UserId, _RoomId, _StartDate, _EndDate, _Price, _Status, _Type
         */
        int _UserId;
        int _RoomId;
        int _StartDate;
        int _EndDate;
        int _Price;
        char* _Status;
        char* _Type;
};

#endif