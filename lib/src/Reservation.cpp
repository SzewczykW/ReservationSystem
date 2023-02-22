#include "Reservation.h"
#include "FileTools.h"

int Reservation::GetPrice(int RoomId, FILE* pFile)
{
    char buffer[256];
    char room_id[10];
    int price;
    if (GetStr(buffer, 256, pFile) != NULL)
    {
        while (!feof(pFile) && !ferror(pFile))
        {
            char* first_comma = static_cast<char*> (memchr(buffer, ',', 10));
            int room_id_length = first_comma - buffer; // get the length of the room id
            memcpy(room_id, buffer, room_id_length);
            room_id[room_id_length] = '\0'; // null terminate the string
            if (atoi(room_id) == RoomId)
            {
                char* second_comma = static_cast<char*> (memchr(first_comma + 1, ',', 10));
                char* third_comma = static_cast<char*> (memchr(second_comma + 1, ',', 10));
                char price_str[7];
                size_t price_length = third_comma - second_comma - 1;
                memcpy(price_str, second_comma + 1, price_length);;
                price_str[price_length] = '\0';
                price = atoi(price_str);
                rewind(pFile);
                return price;
            }

            if (GetStr(buffer, 256, pFile) != NULL)
            { // get the next line
                continue;
            }
            else
            { // if we reached the end of the file
                break;
            }
        }
    }
    rewind(pFile);
    return 0;
}
char* Reservation::GetType(int RoomId, FILE* pFile)
{
    char buffer[256];
    char room_id[10];
    char* room_type;
    if (GetStr(buffer, 256, pFile) != NULL)
    {
        while (!feof(pFile) && !ferror(pFile))
        {
            char* first_comma = static_cast<char*> (memchr(buffer, ',', 10));
            int room_id_length = first_comma - buffer; // get the length of the room id
            memcpy(room_id, buffer, room_id_length);
            room_id[room_id_length] = '\0'; // null terminate the string
            if (atoi(room_id) == RoomId)
            {
                char* second_comma = static_cast<char*> (memchr(first_comma + 1, ',', 10));
                size_t type_length = second_comma - second_comma - 1;
                room_type = static_cast<char*> (malloc(type_length + 1));
                memcpy(room_type, second_comma + 1, type_length);;
                room_type[type_length] = '\0';
                rewind(pFile);
                return room_type;
            }

            if (GetStr(buffer, 256, pFile) != NULL)
            { // get the next line
                continue;
            }
            else
            { // if we reached the end of the file
                break;
            }
        }
    }
    rewind(pFile);
    return NULL;
}

Reservation* Reservation::MakeReservation( int UserId,  int RoomId, FILE *pFile) {
     int StartDate = 0;
     int EndDate = 0;

    while (scanf("%d", &StartDate) != 1 && StartDate < 1 && StartDate > 31) {
        printf("Invalid input. Starting date must be between 1 and 31.\n"
               "Please enter a valid date: ");
        while (getchar() != '\n');
    }

    while (scanf("%d", &EndDate) != 1 && EndDate <= StartDate && EndDate > 31) {
        printf("Invalid input. Ending date must be between Starting date and 31.\n"
               "Please enter a valid date: ");
        while (getchar() != '\n');
    }

    char* Status = static_cast<char*> (malloc(strlen(RESERVATION_STATUS_RESERVED) + 1));
    strcpy(Status, RESERVATION_STATUS_RESERVED);

    return new Reservation(UserId, RoomId, StartDate, EndDate, GetPrice(RoomId, pFile), Status, GetType(RoomId, pFile));
}