// Test program to get the dotstar LEDs working in rust
//

use std::{thread, time};

mod dotstar;

fn main() {
    println!("Running rust dotstar test");

    let mut led = dotstar::LedControl::new();

    for _ in 1..100 {
        let one_second = time::Duration::from_secs(1);

        led.set_led_color(1, 13, 5, 255, 0, 0);
        led.led_update();
        led.led_upda

        thread::sleep(one_second);

        led.clear_led(1, 13);
        led.led_update();
        
        thread::sleep(one_second);

        led.set_led_color(1, 13, 5, 0, 0, 255);
        led.led_update();

        thread::sleep(one_second);

        led.set_led_color(1, 13, 5, 0, 255, 0);
        led.led_update();

        thread::sleep(one_second);
    }
}
