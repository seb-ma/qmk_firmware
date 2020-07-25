#ifdef USER_CLOSE_CHAR
#include "keymap_bepo.h"

#include "user_feature_closechar.h"
#include "user_feature_nbsp.h"

/* List of close char related to the open ones */
static uint16_t close_char[MAX_CLOSE_CHAR];
/* Index of first close char to output */
static int8_t index_close_char = -1;

_Static_assert(MAX_CLOSE_CHAR <= 128, "Variable index_close_char must be declared on > 8 bits (int16_t)");

/* Structure of association between open char and close char */
typedef struct {
    const uint16_t open;
    const uint16_t close;
} close_char_map_t;

/* List of association between open char and close char */
const close_char_map_t close_char_map[] = {
    {BP_DQUO, BP_DQUO}, // ""
    {BP_LDAQ, BP_RDAQ}, // «»
    {BP_LPRN, BP_RPRN}, // ()
    {BP_LCBR, BP_RCBR}, // {}
    {BP_LBRC, BP_RBRC}, // []
};

/* Handle the keys corresponding to an opening char: "(«[{
 Return the key itself or the first closing key if this is the special close key
*/
uint16_t handle_open_close_char(const uint16_t keycode, const bool ignore_mods, const keyrecord_t *const record, const uint16_t previous_keycode) {
    if (record->event.pressed) {
        if (keycode == C_CLOSE_CHAR_CLEAR) {
            // Clear buffer
            index_close_char = -1;
            return C_DUMMY;
        } else if (keycode == C_CLOSE_CHAR && index_close_char >= 0) {
            // Get the last related close char
#ifdef USER_ADDING_NBSP
            return handle_adding_non_breaking_space(close_char[index_close_char--], true, record);
#else
            return close_char[index_close_char--];
#endif
        } else {
            const uint16_t keycode_mods = ignore_mods ? keycode : get_keycode_with_mods_applied(keycode);
            if (keycode != C_CLOSE_CHAR && index_close_char >= 0 && keycode_mods == close_char[index_close_char]) {
                // If the close char was manually tapped, remove it
                index_close_char--;
                return keycode;
            } else if (keycode == KC_BSPACE && index_close_char > -1) {
                // If the open char was a mistake (backspaced), remove the last close char
                for (uint8_t i = 0; i < sizeof(close_char_map) / sizeof(close_char_map_t); i++) {
                    if (close_char_map[i].open == previous_keycode && close_char_map[i].close == close_char[index_close_char]) {
                        index_close_char--;
                        return keycode;
                    }
                }
            } else if (index_close_char < MAX_CLOSE_CHAR - 2) {
                // If this is an open char, store the related close char
                for (uint8_t i = 0; i < sizeof(close_char_map) / sizeof(close_char_map_t); i++) {
                    if (close_char_map[i].open == keycode_mods) {
                        close_char[++index_close_char] = close_char_map[i].close;
                        break;
                    }
                }
            }
        }
    } else if (keycode == C_CLOSE_CHAR) {
        return close_char[index_close_char + 1];
    }
    return keycode;
}

#endif // USER_CLOSE_CHAR
