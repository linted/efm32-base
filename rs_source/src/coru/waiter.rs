use core::future::Future;
use core::pin::Pin;
use core::task::{Poll, Context};

use super::fib::*;

pub struct Waiter<'a> {
    pub (super) fib: &'a mut Fib,
}

impl<'a> Future for Waiter<'a> {
    type Output = ();

    fn poll(mut self: Pin<&mut Self>, _cx: &mut Context) -> Poll<Self::Output> {
        match self.fib.state {
            State::Halted => {
                self.fib.state = State::Running;
                Poll::Ready(())
            }
            State::Running => {
                self.fib.state = State::Halted;
                Poll::Pending
            }
        }
    }
}
