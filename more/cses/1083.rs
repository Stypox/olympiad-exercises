use std::io;

fn main() {
	let mut input = String::new();
	io::stdin().read_line(&mut input).expect("expected stdin");
	let n: usize = input.trim().parse().expect("expected N");

	let mut input = String::new();
	io::stdin().read_line(&mut input).expect("expected stdin");
	let numbers = input.split_ascii_whitespace().filter_map(|p| p.parse().ok());

	let mut v = vec![false; n];
	numbers.for_each(|e: usize| v[e-1] = true);

	print!("{}\n", v.iter().position(|p| *p == false).unwrap() + 1);
}