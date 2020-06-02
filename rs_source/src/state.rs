static mut TICKS:u64 = 0;

pub fn inc_ticks() {
    unsafe { TICKS += 1 }
}

pub fn current_ticks() -> u64 {
    unsafe { TICKS }
}
