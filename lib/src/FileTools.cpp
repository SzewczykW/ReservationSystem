#include "FileTools.h"

char* GetStr(char* const buff, const  int buff_size, FILE* const pfile) {
    memset(buff, 0, buff_size);

    char* result = NULL;
    result = fgets(buff, buff_size, pfile);

    if (buff[0] == '\n') {
        return NULL;
    }
    if (result) {
        char* new_line = strchr(buff, '\n');
        if (new_line)
            *new_line = '\0';
        else
            while (getchar() != '\n');
    }
    return result;
}

bool TestDataFileFormat(FILE* pfile) {
    char buffer[256];
    char* token;
     int commas_per_line = 0;
    char everything_but_integrers[] = " !\"#$ % &'()*+,-./:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~"; // only numbers are allowed
    char everything_but_floats[] = " !\"#$ % &'()*+,-/:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~"; // dots and numbers is allowed
    char everything_but_alpha_paratheses[] = " !\"#$ % &'*+,-./:;<=>?@0123456789[\\]^_`{|}~"; // only letters and parentheses are allowed

    if (GetStr(buffer, 256, pfile) != NULL) {
        while (!feof(pfile) && !ferror(pfile)) {
            token = strtok(buffer, ",");
            while (token != NULL) {
                size_t token_length = strlen(token);
                switch (commas_per_line) {
                    case 0: // RoomId check (only digits are allowed)
                        if (strcspn(token, everything_but_integrers) != token_length) {
                            printf("Error: Details of rooms must be in following order : \n"
                                "RoomId, RoomType, RoomPrice, RoomStatus, OcupancyStartDate, OcupancyEndDate\n"
                                "(if the room is available, the OcupancyStartDate and OcupancyEndDate fields must be equal to 0)\n"
                                "Error: RoomId must be a integrer\n");
                            return false;
                        }
                        break;
                    case 1: // RoomType check (only letters and parentheses are allowed)
                        if (strcspn(token, everything_but_alpha_paratheses) != token_length) {
                            printf("Error: Details of rooms must be in following order : \n"
                                "RoomId, RoomType, RoomPrice, RoomStatus, OcupancyStartDate, OcupancyEndDate\n"
                                "(if the room is available, the OcupancyStartDate and OcupancyEndDate fields must be equal to 0)\n"
                                "Error: RoomType must be a word not containing any special characters (except parentheses) and numbers\n");
                            return false;
                        }
                        break;
                    case 2: // RoomPrice check (only dots and digits are allowed)
                        if (strcspn(token, everything_but_floats) != token_length) {
                            printf("Error: Details of rooms must be in following order : \n"
                                "RoomId, RoomType, RoomPrice, RoomStatus, OcupancyStartDate, OcupancyEndDate\n"
                                "(if the room is available, the OcupancyStartDate and OcupancyEndDate fields must be equal to 0)\n"
                                "Error: RoomPrice must be a float\n");
                            return false;
                        }
                        break;
                    case 3: // RoomStatus check (only letters and parentheses are allowed)
                        if (strcspn(token, everything_but_alpha_paratheses) != token_length) {
                            printf("Error: Details of rooms must be in following order : \n"
                                "RoomId, RoomType, RoomPrice, RoomStatus, OcupancyStartDate, OcupancyEndDate\n"
                                "(if the room is available, the OcupancyStartDate and OcupancyEndDate fields must be equal to 0)\n"
                                "Error: RoomStatus must be a word not containing any special characters (except parentheses) and numbers\n");
                            return false;
                        }
                        break;
                    case 4: // OcupancyStartDate check (only digits are allowed)
                        if (strcspn(token, everything_but_integrers) != token_length) {
                            printf("Error: Details of rooms must be in following order : \n"
                                "RoomId, RoomType, RoomPrice, RoomStatus, OcupancyStartDate, OcupancyEndDate\n"
                                "(if the room is available, the OcupancyStartDate and OcupancyEndDate fields must be equal to 0)\n"
                                "Error: OcupancyStartDate must be a integrer\n");
                            return false;
                        }
                        break;
                    case 5: // OcupancyEndDate check (only digits are allowed)
                        if (strcspn(token, everything_but_integrers) != token_length) {
                            printf("Error: Details of rooms must be in following order : \n"
                                "RoomId, RoomType, RoomPrice, RoomStatus, OcupancyStartDate, OcupancyEndDate\n"
                                "(if the room is available, the OcupancyStartDate and OcupancyEndDate fields must be equal to 0)\n"
                                "Error: OcupancyEndDate must be a integrer\n");
                            return false;
                        }
                        break;
                    default: // if there are more than 6 fields (commas) in a line then the file format is invalid
                        printf("Error: Invalid file format (only CSV files are allowed)\n");
                        return false;
                }
                token = strtok(NULL, ",");
                commas_per_line++;
            }
            commas_per_line = 0; // reset the counter for the next line
            if (GetStr(buffer, 256, pfile) != NULL) { // read the next line
                continue;
            }
            else { // if the file has ended then the format is valid
                break;
            }
        }
    }

    rewind(pfile); // reset the file pointer to the beginning of the file

    return true;
}

FILE* OpenFile(const char* const file_name, const char* const mode) {
    FILE* pfile = fopen(file_name, mode);
    if ( pfile == NULL ) {
        printf("Error: Could not open file %s\n", file_name);
        exit(EXIT_FAILURE);
    }

    rewind(pfile);

    if (TestDataFileFormat(pfile) == false) {
        exit(EXIT_FAILURE);
    }

    rewind(pfile);

    return pfile;
}

bool CloseFile(FILE* pfile)
{
    if (fclose(pfile) != 0) {
        printf("Error: Could not close the file\n");
        return false;
    }
    return true;
}