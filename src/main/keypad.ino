#include <util/delay.h>
#include "keypad.h"
#include "dio.h"

char keypad_get_key(void) {
    // Iterate over each row
    for (int row = 0; row < 3; row++) {
        // Set all rows high initially
        Set_PIN_State(&PORTB, ROW1_PIN, HIGH);
        Set_PIN_State(&PORTB, ROW2_PIN, HIGH);
        Set_PIN_State(&PORTB, ROW3_PIN, HIGH);
        
        // Pull only the current row low
        Set_PIN_State(&PORTB, ROW1_PIN + row, LOW);

        // Short delay to allow signals to stabilize
        _delay_us(5);

        // Check each column for a pressed key
        if (Is_Button_Pressed(&PINB, COL1_PIN)) return key_map[row][0];
        if (Is_Button_Pressed(&PINB, COL2_PIN)) return key_map[row][1];
        if (Is_Button_Pressed(&PINB, COL3_PIN)) return key_map[row][2];
    }
    
    // No key press detected
    return '\0';
}