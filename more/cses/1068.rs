use std::io;

fn main() {
	/*
	let input: Vec<u8> = io::stdin().bytes()
		.filter_map(|p| p.ok())
		.collect();
	*/

	/*
	let mut input = String::new();
	io::stdin().read_to_string(&mut input).expect("stdin should be available");
	let mut numbers = input.split_ascii_whitespace().filter_map(|p| p.parse().ok());

	let mut N: i32 = numbers.next().expect("missing N");
	*/

	let mut input = String::new();
	io::stdin().read_line(&mut input).expect("expected stdin");
	let mut n: i64 = input.trim().parse().expect("expected N");

	while n != 1 {
		print!("{} ", n);
		if n % 2 == 0 {
			n /= 2;
		} else {
			n = n*3 + 1;
		}
	}

	print!("{}\n", n);
}