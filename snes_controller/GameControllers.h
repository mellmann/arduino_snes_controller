
#ifndef SNES_H
#define SNES_H

class SNESController
{
public:

  enum ButtonID
  {
    B = 0,
    Y = 1,
    SELECT = 2,
    START = 3,
    UP = 4,
    DOWN = 5,
    LEFT = 6,
    RIGHT = 7,
    A = 8,
    X = 9,
    L = 10,
    R = 11,
    NUM_OF_BUTTONS = 12 // needed for iteration
  };
  
  class Button {
    private:
      long count;
      bool state_changed;
      
    public:
      Button() : count(0), state_changed(false) {}
      
      void update(bool pressed) {
        if(pressed) {
          state_changed = count == 0; // button was released before
          count++;
        } else {
          state_changed = count > 0; // button was pressed before
          count = 0;
        }
      }
      
    bool isPressed() {
      return count > 0;
    }
    
    bool pressed() {
      return count == 1;
    }
    
    bool released() {
      return count == 0 && state_changed;
    }
  };

  // initialize a new controller
  SNESController(int latchPin, int clockPin, int dataPin) 
    : 
    latchPin(latchPin), 
    clockPin(clockPin), 
    dataPin(dataPin)
  {
  }
  
private:

  // pins
  int latchPin;
  int clockPin;
  int dataPin;
  
public:
  Button buttons[NUM_OF_BUTTONS];

  /// This has to be initialized once for the shared pins latch and clock
  void init()
  {
    pinMode(latchPin, OUTPUT);
    digitalWrite(latchPin, LOW);
    
    pinMode(clockPin, OUTPUT);
    digitalWrite(clockPin, HIGH);
    
    pinMode(dataPin, INPUT_PULLUP);
  }


  void poll()
  {
    // signal the controller to send data
    digitalWrite(latchPin, HIGH);
    delayMicroseconds(12);
    digitalWrite(latchPin, LOW);
    delayMicroseconds(6);
    
    // read values for all buttons
    for(int i = 0; i < NUM_OF_BUTTONS; i++) {
      
      // read the new value and update the current button state
      buttons[i].update(digitalRead(dataPin) == LOW);
        
      // clock tick to read the next value
      digitalWrite(clockPin, HIGH);
      delayMicroseconds(6);
      digitalWrite(clockPin, LOW);
      delayMicroseconds(6);
    }
  }

};

#endif //SNES_H