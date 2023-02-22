#include "ReservationSystem.h"
#include "GetRootProjectPath.h"

ReservationSystem::ReservationSystem() {
    _pFile = OpenFile(DATA_PATH, "rb");
}

void ReservationSystem::PrintAvailableRooms() {
    char buffer[256];
    char room_id[10];
     int count = 0;

    if (GetStr(buffer, 256, _pFile) != NULL) {
        while (!feof(_pFile) && !ferror(_pFile)) {
            if (strstr(buffer, RESERVATION_STATUS_AVAILABLE) != NULL) {
                char* first_comma = static_cast<char*> (memchr(buffer, ',', 10));

                int room_id_length = first_comma - buffer; // get the length of the room id

                memcpy(room_id, buffer, room_id_length);
                room_id[room_id_length] = '\0'; // null terminate the string

                fputs(room_id, stdout);
                fputc('\t', stdout);
                if (count++ % 10 == 9)
                {
                    fputc('\n', stdout);
                }
            }
            if (GetStr(buffer, 256, _pFile) != NULL) { // get the next line
                continue;
            }
            else { // if we reached the end of the file
                break;
            }
        }
    }
    if (count % 10 != 9) {
        fputc('\n', stdout);
    }

    rewind(_pFile);
}

FILE* ReservationSystem::GetFilePointer() {
    return _pFile;
}

void ReservationSystem::SetFilePointer(const char* const file_name, const char* const mode) {
    _pFile = OpenFile(file_name, mode);
}