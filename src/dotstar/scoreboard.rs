use dotstar::LedControl;
use std::thread::{sleep};
use std::time;

const BRIGHTNESS: u8 = 5;

pub struct DotstarScoreboardControl {
    balls: u8,
    strikes: u8,
    outs: u8,
    first: bool,
    second: bool,
    third: bool,
    led: LedControl
}

/// Effects functions
///
/// Used for the baseball specific lighting effects and abstraction of the specific LEDs
/// These functions will also automatically update the LEDs on the board
impl DotstarScoreboardControl {

    pub fn new() -> DotstarScoreboardControl {
        DotstarScoreboardControl {
            balls: 0,
            strikes: 0,
            outs: 0,
            first: false,
            second: false,
            third: false,
            led: LedControl::new()
        }
    }

    pub fn set_count(&mut self, balls: u8, strikes: u8, outs: u8) {
        self.balls = balls;
        self.strikes = strikes;
        self.outs = outs;

        self.push_pixels();
    }

    pub fn set_runners(&mut self, first: bool, second: bool, third: bool) {
        self.first = first;
        self.second = second;
        self.third = third;

        self.push_pixels();
    }

    pub fn strikeout(&mut self) {
        let effect_duration = time::Duration::from_millis(750);

        for _ in 0..5 {
            self.led.set_led_color(5, 7, BRIGHTNESS, 255, 0, 0);
            self.led.led_update();
            sleep(effect_duration);
            self.led.set_led_color(5, 7, BRIGHTNESS, 0, 0, 0);
            self.led.led_update();
            sleep(effect_duration);
        }

        // Reset count, use the current outs
        self.set_count(0, 0, self.outs);
    }

    pub fn walk(&mut self) {
        let effect_duration = time::Duration::from_millis(750);

        for _ in 0..5 {
            self.led.set_led_color(1, 4, BRIGHTNESS, 0, 255, 0);
            self.led.led_update();
            sleep(effect_duration);
            self.led.set_led_color(1, 4, BRIGHTNESS, 0, 0, 0);
            self.led.led_update();
            sleep(effect_duration);
        }

        // Reset count, use the current outs
        self.set_count(0, 0, self.outs);
    }

    pub fn sides_retired(&mut self) {
        let effect_duration = time::Duration::from_millis(750);

        for _ in 0..5 {
            self.led.set_led_color(8, 10, BRIGHTNESS, 0, 0, 255);
            self.led.led_update();
            sleep(effect_duration);
            self.led.set_led_color(8, 10, BRIGHTNESS, 0, 0, 0);
            self.led.led_update();
            sleep(effect_duration);
        }

        // Reset count, use the current outs
        self.set_count(0, 0, 3);
    }

    pub fn home_run(&mut self) {
        let effect_duration = time::Duration::from_millis(750);

        for _ in 0..5 {
            self.led.set_led_color(11, 13, BRIGHTNESS, 255, 255, 0);
            self.led.led_update();
            sleep(effect_duration);
            self.led.set_led_color(11, 13, BRIGHTNESS, 0, 0, 0);
            self.led.led_update();
            sleep(effect_duration);
        }

        // Reset count, use the current outs
        self.set_count(0, 0, self.outs);
    }

    fn push_pixels(&mut self) {
        self.led.clear_led(1,13);

        if self.balls > 0 {
            self.led.set_led_color(1, self.balls as usize, BRIGHTNESS, 0, 255, 0);
        }

        if self.strikes > 0 {
            self.led.set_led_color(5, 4 + (self.strikes) as usize, BRIGHTNESS, 255, 0, 0);
        }

        if self.outs > 0 {
            self.led.set_led_color(8, 7 + (self.outs) as usize, BRIGHTNESS, 0, 0, 255);
        }

        if self.first {
            self.led.set_led_color(11, 11, BRIGHTNESS, 255, 255, 0);
        }

        if self.second {
            self.led.set_led_color(12, 12, BRIGHTNESS, 255, 255, 0);
        }

        if self.third {
            self.led.set_led_color(13, 13, BRIGHTNESS, 255, 255, 0);
        }

        self.led.led_update();
    }
}
