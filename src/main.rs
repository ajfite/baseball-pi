// Test program to get the dotstar LEDs working in rust
//
use std::{thread, time};
use dotstar::scoreboard::DotstarScoreboardControl;

mod dotstar;

fn main() {
    println!("Running rust dotstar test");

    let mut dotstar_control = DotstarScoreboardControl::new();

    for _ in 1..100 {
        let one_second = time::Duration::from_secs(1);

        dotstar_control.set_count(0, 0, 0);
        thread::sleep(one_second);
        dotstar_control.set_count(1, 0, 0);
        thread::sleep(one_second);
        dotstar_control.set_count(2, 0, 0);
        thread::sleep(one_second);
        dotstar_control.set_count(2, 1, 0);
        thread::sleep(one_second);
        dotstar_control.set_count(2, 2, 0);
        thread::sleep(one_second);
        dotstar_control.strikeout();
        thread::sleep(one_second);
        dotstar_control.set_count(1, 0, 1);
        thread::sleep(one_second);
        dotstar_control.set_count(2, 0, 1);
        thread::sleep(one_second);
        dotstar_control.set_count(3, 0, 1);
        thread::sleep(one_second);
        dotstar_control.walk();
        dotstar_control.set_runners(true, false, false);
        thread::sleep(one_second);
        dotstar_control.set_count(0,1,1);
        thread::sleep(one_second);
        dotstar_control.home_run();
        dotstar_control.set_runners(false, false, false);
        thread::sleep(one_second);
        dotstar_control.set_count(1, 0, 1);
        thread::sleep(one_second);
        dotstar_control.set_count(0, 0, 2);
        thread::sleep(one_second);
        dotstar_control.set_count(0, 1, 2);
        thread::sleep(one_second);
        dotstar_control.set_count(0, 2, 2);
        thread::sleep(one_second);
        dotstar_control.strikeout();
        dotstar_control.sides_retired();

    }
}
