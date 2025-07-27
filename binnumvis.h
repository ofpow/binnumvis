#pragma once

#define define_array(_name, _type) \
    typedef struct _name {         \
        _type *data;               \
        int64_t index;             \
        int64_t capacity;          \
    } _name                        \

typedef struct Button {
    Rectangle rec;
    const char *text;
    Color color;
    int index;
} Button;

define_array(Buttons, Button);
Buttons buttons;

bool raylib_color_equals(Color c1, Color c2) {
    return (c1.r == c2.r && c1.g == c2.g && c1.b == c2.b && c1.a == c2.a);
}

int num_bits = 64;
int button_x_divide = 64;
int button_y_divide = 10;
int button_height_divide = 100;
int button_width_divide = 38;
char *signed_print = "%ld";
char *unsigned_print = "%llu";
char *hex_print = "0x%16llX";
int bit_text_offset = 2;
int bit_text_width_divide = 56;
int text_height_divide = 40;
int text_width_divide = 84;

void set_64_bit(void) {
    num_bits = 64;
    button_x_divide = 64;
    button_y_divide = 10;
    button_height_divide = 100;
    button_width_divide = 38;
    signed_print = "%ld";
    unsigned_print = "%llu";
    hex_print = "0x%16llX";
    bit_text_offset = 2;
    bit_text_width_divide = 56;
    text_height_divide = 40;
    text_width_divide = 84;
}
