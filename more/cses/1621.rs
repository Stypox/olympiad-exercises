use std::{io, collections::HashSet};

fn main() {
	let mut input = String::new();
	io::stdin().read_line(&mut input).unwrap();
	let n: i64 = input.trim().parse().unwrap();

	let mut input = String::new();
	io::stdin().read_line(&mut input).unwrap();
	let numbers = input.split_ascii_whitespace().filter_map(|p| p.parse::<i64>().ok());

	print!("{}\n", numbers.collect::<HashSet<i64>>().len());
}