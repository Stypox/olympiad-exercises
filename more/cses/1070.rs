use std::io;

fn main() {
	let mut input = String::new();
	io::stdin().read_line(&mut input).unwrap();
	let n: i64 = input.trim().parse().unwrap();

	if n == 1 {
		print!("1")
	} else if n == 2 || n == 3 {
		print!("NO SOLUTION")
	} else if n == 4 || n == 5 {
		if n == 5 {
			print!("5 ")
		}
		print!("3 1 4 2")
	} else {
		if n % 2 != 0 {
			print!("{} ", n)
		}

		(1..=n/2).flat_map(|i| [i, n/2+i]).for_each(|i| print!("{} ", i))
	}
	println!()
}