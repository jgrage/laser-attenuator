/* filter.cpp
 * Jonas
 */
#include "Arduino.h"
#include "filter.hpp"

/* -----------------------
 * Generic filter functions
 * -----------------------
 */
void filter::connect(int enable_pin, int encoder_inserted_pin, int encoder_removed_pin){
    
    _encoder_inserted_pin = encoder_inserted_pin;
    _encoder_removed_pin = encoder_removed_pin;
    _enable_pin = enable_pin;
    
    pinMode(_encoder_inserted_pin, INPUT);
    pinMode(_encoder_removed_pin, INPUT);
    pinMode(_enable_pin, OUTPUT);
    return;
}

void filter::insert(){
    digitalWrite(_enable_pin, HIGH);
    return;
}

void filter::remove(){
    digitalWrite(_enable_pin, LOW);
    return;
}

void filter::update_state(){
    int removed = digitalRead(_encoder_removed_pin);
    int inserted = digitalRead(_encoder_inserted_pin);
    
    if ((removed == HIGH) && (inserted == LOW)){
        state = REMOVED;
    }
    
    else if ((removed == LOW) && (inserted == HIGH)){
        state = INSERTED;
    }
    
    else{
        state = MOVING;
    }
    return;
}
