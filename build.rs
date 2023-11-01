use std::env;

fn main() {
    let current_dir = env::current_dir().unwrap();
    println!("cargo:rustc-link-search=native={}", current_dir.display());

    cxx_build::bridge("src/main.rs")
        .file("src/wrapper.cpp")
        .flag_if_supported("-std=c++20")
        .compile("cxx-test");

    println!("cargo:rustc-link-lib=static=test");
    println!("cargo:rerun-if-changed=/src/*");
}
