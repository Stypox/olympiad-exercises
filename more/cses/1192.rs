use std::io;

fn main() {
	let mut input = String::new();
	io::stdin().read_line(&mut input).unwrap();
	let mut input = input.split_ascii_whitespace().filter_map(|p| p.parse::<usize>().ok());
	let (n, m) = (input.next().unwrap(), input.next().unwrap());

	let mut mat = vec![vec![false; m]; n];
	for i in 0..n {
		let mut input = String::new();
		io::stdin().read_line(&mut input).unwrap();
		input.trim().char_indices().filter(|(_, c)| *c == '#').for_each(|(j, _)| mat[i][j] = true);
	}

	fn bucket_fill(i: usize, j: usize, n: usize, m: usize, mat: &mut Vec<Vec<bool>>) {
		if !(0..n).contains(&i) || !(0..m).contains(&j) || mat[i][j] {
			return;
		}
		mat[i][j] = true;
		bucket_fill(i+1, j, n, m, mat);
		bucket_fill(i, j+1, n, m, mat);
		bucket_fill(i, j-1, n, m, mat);
		bucket_fill(i-1, j, n, m, mat);
	}

	let mut rooms = 0;
	for i in 0..n {
		for j in 0..m {
			if !mat[i][j] {
				rooms += 1;
				bucket_fill(i, j, n, m, &mut mat);
			}
		}
	}

	println!("{}", rooms);
}