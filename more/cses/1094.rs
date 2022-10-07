use std::io;

fn main() {
	let mut input = String::new();
	io::stdin().read_line(&mut input).unwrap();
	let n: i64 = input.trim().parse().unwrap();

	let mut input = String::new();
	io::stdin().read_line(&mut input).unwrap();
	let numbers = input.split_ascii_whitespace().filter_map(|p| p.parse::<i64>().ok());

	let mut res = 0;
	let mut prev = 0;
	for e in numbers {
		if e < prev {
			res += prev - e;
		} else {
			prev = e;
		}
	}

	print!("{}\n", res);
}