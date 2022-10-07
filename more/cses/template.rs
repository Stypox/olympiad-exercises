use std::io;

fn main() {
	let mut input = String::new();
	io::stdin().read_line(&mut input).unwrap();
	let n: i64 = input.trim().parse().unwrap();

	println!("{}", n);
}