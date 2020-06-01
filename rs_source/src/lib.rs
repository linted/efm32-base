#![no_std]
#![feature(lang_items)]
#![feature(alloc_error_handler)]

use core::panic::PanicInfo;

extern crate alloc;

mod coru;
use coru::executor::Executor;

mod bg_malloc;
use bg_malloc::BGAlloc;

#[global_allocator]
static ALLOCATOR: BGAlloc = BGAlloc{};

#[alloc_error_handler]
fn alloc_error_handler(_layout: alloc::alloc::Layout) -> !{
    panic!("");
}

#[panic_handler]
fn panic(_info: &PanicInfo) -> ! {
    loop {}
}

#[lang = "eh_personality"]
extern "C" fn eh_personality() {}

extern "C" {
    fn delay(_amnt: usize);
    fn toggle_pin(pin: u32, t: u32);
    fn current_ticks() -> u32;
}

#[no_mangle]
pub fn rs_main() {
    let mut exe = Executor::new();

    exe.push(move | mut fib | async move {
        loop {
            unsafe { toggle_pin(5,3) };
            fib.tick_waiter(1000).await;
        }
    });

    exe.run();
}

