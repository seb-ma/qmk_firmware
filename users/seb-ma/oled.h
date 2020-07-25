#pragma once
#ifdef OLED_DRIVER_ENABLE
#include QMK_KEYBOARD_H

/* MIN and MAX functions exist somewhere in QMK tree and may or may not be defined according to enabled features */
#ifndef MIN
#   define MIN(X, Y) ((X) < (Y) ? (X) : (Y))
#endif
#ifndef MAX
#   define MAX(X, Y) ((X) > (Y) ? (X) : (Y))
#endif


/* Check if this is a custom rgb key and process it if true
 (To be called in process_record_user)
*/
bool handle_oled(const uint16_t keycode, keyrecord_t *const record);

#if !defined(MASTER_ONLY) && (defined(BONGOCAT_ANIMATION) || defined(LIFE_ANIMATION) || defined(POMODORO_ANIMATION) || defined(ONEKO_ANIMATION))
#   define RENDER_ANIMATIONS
#endif

#ifdef RENDER_ANIMATIONS
/* Definition of the animation */
typedef struct {
    uint32_t start_timer;
    uint16_t frame_duration;
    int16_t  ratioPerc;
} t_animation;

/* Declaration of the animation */
extern t_animation animation;

/* Callback to render the first frame of the animation */
typedef void (*render_init_frame_fct)(t_animation*);

/* Callback to render the next frame of the animation */
typedef void (*render_next_frame_fct)(t_animation*);

/* Declaration of bongocat renderers */
#   ifdef BONGOCAT_ANIMATION
    void bongocat_render_init_frame(t_animation* animation);
    void bongocat_render_next_frame(t_animation* animation);
#   endif
/* Declaration of lifegame renderers */
#   ifdef LIFE_ANIMATION
    void gamelife_render_init_frame(t_animation* animation);
    void gamelife_render_next_frame(t_animation* animation);
#   endif
#   ifdef POMODORO_ANIMATION
    void pomodoro_render_init_frame(t_animation* animation);
    void pomodoro_render_next_frame(t_animation* animation);
#   endif
#   ifdef ONEKO_ANIMATION
    void oneko_render_init_frame(t_animation* animation);
    void oneko_render_next_frame(t_animation* animation);
#   endif

#else // RENDER_ANIMATIONS

// Define a fake type of render_init_frame_fct only to have a count of number of animations
typedef void (*render_init_frame_fct)(uint8_t*);

#endif // RENDER_ANIMATIONS

#endif // OLED_DRIVER_ENABLE
