use core::future::Future;
use alloc::boxed::Box;
use core::pin::Pin;
use alloc::collections::vec_deque::VecDeque;
use core::task::{Poll, Context};

use super::fib::{Fib, State};
use super::waker;


pub struct Executor {
    fibs: VecDeque<Pin<Box<dyn Future<Output=()>>>>,
}

impl Executor {
    pub fn new() -> Self {
        Executor {
            fibs: VecDeque::new(),
        }
    }


    pub fn push<C, F>(&mut self, closure: C)
    where
        F: Future<Output=()> + 'static,
        C: FnOnce(Fib) -> F,
    {
        let fib = Fib { state: State::Running };
        self.fibs.push_back(Box::pin(closure(fib)));
    }


    pub fn run(&mut self) {
        let waker = waker::create();
        let mut context = Context::from_waker(&waker);

        while let Some(mut fib) = self.fibs.pop_front() {
            match fib.as_mut().poll(&mut context) {
                Poll::Pending => {
                    self.fibs.push_back(fib);
                },
                Poll::Ready(()) => {},
            }
        }
    }
}
