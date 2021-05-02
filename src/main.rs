// Test program to get the dotstar LEDs working in rust
//
extern crate spidev;
use std::io;
use std::io::prelude::*;
use spidev::{Spidev, SpidevOptions, SpidevTransfer, SpiModeFlags};

fn main() {
    println!("Running rust dotstar test");

    let mut spi = create_spi().unwrap();

    spi.write(&[0x00, 0x00, 0x00, 0x00, 
              0xFF, 0x00, 0xFF, 0xFF,
              0xFF, 0x00, 0xFF, 0xFF,
              0xFF, 0x00, 0xFF, 0xFF,
              0xFF, 0x00, 0xFF, 0xFF,
              0xFF, 0x00, 0xFF, 0xFF,
              0xFF, 0xFF, 0xFF, 0xFF]); 
}

fn create_spi() -> io::Result<Spidev> {
    let mut spi = Spidev::open("/dev/spidev1.0")?;
    let options = SpidevOptions::new()
        .bits_per_word(8)
        .max_speed_hz(200_000)
        .mode(SpiModeFlags::SPI_MODE_0)
        .build();
    spi.configure(&options)?;
    Ok(spi)
}
