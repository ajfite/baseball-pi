extern crate spidev;
use std::io;
use std::io::prelude::*;
use self::spidev::{Spidev, SpidevOptions, SpiModeFlags};

// Spi Consts
const SPI_DEVICE_PATH: &str = "/dev/spidev1.0";
const MAX_SPI_SPEED: u32 = 200_000;

// LED Protocol Consts
const LED_COUNT: usize = 13;
const FRAME_WORD_COUNT: usize = 4;
const BITS_PER_WORD: u8 = 8;
const OVERHEAD_FRAMES: usize = 2;
const LED_ARR_SIZE: usize = (OVERHEAD_FRAMES + LED_COUNT) * FRAME_WORD_COUNT;

pub struct LedControl {
    led_array: [u8; LED_ARR_SIZE],
    spi_device: Spidev
}

impl LedControl {
    pub fn new() -> LedControl {
        let init_spi_dev = match LedControl::create_spi() {
            Ok(n) => { 
                println!("Spi setup was successful");
                n
            },
            Err(_) => panic!("Spi device setup failed")
        };

        LedControl {
            led_array: LedControl::init_led_array(),
            spi_device: init_spi_dev
        }
    }

    fn init_led_array() -> [u8; LED_ARR_SIZE] {
        let mut arr = [0u8; LED_ARR_SIZE];        

        // Init End Frame
        for n in (LED_ARR_SIZE - 1 - FRAME_WORD_COUNT)..LED_ARR_SIZE {
            arr[n] = 0xFF;
        }

        // Set up the pre-amble on the led frame
        let mut n = FRAME_WORD_COUNT;

        while n < LED_ARR_SIZE {
            arr[n] = 0b11100000;

            n += FRAME_WORD_COUNT;
        }

        return arr;
    }

    fn create_spi() -> io::Result<Spidev> {
        let mut spi = Spidev::open(SPI_DEVICE_PATH)?;
        let options = SpidevOptions::new()
            .bits_per_word(BITS_PER_WORD)
            .max_speed_hz(MAX_SPI_SPEED)
            .mode(SpiModeFlags::SPI_MODE_0)
            .build();
        spi.configure(&options)?;
        Ok(spi)
    }

    pub fn led_update(&mut self) {
        match self.spi_device.write(&self.led_array) {
            Ok(s) => {
                println!("Wrote {} to LEDs", s); 
                ()
            },
            Err(_) => panic!("Couldn't write to spi device")
        }
    }

    pub fn clear_led(&mut self, led_start: usize, led_end: usize) {
        self.set_led_color(led_start, led_end, 0, 0, 0, 0);
    }

    pub fn set_led_color(&mut self, led_start: usize, led_end: usize, brightness: u8, r: u8, g: u8, b: u8) {
        for n in led_start..led_end {
            self.led_array[FRAME_WORD_COUNT * n] = 0b11100000 | (0b00011111 & brightness);
            self.led_array[(FRAME_WORD_COUNT * n) + 1] = r;
            self.led_array[(FRAME_WORD_COUNT * n) + 2] = g;
            self.led_array[(FRAME_WORD_COUNT * n) + 3] = b;
        }
    }
}
