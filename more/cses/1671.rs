use std::{io, collections::BinaryHeap, cmp::Reverse};

struct Node {
	pub min_so_far: i64,
	pub to: Vec<(usize, i64)>
}

impl Clone for Node {
	fn clone(&self) -> Self {
		return Node { min_so_far: self.min_so_far, to: self.to.clone() };
	}
}

impl Default for Node {
	fn default() -> Self {
		return Node { min_so_far: i64::MAX, to: vec![] };
	}
}

fn main() {
	let mut input = String::new();
	io::stdin().read_line(&mut input).unwrap();
	let mut input = input.split_ascii_whitespace().filter_map(|p| p.parse().ok());
	let n = input.next().unwrap();
	let m = input.next().unwrap();

	let mut nodes = vec![Node::default(); n];
	for _ in 0..m {
		let mut input = String::new();
		io::stdin().read_line(&mut input).unwrap();
		let mut input = input.split_ascii_whitespace();
		let i = input.next().unwrap().parse::<usize>().unwrap() - 1;
		let j = input.next().unwrap().parse::<usize>().unwrap() - 1;
		let w = input.next().unwrap().parse().unwrap();
		nodes[i].to.push((j, w));
	}

	let mut pq: BinaryHeap<Reverse<(i64, usize)>> = BinaryHeap::new();
	pq.push(Reverse((0, 0)));
	while let Some(Reverse((dist, i))) = pq.pop() {
		if dist >= nodes[i].min_so_far {
			continue;
		}
		nodes[i].min_so_far = dist;

		for (j, w) in &nodes[i].to {
			pq.push(Reverse((dist + w, *j)));
		}
	}

	println!("{}", nodes.iter().map(|node| node.min_so_far.to_string() + " ").collect::<String>())
}