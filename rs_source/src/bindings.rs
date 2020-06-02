
mod imports {

extern "C" {
    pub fn toggle_pin(pin: u32, t: u32);
}

}

pub fn toggle_pin(pin: u32, t: u32) {
    unsafe { imports::toggle_pin(pin, t) }
}
