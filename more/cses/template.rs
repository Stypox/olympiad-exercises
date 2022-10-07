use std::io;

fn main() {
	let mut input = String::new();
	io::stdin().read_line(&mut input).expect("expected stdin");
	let n: i64 = input.trim().parse().expect("expected N");

	print!("{}\n", n);
}