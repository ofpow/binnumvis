#pragma once

typedef struct Button {
    Rectangle rec;
    const char *text;
    Color color;
    int index;
} Button;

define_array(Buttons, Button);
Buttons buttons;
