use std::ffi::CString;

#[cxx::bridge]
mod ffi {
    unsafe extern "C++" {
        include!("cxx_test/src/wrapper.hpp");

        type ObjectRepository;

        fn create() -> UniquePtr<ObjectRepository>;
        fn size(&self) -> usize;
        unsafe fn insert(self: Pin<&mut ObjectRepository>, v: *mut f32, size: usize) -> usize;
        fn remove(self: Pin<&mut ObjectRepository>, i: usize);

        fn header();
        unsafe fn stat(op: *const c_char);
    }
}

fn stat(op: &str) {
    unsafe {
        ffi::stat(CString::new(op).expect("CString::new is failure").as_ptr());
    }
}

fn main() {
    const DIM: usize = 128;
    const SIZE: usize = 1000000;

    ffi::header();
    stat("start");

    let mut vectors = vec![[0.0 as f32; DIM]; SIZE];
    for (i, vector) in vectors.iter_mut().enumerate() {
        vector[0] = i as f32;
    }

    let mut o = ffi::create();

    for _ in 0..100 {
        stat("init");
        let mut ids = vec![0 as usize; SIZE];
        for (i, v) in vectors.iter_mut().enumerate() {
            unsafe {
                ids[i] = o.pin_mut().insert(v.as_mut_ptr(), DIM);
            }
        }
        stat("insert");

        for id in ids {
            o.pin_mut().remove(id);
        }
        stat("remove");
    }

    stat("finish");
}
