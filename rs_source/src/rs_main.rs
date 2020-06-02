use crate::coru::Executor;
use crate::bindings::*;

#[no_mangle]
pub fn rs_main() {
    let mut exe = Executor::new();

    exe.push(move | mut fib | async move {
        loop {
            toggle_pin(5,3);
            fib.tick_waiter(1000).await;
        }
    });

    exe.run();
}
