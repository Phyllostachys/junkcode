extern crate winapi;
extern crate user32;

fn main() {
    unsafe {
        user32::MessageBoxA(0 as *mut _,
                            "Hello from Rust in Windows!".as_ptr() as *mut _,
                            "Heyooo".as_ptr() as *mut _,
                            0);
    }
}
