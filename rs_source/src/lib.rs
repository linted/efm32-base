#![no_std]
#![no_main]
#![feature(lang_items)]

use core::panic::PanicInfo;

extern crate libc;

#[panic_handler]
fn panic(_info: &PanicInfo) -> ! {
    loop {}
}

#[lang = "eh_personality"]
extern "C" fn eh_personality() {}

extern "C" {
    fn delay(_amnt: usize);
    fn toggle_pin(pin: u32, t: u32);
}

#[no_mangle]
pub fn rs_main() {
    loop {
        unsafe{ delay(1000) };
        unsafe{ toggle_pin(0, 4) };
    }
}

