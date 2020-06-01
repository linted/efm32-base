use core::alloc::{GlobalAlloc, Layout};

pub struct BGAlloc;

extern "C" {
    fn bg_malloc(size: usize) -> *mut u8;
    fn bg_free(ptr: *mut u8);
}

unsafe impl GlobalAlloc for BGAlloc {
    unsafe fn alloc(&self, layout: Layout) -> *mut u8 {
        bg_malloc(layout.size())
    }

    unsafe fn dealloc(&self, ptr: *mut u8, _layout: Layout) {
        bg_free(ptr)
    }
}
