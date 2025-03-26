#![allow(unused)]
pub(crate) mod cbind {
    include!(concat!(env!("OUT_DIR"), "/bindings.rs"));
}
#[link(name = "cmain")]
unsafe extern "C" {}
/*unsafe extern "C" {}*/
#[unsafe(no_mangle)]
pub extern "C" fn hello_from_rust() {
    println!("Hello from Rust again!");
}

#[unsafe(no_mangle)]
pub extern "C" fn launch() {
    println!("Program launched from rust");
    unsafe {
        cbind::solve();
        //cbind::run_something_in_c();
    }
}
#[derive(Debug)]
struct ProblemRust{
    s: String
}

#[derive(Debug)]
struct ProblemShared{
    c: i16,
}

//#[repr(C)]
#[derive(Debug)]
pub struct Problem {
    c: cbind::ProblemCpp,
    z: ProblemRust,
    s: ProblemShared
}

#[unsafe(no_mangle)]
pub extern "C" fn new_my_struct(onlyc: cbind::ProblemCpp) -> *mut Problem {
    Box::into_raw(Box::new(Problem{
        c: onlyc,
        z: ProblemRust{
            s: "Hello from Rust".to_string()
        },
        s: ProblemShared{
            c: 0
        }
    }))
}


#[unsafe(no_mangle)]
pub extern "C" fn drop_struct(problem: *mut Problem)  {
    unsafe {
        let _ = Box::from_raw(problem);
    }
}