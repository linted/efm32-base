use super::waiter::Waiter;
use super::tick_waiter::TickWaiter;
use crate::current_ticks;

pub enum State {
    Halted,
    Running,
}

pub struct Fib {
    pub (super) state: State,
}

impl Fib {
    pub fn waiter<'a>(&'a mut self) -> Waiter<'a> {
        Waiter { fib: self }
    }

    pub fn tick_waiter<'a>(&'a mut self, ticks: u32) -> TickWaiter<'a> {
        TickWaiter {
            fib: self,
            end: unsafe { current_ticks() } + ticks,
        }
    }
}
