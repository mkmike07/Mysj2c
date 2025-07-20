// #include "board_io.h"
// #include "delay.h"
// #include "gpio.h"

// #include "lpc40xx.h"
// #include <stdio.h>

// #include <stdint.h>

// // const uint32_t led3 = (1U << 3);

// volatile uint32_t *const DIR2 = (uint32_t *)(0x20098040);
// volatile uint32_t *const PIN2 = (uint32_t *)(0x20098054);

// void toggle() {
//   // set as output
//   (*DIR2) |= (1 << 3);
//   // set the bit
//   (*PIN2) |= (1 << 3);
//   delay__ms(500);
//   (*PIN2) &= ~(1 << 3);
//   delay__ms(500);
// }

// int main(void) {
//   const gpio_s led0 = board_io__get_led0();
//   const gpio_s led1 = board_io__get_led1();
//   const gpio_s led2 = board_io__get_led2();

//   while (true) {

//     // gpio__toggle(led0);
//     // gpio__toggle(led1);
//     // gpio__toggle(led2);
//     // delay__ms(500);
//     // printf("Hello world!\n");

//     // gpio__set(led0);

//     // // gpio set as output
//     // LPC_GPIO2->DIR |= (1 << 3);
//     // setPinAsouput;

//     // LPC_GPIO2->PIN |= (1 << 3);
//     // LPC_GPIO2->CLR = (1 << 3);
//     // ClearPin;
//     // delay__ms(500);

//     // LPC_GPIO2->PIN &= ~(1 << 3);
//     // SetPin;
//     // LPC_GPIO2->SET = (1 << 3);
//     // delay__ms(500);

//     toggle();

//   }

//   return 0; // main() shall never return
// }

#include "board_io.h"
#include "delay.h"
#include "gpio.h"

#include "lpc40xx.h"
#include <stdint.h>
#include <stdio.h>

// const uint32_t led3 = (1U << 3);

volatile uint32_t *const DIR2 = (uint32_t *)(0x20098040);
volatile uint32_t *const PIN2 = (uint32_t *)(0x20098054);

volatile uint32_t *const DIR1 = (uint32_t *)(0x20098020);
volatile uint32_t *const PIN1 = (uint32_t *)(0x20098034);

// Global Variable

bool toggle_state = false;
bool last_button_state = true;
bool led_state = false;

void Set_switch() {

  // set as input
  (*DIR1) &= ~(1 << 19);

  // set the bit / Enable pull up resistor
  (*PIN1) |= (1 << 19);
  // clear the bit
  // (*PIN1) &= ~(1 << 19);
}

void Set_Led() {

  // set as output
  (*DIR2) |= (1 << 3);
}

bool read_switch_state() { return (*PIN1) & (1 << 19); }

void toggle() {
  // set as output
  (*DIR2) |= (1 << 3);
  // set the bit
  (*PIN2) |= (1 << 3);
  delay__ms(500);
  // clear the bit
  (*PIN2) &= ~(1 << 3);
  delay__ms(500);
}

int main(void) {
  const gpio_s led0 = board_io__get_led0();
  const gpio_s led1 = board_io__get_led1();
  const gpio_s led2 = board_io__get_led2();

  Set_Led();
  Set_switch();

  while (true) {

    // gpio__toggle(led0);
    // gpio__toggle(led1);
    // gpio__toggle(led2);
    // delay__ms(500);
    // printf("Hello world!\n");

    // gpio__set(led0);

    //  gpio set led P2.3 direction as output

    // LPC_GPIO2->DIR |= (1 << 3);

    // setPinAsouput;

    // LPC_GPIO2->PIN |= (1 << 3);
    // LPC_GPIO2->CLR = (1 << 3);
    // ClearPin;
    // delay__ms(500);

    // LPC_GPIO2->PIN &= ~(1 << 3);
    // SetPin;
    // LPC_GPIO2->SET = (1 << 3);
    // delay__ms(500);

    // toggle();

    bool current_button_state = read_switch_state();

    printf("Hello world!\n");

    if (current_button_state && !last_button_state) {

      toggle_state = !toggle_state; 
      delay__ms(50);
    }

    last_button_state = current_button_state;

    if (toggle_state) {
      led_state = !led_state;

      if (led_state) {

        // Set (2.3)
        (*PIN2) |= (1 << 3);
      } else {

        // Clear (2.3)
        (*PIN2) &= ~(1 << 3);
      }

      delay__ms(500);
    }

    //   else {
    //     if (led_state) {

    //       // Set (2.3)
    //       (*PIN2) |= (1 << 3);
    //     } else {

    //       //Clear (2.3)
    //       (*PIN2) &= ~(1 << 3);
    //     }
    //   }
    // }

    return 0; // main() shall never return
  }
}