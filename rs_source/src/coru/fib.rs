use super::waiter::Waiter;
use super::tick_waiter::TickWaiter;
use crate::state::current_ticks;

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

    pub fn tick_waiter<'a>(&'a mut self, ticks: u64) -> TickWaiter<'a> {
        TickWaiter {
            fib: self,
            end: current_ticks() + ticks,
        }
    }
}
