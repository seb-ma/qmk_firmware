#pragma once
#if defined(OLED_DRIVER_ENABLE) && defined(BONGOCAT_ANIMATION)

/*
Sources:
    Images:    Bongo cat: https://bongo-cat.glitch.me/
    Converter: https://javl.github.io/image2cpp/ (in Draw mode, use "Vertical - 1 bit per pixel")
    Generator: gen_bongocat.c
*/

/*--------------
  Base (paws up)
  --------------*/
// up
static const uint8_t up_idx_delta[] PROGMEM = {
     64, 116,  76,  40, 117, 129, 127,  67,  80,
};

static const uint8_t up_siz[] PROGMEM = {
      1,  29,  29,  53,  63,  65,  59,  32,  37,
};

static const char up_val[] PROGMEM = {
    0x80, 0x80, 0x80, 0xc0, 0xc0, 0xe0, 0xe0, 0xe0, 0xf0, 0xf0,
    0xf8, 0xfc, 0xff, 0xff, 0xff, 0xfe, 0xfc, 0xf8, 0xf0, 0xf0,
    0xf0, 0xf0, 0xe0, 0xe0, 0xe0, 0xc0, 0xc0, 0xc0, 0x80, 0x80,
    0x02, 0x02, 0x02, 0x02, 0x00, 0x04, 0x04, 0x04, 0x00, 0x08,
    0x08, 0x08, 0x00, 0x10, 0x10, 0x10, 0x00, 0x20, 0x20, 0x20,
    0x00, 0x40, 0x40, 0x40, 0x00, 0x80, 0x80, 0x80, 0x80, 0xfc,
    0xfe, 0xf6, 0x9e, 0xfe, 0xfc, 0xf8, 0xe0, 0xfc, 0xfe, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x3f, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xfe, 0xfe, 0xfc, 0xf8, 0xf0, 0xf0, 0xf8, 0xfc, 0xfc,
    0xfe, 0x1e, 0x01, 0x01, 0x01, 0x01, 0x00, 0x02, 0x02, 0x02,
    0x80, 0xc4, 0xe4, 0xe3, 0xe7, 0xe7, 0xc7, 0xc7, 0xcf, 0x4f,
    0x8f, 0x8f, 0x9f, 0x9f, 0x1f, 0x1f, 0x1f, 0x3f, 0x3f, 0x3f,
    0x3f, 0x7f, 0x7f, 0x7e, 0x7f, 0xfe, 0xfc, 0xf9, 0xfb, 0xfb,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe7, 0xe7, 0xff, 0x1f,
    0xf3, 0xfd, 0xf7, 0x3e, 0x3e, 0xed, 0xf9, 0xf7, 0xef, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xc3, 0x80, 0x20, 0x60, 0x68, 0x7c,
    0x5e, 0xdf, 0xdf, 0xff, 0xbf, 0xbf, 0xbf, 0x8f, 0x77, 0x7b,
    0x7c, 0x7f, 0xff, 0xff, 0x7f, 0xbf, 0xcf, 0xf7, 0xfb, 0xfc,
    0xfe, 0xfe, 0xfe, 0xfe, 0x7c, 0x9c, 0xec, 0xf0, 0xf8, 0xf8,
    0xf8, 0xf9, 0xf1, 0xf1, 0x71, 0x93, 0xe3, 0xe3, 0xe3, 0xe7,
    0xc7, 0xc6, 0xc3, 0x07, 0x8f, 0x8f, 0x8f, 0x8f, 0x1f, 0x1f,
    0x1f, 0x1f, 0x3f, 0x3f, 0x3f, 0x3f, 0x7f, 0x7f, 0x78, 0x40,
    0x0f, 0x0f, 0x0f, 0x1f, 0x1f, 0x1f, 0x1f, 0x3e, 0x3e, 0x3e,
    0x3e, 0x7c, 0x7d, 0x7d, 0x7d, 0xfd, 0xfb, 0xfb, 0xfb, 0xfa,
    0xf6, 0xf6, 0xf7, 0xf5, 0xed, 0xed, 0xef, 0xeb, 0xcb, 0xd8,
    0xdb, 0xd7, 0x97, 0xb7, 0xb7, 0xbf, 0xaf, 0x67, 0x69, 0x7e,
    0x5f, 0xdf, 0xdf, 0xff, 0xbf, 0xbf, 0xaf, 0xb3, 0x7c, 0x7f,
    0x7f, 0x7f, 0xff, 0x7f, 0x3f, 0xcf, 0x67, 0x39, 0x04, 0x01,
    0x01, 0x01, 0x00, 0x02, 0x02, 0x02, 0x00, 0x04, 0x04, 0x04,
    0x00, 0x08, 0x08, 0x08, 0x08, 0x10, 0x10, 0x10, 0x10, 0x00,
    0x20, 0x20, 0x20, 0x00, 0x40, 0x40, 0x40, 0x00, 0x80, 0x80,
    0x80, 0x01, 0x01, 0x01, 0x03, 0x03, 0x03, 0x03, 0x07, 0x07,
    0x07, 0x07, 0x0f, 0x0f, 0x0f, 0x0f, 0x1f, 0x1f, 0x1f, 0x1f,
    0x3f, 0x3f, 0x3f, 0x3e, 0x7e, 0x7e, 0x7e, 0x7c, 0xfd, 0xfd,
    0xfd, 0xf9, 0xfb, 0x03, 0x38, 0x0e, 0x07, 0x01,
};


/*--------------
  Left paw down
  --------------*/
// diff_key1_up
static const uint8_t diff_key1_up_idx_delta[] PROGMEM = {
    255,  41, 123, 126,
};

static const uint8_t diff_key1_up_siz[] PROGMEM = {
      0,   8,  15,  12,
};

static const char diff_key1_up_val[] PROGMEM = {
    0x00, 0x00, 0x00, 0xc0, 0xe0, 0xf0, 0xf8, 0xf8, 0x82, 0x82,
    0x80, 0x04, 0x04, 0x7c, 0x7e, 0xff, 0x7f, 0x7f, 0x7f, 0x7f,
    0xbf, 0xbf, 0xbf, 0x60, 0x60, 0x40, 0xc4, 0xc4, 0xc0, 0x80,
    0x80, 0x80, 0x88, 0x58, 0x78,
};

// diff_key2_up
static const uint8_t diff_key2_up_idx_delta[] PROGMEM = {
    255,  41, 128,   6, 125,
};

static const uint8_t diff_key2_up_siz[] PROGMEM = {
      0,   8,   2,  12,  11,
};

static const char diff_key2_up_val[] PROGMEM = {
    0x00, 0x00, 0x00, 0xc0, 0xe0, 0xf0, 0xf8, 0xf8, 0xe0, 0xe6,
    0x0f, 0x07, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f,
    0x3f, 0x1f, 0x05, 0x01, 0x13, 0x08, 0x00, 0x03, 0x03, 0x83,
    0x93, 0xf3, 0xf9,
};

// diff_key3_up
static const uint8_t diff_key3_up_idx_delta[] PROGMEM = {
    255,  41, 128,  11, 127, 129,
};

static const uint8_t diff_key3_up_siz[] PROGMEM = {
      0,   8,   2,  10,  14,   7,
};

static const char diff_key3_up_val[] PROGMEM = {
    0x00, 0x00, 0x00, 0xc0, 0xe0, 0xf0, 0xf8, 0xf8, 0xe0, 0xe6,
    0x3f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb, 0x0e,
    0x3f, 0x0f, 0x07, 0x20, 0x19, 0x03, 0x63, 0x03, 0x03, 0x03,
    0x80, 0xe4, 0xf4, 0xf0, 0xf6, 0xf4, 0xec, 0xec, 0xec, 0xe8,
    0xc8,
};


/*--------------
  Right paw down
  --------------*/
// diff_key4_up
static const uint8_t diff_key4_up_idx_delta[] PROGMEM = {
    255, 205, 112, 127,
};

static const uint8_t diff_key4_up_siz[] PROGMEM = {
      0,  10,  19,  12,
};

static const char diff_key4_up_val[] PROGMEM = {
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0x1c, 0x2c, 0x20, 0x00, 0x00, 0x18, 0x3e, 0x3f, 0x3f, 0x3f,
    0xbf, 0xbf, 0xbf, 0xdf, 0xdf, 0xdf, 0xcf, 0xcf, 0x0f, 0xd8,
    0xd0, 0x90, 0xb0, 0xb1, 0xb1, 0xa0, 0x60, 0x68, 0x7e, 0x5e,
    0xd9,
};

// diff_key5_up
static const uint8_t diff_key5_up_idx_delta[] PROGMEM = {
    255, 205, 121, 126,
};

static const uint8_t diff_key5_up_siz[] PROGMEM = {
      0,  10,  19,  10,
};

static const char diff_key5_up_val[] PROGMEM = {
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0x61, 0x83, 0x03, 0x03, 0x33, 0x7d, 0x7f, 0x7f, 0x7f, 0x7f,
    0xbf, 0xbf, 0x9f, 0x9f, 0x0f, 0x0f, 0x17, 0x17, 0x37, 0x61,
    0x60, 0x40, 0xc1, 0xc0, 0xc0, 0x80, 0x80, 0xa0, 0xa4,
};

// diff_key6_up
static const uint8_t diff_key6_up_idx_delta[] PROGMEM = {
    255, 205, 128, 127,
};

static const uint8_t diff_key6_up_siz[] PROGMEM = {
      0,  10,  15,  13,
};

static const char diff_key6_up_val[] PROGMEM = {
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xc7, 0xc7, 0x07, 0x0f, 0xe7, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0x8b, 0x83, 0x02, 0x10, 0x10,
    0x01, 0x01, 0x03, 0x03, 0xc1, 0x51, 0x59, 0x05,
};

#endif // defined(OLED_DRIVER_ENABLE) && defined(BONGOCAT_ANIMATION)
