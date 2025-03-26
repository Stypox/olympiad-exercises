use std::env;
use std::path::PathBuf;

fn main() {
    let crate_dir = env::var("CARGO_MANIFEST_DIR").unwrap();
    let cbindings = crate_dir.clone() + "/csrc/bindings.hpp";
    let rbindings = crate_dir.clone() + "/rustbindings.hpp";

    let out_path = PathBuf::from(env::var("OUT_DIR").unwrap());

    // The bindgen::Builder is the main entry point
    // to bindgen, and lets you build up options for
    // the resulting bindings.
    let bindings = bindgen::Builder::default()
        // The input header we would like to generate
        // bindings for.
        .header(&cbindings)
        // Tell cargo to invalidate the built crate whenever any of the
        // included header files changed.
        .parse_callbacks(Box::new(bindgen::CargoCallbacks::new()))
        // Finish the builder and generate the bindings.
        .generate()
        // Unwrap the Result and panic on failure.
        .expect("Unable to generate bindings");

    bindings
        .write_to_file(out_path.join("bindings.rs"))
        .expect("Couldn't write bindings!");

    //let bind = cbindgen::generate(&crate_dir).unwrap();
    let bind = cbindgen::Builder::new()
        .with_crate(&crate_dir)
        .with_language(cbindgen::Language::Cxx)
        .with_include_guard("TEST_H")
        .with_include("csrc/bindings.hpp")
        //.with_std_types(false)
        .with_no_includes()
        .with_cpp_compat(true)
        .generate()
        .expect("Unable to generate bindings");
    //println!("{:?}", bind.struct_exists(cbindgen::));
    bind.write_to_file(rbindings);
    let mut b = cc::Build::new();
    let b = b
        .cpp(true)
        .file("csrc/cmain.cpp")
        .opt_level(3)
        .define("RUST1", None);


    #[cfg(debug_assertions)]
        b.define("DEBUG", None);

        b.compile("cmain");
    let out_path = out_path.display().to_string();
    println!("cargo:rerun-if-changed=NULL");
    println!("cargo::rerun-if-changed=src/lib.rs");
    println!("cargo:rustc-link-search={}", out_path);
}
