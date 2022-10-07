use std::io;
use std::cmp::max;

fn main() {
	let mut input = String::new();
	io::stdin().read_line(&mut input).expect("expected stdin");
	let input = input.trim();

	let mut prev: char = ' ';
	let mut count = 0;
	let mut maxcount = 0;
	for i in input.chars() {
		if prev != i {
			prev = i;
			count = 0;
		}
		count += 1;
		maxcount = max(count, maxcount);
	}

	print!("{}\n", maxcount);
}