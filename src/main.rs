// Test program to get the dotstar LEDs working in rust
//

mod dotstar;

fn main() {
    println!("Running rust dotstar test");

    let mut led = dotstar::LedControl::new();

    led.led_update(); 
}
