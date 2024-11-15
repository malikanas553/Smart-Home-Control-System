// Include Guard to avoid multiple inclusion
#ifndef __keypad__
#define __keypad__

const char key_map[3][3] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'}
};

char key = '\0';

char keypad_get_key(void);

#endif
