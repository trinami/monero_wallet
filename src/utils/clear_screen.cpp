#include "utils/clear_screen.hpp"

void clearScreen()
{
    Serial.write(27);             // ESC command
    Serial.print("[2J");        // clear screen command
    Serial.write(27);
    Serial.print("[H"); 
}
