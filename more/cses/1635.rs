use std::io;

fn main() {
	let mut input = String::new();
	io::stdin().read_line(&mut input).unwrap();
	let mut input = input.split_ascii_whitespace().filter_map(|p| p.parse().ok());
	let _n = input.next().unwrap();
	let x = input.next().unwrap();

	let mut input = String::new();
	io::stdin().read_line(&mut input).unwrap();
	let nums = input.split_ascii_whitespace().filter_map(|p| p.parse().ok()).collect();

	fn rec(x: i64, nums: &Vec<i64>, mem: &mut Vec<i64>) -> i64 {
		if x < 0 {
			return 0;
		} else if x == 0 {
			return 1;
		} else if mem[x as usize] == -1 {
			mem[x as usize] = nums.iter().fold(0, |sum, num| (sum + rec(x - num, nums, mem)) % 1_000_000_007);
		}
		return mem[x as usize];
	}

	let mut mem: Vec<i64> = vec![-1; x as usize + 1];
	println!("{}", rec(x, &nums, &mut mem));
}