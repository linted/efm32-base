#![allow(non_snake_case)]
use crate::state::inc_ticks;

#[no_mangle]
fn SysTick_Handler() {
    inc_ticks()
}
