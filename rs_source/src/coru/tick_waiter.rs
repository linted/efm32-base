use core::future::Future;
use core::pin::Pin;
use core::task::{Poll, Context};

use super::fib::*;
use crate::current_ticks;

pub struct TickWaiter<'a> {
    pub (super) fib: &'a mut Fib,
    pub (super) end: u32,
}

impl<'a> Future for TickWaiter<'a> {
    type Output = ();

    fn poll(mut self: Pin<&mut Self>, _cx: &mut Context) -> Poll<Self::Output> {
        match self.fib.state {
            State::Halted => {
                if self.end <= unsafe { current_ticks() } {
                    self.fib.state = State::Running;
                    Poll::Ready(())
                }
                else {
                    Poll::Pending
                }
            }
            State::Running => {
                self.fib.state = State::Halted;
                Poll::Pending
            }
        }
    }
}
