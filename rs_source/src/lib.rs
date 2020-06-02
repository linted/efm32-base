#![no_std]
#![feature(lang_items)]
#![feature(alloc_error_handler)]

use core::panic::PanicInfo;

extern crate alloc;

mod coru;

mod bg_malloc;
use bg_malloc::BGAlloc;

mod handlers;
pub use handlers::*; // This has to stay
mod state;
mod bindings;

mod rs_main;
pub use rs_main::rs_main;

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



