#include "board_io.h"
#include "delay.h"
#include "gpio.h"
#include <stdio.h>

#include "lpc40xx.h"

#if 0
int main(void) {
  // const gpio_s led = board_io__get_led0();

  // const gpio_s led1 = board_io__get_led1();

  // const gpio_s led3 = board_io__get_led3();

  while (true) {
    // gpio__toggle(led);
    // gpio__toggle(led1);
    // gpio__toggle(led3);
    // delay__ms(500);
    // printf("Hello world!\n");

    LPC_GPIO2->PIN |= (1 << 3);
    LPC_GPIO2->CLR = (1 << 3);
    
    // ClearPin;
    delay__ms(500);

    LPC_GPIO2->PIN &= ~(1 << 3);
    // SetPin;
    LPC_GPIO2->SET = (1 << 3);
    delay__ms(500);
  }

  return 0; // main() shall never returnsconsc
}

#endif

bool toogle_state = false;
bool last_button_state = true;
bool led_state = false;

bool readSwitchState() { return (LPC_GPIO1->PIN & (1 << 19)) != 0; }

void SetPin() { LPC_GPIO2->SET = (1 << 3); }

void ClearPin() { LPC_GPIO2->CLR = (1 << 3); }

void CarBlinker(bool on) {

  // While holding button

  if (LPC_GPIO1->PIN & (1 << 19)) {

    // This sets the pin to high
    SetPin();
    delay__ms(250);
    // This sets the pin to low
    ClearPin();
  }
}

void CarBlinker2(bool on) {

  // While holding button

  if (on) {

    // This sets the pin to high
    SetPin();
    delay__ms(250);
    // This sets the pin to low
    ClearPin();
  }
}

int main() {

  // Set as output LED
  LPC_GPIO1->DIR |= (1 << 24);
  LPC_GPIO2->DIR |= (1 << 3);

  // Set switch as OUTPUT
  LPC_GPIO0->DIR &= ~(1 << 30);

  LPC_GPIO1->DIR &= ~(1 << 19);

  while (true) {

    // // SET PIN
    // LPC_GPIO1->PIN |= (1 << 24);
    // delay__ms(500);
    // // CLEAR PIN
    // LPC_GPIO1->PIN &= ~(1 << 24);
    // delay__ms(500);
    // // LPC_GPIO1->PIN |= (1 << 24);

    // // LPC_GPIO1->PIN ^= (1 << 24);
    // // LPC_GPIO2->PIN ^= (1 << 3);

    delay__ms(500);

    // Using set and clear

    // // This sets the pin to high
    // SetPin();
    // delay__ms(500);

    // // This sets the pin to low
    // ClearPin();

    // delay__ms(500);

    // if (LPC_GPIO1->PIN & (1 << 19)) {
    //   SetPin();
    // }
    // else {
    //   ClearPin();
    // }

    // bool current_button_state = readSwitchState();

    // if (current_button_state && !last_button_state) {

    //   toogle_state = !toogle_state;
    //   delay__ms(100);
    // }

    // // The state of last_button_pressed is always low before the button
    // // is pressed, making the above if condition on right true.
    // last_button_state = current_button_state;

    // if (toogle_state) {

    //   led_state = !led_state;
    //   CarBlinker2(led_state);
    //   delay__ms(250);
    // }

    bool current_state = readSwitchState();

    if (current_state && !last_button_state) {

      toogle_state = !toogle_state;

      delay__ms(100);
    }

    last_button_state = current_state;

    if (toogle_state) {

      led_state = !led_state;

      CarBlinker2(led_state);
      delay__ms(250);
    }
  }
  return 1;
}
