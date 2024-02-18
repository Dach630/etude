#include "cassini.h"

int print_reply(const char* resp, uint16_t operation) {

    int reply = -1;
    reply = open(resp, O_RDONLY); //open reply
    if (reply == -1) {
        perror("open reply");
        return(1);
    }

    size_t rd = 0;
    uint16_t repType;
    rd = read(reply, &repType, sizeof(uint16_t)); // repType reply
    if (rd < 1) {
        perror("read reply");
        goto error;
    }

    switch (operation) {
        case CLIENT_REQUEST_LIST_TASKS:
        {
            if (be16toh(repType) == SERVER_REPLY_OK) {
                uint32_t nbTask = 0;
                uint64_t taskId;
                int rdTime;
                uint32_t nbString = 0;
                uint32_t lenString;
                uint64_t min;
                uint32_t h;
                uint8_t days;
                struct timing *time = malloc(sizeof(struct timing));
                if (time == NULL) {
                    perror("malloc");
                    goto error;
                }
                char *dest = malloc(TIMING_TEXT_MIN_BUFFERSIZE + 1);
                if (dest == NULL) {
                    perror("malloc");
                    free(time);
                    goto error;
                }
                unsigned char* buf = malloc(1025);
                if (buf == NULL) {
                    perror("malloc");
                    free(dest);
                    free(time);
                    goto error;
                }
                char* temp = malloc(1025);
                if (temp == NULL) {
                    perror("malloc");
                    free(dest);
                    free(time);
                    free(buf);
                    goto error;
                }
                rd = read(reply, &nbTask, sizeof(uint32_t));
                if (rd < 1) {
                    perror("read reply");
                    goto errorLS;
                }
                int n = be32toh(nbTask);
    	        for (int i = 0; i < n; i += 1){
                    rd = read(reply, &taskId, sizeof(uint64_t));
                    if (rd < 1) {
                        perror("read ");
                        goto errorLS;
                    }
                    printf("%ld: ", be64toh(taskId));
                    rd = read(reply, &min, sizeof(uint64_t));
                    if (rd < 1) {
                        perror("read");
                        goto errorLS;
                    }
                    rd = read(reply, &h, sizeof(uint32_t));
                    if (rd < 1) {
                        perror("read");
                        goto errorLS;
                    }
                    rd = read(reply, &days, sizeof(uint8_t));
                    if (rd < 1) {
                        perror("read");
                        goto errorLS;
                    }
                    time->minutes = be64toh(min);
                    time->hours = be32toh(h);
                    time->daysofweek = days;
                    rdTime = timing_string_from_timing(dest, time);
                    if (rdTime < 1) {
                        perror("timing_string_from_timing");
                        goto errorLS;
                    }
                    printf("%s", dest);
                    read(reply, &nbString, sizeof(uint32_t));
                    if (rd < 1) {
                        perror("read");
                        goto errorLS;
                    }
                    int m = be32toh(nbString);
                    char ch;
    		        for (int j = 0; j < m; j += 1) {
                        read(reply, &lenString, sizeof(uint32_t));
                        if (rd < 1) {
                            perror("read");
                            goto errorLS;
                        }
    		            printf(" ");
                        int k = be32toh(lenString);
                        for (int i = 0; i < k; i += 1) {
                            rd = read(reply, &ch, sizeof(uint8_t));
                            if (rd < 1) {
                                perror("read");
                                goto error;
                            }
                            printf("%c", (ch));
                        }
                    }
    		        printf("\n");
                }
                free(dest);
                free(buf);
                free(time);
                free(temp);
                break;
            errorLS: {
                free(dest);
                free(buf);
                free(time);
                free(temp);
                goto error;
                }
            }
            else{
                goto error;
            }
            break;
        }
        case CLIENT_REQUEST_CREATE_TASK:
        {
            if (be16toh(repType) == SERVER_REPLY_OK) {
            uint64_t taskId = 0;
                rd = read(reply, &taskId, sizeof(uint64_t));
                if (rd < 1) {
                    perror("read");
                    goto error;
                }
                printf("%u\n", (unsigned int)be64toh(taskId));
            }
            else {
                goto error;
            }
            break;
        }
        case CLIENT_REQUEST_REMOVE_TASK:
        {
            switch (be16toh(repType)) {
                case SERVER_REPLY_OK: {
                    break;
                }
                case SERVER_REPLY_ERROR: {
                    rd = read(reply, &repType, sizeof(uint16_t));
                    if (rd < 1) {
                        goto error;
                    }
                    uint16_t er = be16toh(repType);
                    if (er == SERVER_REPLY_ERROR_NOT_FOUND) {
                        printf("ER, %u \n", er);
                    }
                    else {
                        goto error;
                    }
                    break;
                }
                default:
                    goto error;
                }
    	    break;
        }
        case CLIENT_REQUEST_GET_TIMES_AND_EXITCODES:
        {
            switch (be16toh(repType)) {
                case SERVER_REPLY_OK: {
    	            uint32_t nbRun;
    	            int64_t reply_time;
                	  uint16_t ex;
                	  rd = read(reply, &nbRun, sizeof(uint32_t));
                	  if (rd < 1) {
                	    perror("read");
                        goto error;
                	  }
                    int n = be32toh(nbRun);
                    for (int i = 0; i < n; i += 1) {
                        rd = read(reply, &reply_time, sizeof(int64_t));
                	    if (rd < 1) {
                	      perror("read");
                	      goto error;
                	    }
                	    
            	    time_t timestamp = (time_t) be64toh(reply_time);
            	    struct tm * now = localtime(&timestamp);
            	    
            	    printf( "%4d-%02d-%02d %02d:%02d:%02d ",
            		    now->tm_year+1900, now->tm_mon+1, now->tm_mday,
            		    now->tm_hour, now->tm_min, now->tm_sec);
            	    rd = read(reply, &ex, sizeof(uint16_t));
            	    if (rd < 1) {
            	      perror("read");
            	      goto error;
            	    }
            	    printf("%d\n", be16toh(ex));
                }
                break;
            }
            case SERVER_REPLY_ERROR: {
                rd = read(reply, &repType, sizeof(uint16_t));
                if (rd < 1) {
                    goto error;
                }
                uint16_t er = be16toh(repType);
                if (er == SERVER_REPLY_ERROR_NOT_FOUND) {
                    printf("ER, %u \n", er);
                }
                else {
                    goto error;
                }
        	    goto error;
                    break;
            }
            default:
                goto error;
            }
    	    break;
        }
        case CLIENT_REQUEST_TERMINATE:
        {
            if (be16toh(repType) != SERVER_REPLY_OK) {
                goto error;
            }
            break;
        }
        case CLIENT_REQUEST_GET_STDOUT:
        {
            switch (be16toh(repType)) {
                case SERVER_REPLY_OK: {
                    uint32_t len;
                    rd = read(reply, &len, sizeof(uint32_t));
                    if (rd < 1) {
                        perror("read");
                        goto error;
                    }
                    int n = be32toh(len);
                    uint8_t ch;
                    for (int i = 0; i < n; i += 1) {
                        rd = read(reply, &ch, sizeof(uint8_t));
                        if (rd < 1) {
                            perror("read");
                            goto error;
                        }
                        printf("%c", (ch));
                    }
                    break;
        	    }
                case SERVER_REPLY_ERROR: {
                    rd = read(reply, &repType, sizeof(uint16_t));
                    if (rd < 1) {
                        goto error;
                    }
                    uint16_t er = be16toh(repType);
                    if (er == SERVER_REPLY_ERROR || er == SERVER_REPLY_ERROR_NOT_FOUND) {
                        printf("ER, %u \n", er);
                    }
                    else {
                        goto error;
                    }
                    break;
                }
                default:
                    goto error;
            }
            break;
        }
        case CLIENT_REQUEST_GET_STDERR:
        {
            switch (be16toh(repType)) {
                case SERVER_REPLY_OK: {
                     uint32_t len;
                    rd = read(reply, &len, sizeof(uint32_t));
                    if (rd < 1) {
                        perror("read");
                        goto error;
                    }
                    int n = be32toh(len);
                    uint8_t ch;
                    for (int i = 0; i < n; i += 1) {
                        rd = read(reply, &ch, sizeof(uint8_t));
                        if (rd < 1) {
                            perror("read");
                            goto error;
                        }
                        printf("%c", (ch));
                    }
                    break;
        	    }
                case SERVER_REPLY_ERROR: {
                    rd = read(reply, &repType, sizeof(uint16_t));
                    if (rd < 1) {
                        goto error;
                    }
                    uint16_t er = be16toh(repType);
                    if (er == SERVER_REPLY_ERROR || er == SERVER_REPLY_ERROR_NOT_FOUND) {
                        printf("ER, %u \n", er);
                    }
                    else {
                        goto error;
                    }
                    break;
                }
                default:
                    goto error;
                }
                break;
            }
            default:
                goto error;
        }

    if (close(reply) == -1) {
        perror("close");
        return 1;
    }
    return(0);

    error:
        close(reply);
        return(1);
}
