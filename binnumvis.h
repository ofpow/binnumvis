#pragma once

uint64_t num = 0;

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
Buttons bit_buttons;
Buttons bit_selection_buttons;

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

void set_64_bit_settings(void) {
    num = 0;
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

    for (int i = 0; i < num_bits; i++) {
        bit_buttons.data[i] = (Button){
            { 16 + i * (GetScreenWidth() / button_x_divide), GetScreenHeight() / button_y_divide, GetScreenWidth() / button_height_divide, GetScreenHeight() / button_width_divide },
            "0",
            RED,
            i
        };
    }
}

void set_32_bit_settings(void) {
    num = 0;
    num_bits = 32;
    button_x_divide = 32;
    button_y_divide = 10;
    button_height_divide = 50;
    button_width_divide = 19;
    signed_print = "%d";
    unsigned_print = "%u";
    hex_print = "0x%8llX";
    bit_text_offset = 4;
    bit_text_width_divide = 28;
    text_height_divide = 20;
    text_width_divide = 42;

    for (int i = 0; i < num_bits; i++) {
        bit_buttons.data[i] = (Button){
            {
                16 + i * (GetScreenWidth() / button_x_divide), 
                GetScreenHeight() / button_y_divide, 
                GetScreenWidth() / button_height_divide,
                GetScreenHeight() / button_width_divide,
            },
            "0",
            RED,
            i
        };
    }
}

void set_8_bit_settings(void) {
    num = 0;
    num_bits = 8;
    button_x_divide = 8;
    button_y_divide = 12;
    button_height_divide = 24;
    button_width_divide = 10;
    signed_print = "%d";
    unsigned_print = "%u";
    hex_print = "0x%8llX";
    bit_text_offset = 16;
    bit_text_width_divide = 14;
    text_height_divide = 10;
    text_width_divide = 20;

    for (int i = 0; i < num_bits; i++) {
        bit_buttons.data[i] = (Button){
            { 16 + i * (GetScreenWidth() / button_x_divide), GetScreenHeight() / button_y_divide, GetScreenWidth() / button_height_divide, GetScreenHeight() / button_width_divide },
            "0",
            RED,
            i
        };
    }
}

void update_button_sizes(void) {
    for (int i = 0; i < num_bits; i++) {
        bit_buttons.data[i].rec = (Rectangle){
            16 + i * (GetScreenWidth() / button_x_divide),
            GetScreenHeight() / button_y_divide,
            GetScreenWidth() / button_height_divide,
            GetScreenHeight() / button_width_divide
        };
    }
    bit_selection_buttons.data[2].rec = (Rectangle)(Rectangle){GetScreenWidth() / 1.6666667 - (GetScreenWidth() / 30), GetScreenHeight() / 30, GetScreenWidth() / 15, GetScreenHeight() / 20},
    bit_selection_buttons.data[1].rec = (Rectangle)(Rectangle){GetScreenWidth() / 2 - (GetScreenWidth() / 30), GetScreenHeight() / 30, GetScreenWidth() / 15, GetScreenHeight() / 20},
    bit_selection_buttons.data[0].rec = (Rectangle){GetScreenWidth() / 2.5 - (GetScreenWidth() / 30), GetScreenHeight() / 30, GetScreenWidth() / 15, GetScreenHeight() / 20};
}

void init_buttons(void) {
    bit_buttons = (Buttons) {
        calloc(64, sizeof(Button)),
        63,
        64
    };

    for (int i = 0; i < num_bits; i++) {
        bit_buttons.data[i] = (Button){
            { 16 + i * (GetScreenWidth() / button_x_divide), GetScreenHeight() / button_y_divide, GetScreenWidth() / button_height_divide, GetScreenHeight() / button_width_divide },
            "0",
            RED,
            i
        };
    }

    bit_selection_buttons = (Buttons) {
        calloc(64, sizeof(Button)),
        2,
        3
    };

    bit_selection_buttons.data[0] = (Button) {
        (Rectangle){GetScreenWidth() / 2.5 - (GetScreenWidth() / 30), GetScreenHeight() / 30, GetScreenWidth() / 15, GetScreenHeight() / 20},
        "8 bit",
        LIGHTGRAY,
        0
    };
    bit_selection_buttons.data[1] = (Button) {
        (Rectangle){GetScreenWidth() / 2 - (GetScreenWidth() / 30), GetScreenHeight() / 30, GetScreenWidth() / 15, GetScreenHeight() / 20},
        "32 bit",
        LIGHTGRAY,
        1
    };
    bit_selection_buttons.data[2] = (Button) {
        (Rectangle){GetScreenWidth() / 1.6666667 - (GetScreenWidth() / 30), GetScreenHeight() / 30, GetScreenWidth() / 15, GetScreenHeight() / 20},
        "64 bit",
        LIGHTGRAY,
        2
    };
}

void draw_bit_selection_buttons(void) {
    char num_text[24];

    float xoffset = GetScreenWidth() / 60;
    float yoffset = GetScreenHeight() / 65;
    DrawRectangleRounded(bit_selection_buttons.data[0].rec, 0.5, 3, LIGHTGRAY);
    DrawText("8 bit", bit_selection_buttons.data[0].rec.x + xoffset, bit_selection_buttons.data[0].rec.y + yoffset, 50, WHITE);
    if (CheckCollisionPointRec(GetMousePosition(), bit_selection_buttons.data[0].rec) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        set_8_bit_settings();
    }
    DrawRectangleRounded(bit_selection_buttons.data[1].rec, 0.5, 3, LIGHTGRAY);
    DrawText("32 bit", bit_selection_buttons.data[1].rec.x + xoffset, bit_selection_buttons.data[1].rec.y + yoffset, 50, WHITE);
    if (CheckCollisionPointRec(GetMousePosition(), bit_selection_buttons.data[1].rec) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        set_32_bit_settings();
    }
    DrawRectangleRounded(bit_selection_buttons.data[2].rec, 0.5, 3, LIGHTGRAY);
    DrawText("64 bit", bit_selection_buttons.data[2].rec.x + xoffset, bit_selection_buttons.data[2].rec.y + yoffset, 50, WHITE);
    if (CheckCollisionPointRec(GetMousePosition(), bit_selection_buttons.data[2].rec) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        set_64_bit_settings();
    }

    sprintf(num_text, signed_print, num);
    DrawText("signed:", GetScreenWidth() / 40, GetScreenHeight() / 5, GetScreenWidth() / 40, LIGHTGRAY);
    DrawText(num_text, GetScreenWidth() / 40, GetScreenHeight() / 4, GetScreenWidth() / 40, WHITE);

    sprintf(num_text, unsigned_print, num);
    DrawText("unsigned:", GetScreenWidth() / 2, GetScreenHeight() / 5, GetScreenWidth() / 40, LIGHTGRAY);
    DrawText(num_text, GetScreenWidth() / 2, GetScreenHeight() / 4, GetScreenWidth() / 40, WHITE);

    sprintf(num_text, "0x%16llX", num);
    DrawText("hex:", GetScreenWidth() / 40, GetScreenHeight() / 3, GetScreenWidth() / 40, LIGHTGRAY);
    DrawText(num_text, GetScreenWidth() / 40, GetScreenHeight() / 2.5, GetScreenWidth() / 40, WHITE);
}

bool pressed_last_frame = false;
Vector2 start_pos = {0};
Vector2 end_pos = {0};

#define ABS(_x) ((_x) < 0 ? -(_x) : (_x))

void update_bit_button(int i) {
    Button b = bit_buttons.data[i];
    DrawRectangleRounded(b.rec, 0.5, 3, b.color);
    
    DrawText(b.text, b.rec.x + bit_text_offset, b.rec.y, GetScreenWidth() / bit_text_width_divide, WHITE);
    
    if (i % 8 == 0 && num_bits > 8) {
        char x[4];
        sprintf(x, "%d", i);
        DrawText(x, b.rec.x + bit_text_offset, b.rec.y + GetScreenHeight() / text_height_divide, GetScreenWidth() / text_width_divide, LIGHTGRAY);
    }

    if (CheckCollisionPointRec(GetMousePosition(), b.rec) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !pressed_last_frame) {
        pressed_last_frame = true;
        start_pos = GetMousePosition();
        uint64_t mask = (uint64_t)1 << i;
        if (raylib_color_equals(b.color, RED)) {
            num |= mask;
            bit_buttons.data[i].color = GREEN;
            bit_buttons.data[i].text = "1";
        } else {
            num &= ~mask;
            bit_buttons.data[i].color = RED;
            bit_buttons.data[i].text = "0";
        }
    }

    if (pressed_last_frame && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
        end_pos = GetMousePosition();
        pressed_last_frame = false;
        if (start_pos.x != end_pos.x || start_pos.y != end_pos.y) {
            return;
        }
        end_pos = (Vector2){0, 0};
    }
}

bool text_input_active = false;
char input_text[24];
int i = 0;

void update_input(void) {
    DrawText("input:", GetScreenWidth() / 2, GetScreenHeight() / 3, GetScreenWidth() / 40, LIGHTGRAY);
    Rectangle input_background = {GetScreenWidth() / 2, GetScreenHeight() / 2.5, GetScreenWidth() / 3, GetScreenHeight() / 20};
    DrawRectangleRec(input_background, WHITE);

    if (CheckCollisionPointRec(GetMousePosition(), input_background) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        text_input_active = true;
    } else if (!CheckCollisionPointRec(GetMousePosition(), input_background) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        text_input_active = false;
    }

    if (text_input_active) {
        int c = GetCharPressed();
        while (c > 0) {
            if (i < 23) {
                input_text[i] = c;
                input_text[i + 1] = 0;
                i++;
            }
            c = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE)) {
            i--;
            if (i < 0) i = 0;
            input_text[i] = 0;
        } 
        DrawRectangleLinesEx(input_background, 10, LIGHTGRAY);
    } else {
        DrawRectangleRec(input_background, WHITE);
    }

    DrawText(input_text, input_background.x + GetScreenWidth()/200, input_background.y, GetScreenHeight()/25, PINK);

    Rectangle input_button = {GetScreenWidth() / 1.175, GetScreenHeight() / 2.5, GetScreenWidth() / 12, GetScreenHeight() / 20};
    DrawRectangleRec(input_button, LIGHTGRAY);
    DrawText("INPUT", input_button.x + GetScreenWidth()/200, input_button.y + GetScreenHeight()/100, GetScreenHeight()/25, WHITE);

    if (CheckCollisionPointRec(GetMousePosition(), input_button) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        text_input_active = false;
        num = atoll(input_text);
        memset(input_text, 0, sizeof(input_text));
        i = 0;

        for (int i = 0; i < num_bits; i++) {
            if ((num >> i) & 1) {
                bit_buttons.data[i] = (Button){
                    { 16 + i * (GetScreenWidth() / button_x_divide), GetScreenHeight() / button_y_divide, GetScreenWidth() / button_height_divide, GetScreenHeight() / button_width_divide },
                    "1",
                    GREEN,
                    i
                };
            } else {
                bit_buttons.data[i] = (Button){
                    { 16 + i * (GetScreenWidth() / button_x_divide), GetScreenHeight() / button_y_divide, GetScreenWidth() / button_height_divide, GetScreenHeight() / button_width_divide },
                    "0",
                    RED,
                    i
                };
            }
        }
    }
}

Button toggle_bit_button(Button b) {
    if (raylib_color_equals(b.color, RED)) {
        return (Button) {
            b.rec,
            "1",
            GREEN,
            b.index,
        };
    } else {
        return (Button) {
            b.rec,
            "0",
            RED,
            b.index,
        };
    }
}

void update_drag_toggle(void) {
    if (end_pos.x != 0 || end_pos.y != 0) {
        float temp = 0;
        if (end_pos.x < start_pos.x) {
            temp = end_pos.x;
            end_pos.x = start_pos.x;
            start_pos.x = temp;
        }
        if (start_pos.y > end_pos.y) {
            temp = end_pos.y;
            end_pos.y = start_pos.y;
            start_pos.y = temp;
        }

        for (int i = 0; i < num_bits; i++) {
            Rectangle r = bit_buttons.data[i].rec;
            if (start_pos.x < r.x && r.x <= end_pos.x) {
                uint64_t mask = (uint64_t)1 << i;
                if (raylib_color_equals(bit_buttons.data[i].color, RED)) {
                    num |= mask;
                } else {
                    num &= ~mask;
                }
                bit_buttons.data[i] = toggle_bit_button(bit_buttons.data[i]);
            }
        }
        end_pos = (Vector2){0, 0};
    }

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        float temp = 0;
        float startx = start_pos.x;
        float starty = start_pos.y;
        float endx = GetMousePosition().x;
        float endy = GetMousePosition().y;
        if (endx < startx) {
            temp = endx;
            endx = startx;
            startx = temp;
        }
        if (starty > endy) {
            temp = endy;
            endy = starty;
            starty = temp;
        }
        Rectangle r = {
            startx,
            starty,
            ABS(startx - endx),
            ABS(endy - starty),
        };
        DrawRectangleRec(r, (Color){200, 200, 200, 100});
    }
}
