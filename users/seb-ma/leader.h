#pragma once
#ifdef LEADER_ENABLE
#include QMK_KEYBOARD_H

/* Leader keys definitions
 To be called in matrix_scan_user
*/
void handle_leader_key(void);

/* Max number of characters to describe a sequence */
#define SIZE_NAME_LEADER_SEQUENCE 10

/* Definition of a leader sequence state */
typedef struct {
    uint16_t timer;
    bool     is_success;
    char     name[SIZE_NAME_LEADER_SEQUENCE];
} t_leader_state;

/* State of leader sequence */
extern t_leader_state leader_state;

#endif // LEADER_ENABLE
