use std::io;

fn main() {
	let mut input = String::new();
	io::stdin().read_line(&mut input).unwrap();
	let n: i64 = input.trim().parse().unwrap();

	let mut prev = [0 as i64; 7];
	prev[5] = 1;
	for _ in 0..n {
		prev[6] = prev.iter().take(6).fold(0, |sum, e| sum + e) % 1_000_000_007;
		for i in 0..6 {
			prev[i] = prev[i+1];
		}
	}

	println!("{}", prev[6]);
}