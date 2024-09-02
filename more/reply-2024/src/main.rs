use std::{collections::{HashMap, HashSet}, fmt::format, fs};

fn main() {
    for i in 0..5{
        let mut sol = Data::read_file(&format!("../inputs/{i}.txt"));
        sol.sol_2(&format!("../solutions/{i}.txt"));
    }
    
    //sol_1("out.txt");
}
struct Data{
    width: usize,
    height: usize,
    ///x, y
    golden: Vec<(usize, usize)>,
    /// x, y, score
    silver: Vec<(usize, usize, usize)>,
    ///id costo quantità
    tiles: HashMap<String,( usize, usize)>,
    output: String,
}

impl Data{
    fn read_file(p: &str)->Self{
        let f = fs::read(p).unwrap();
        let s = String::from_utf8(f).unwrap();
        
        let mut lines= s.lines();
        let l = lines.next().unwrap();
        let v: Vec<_> = l.split_ascii_whitespace().map(|x| x.trim().parse::<usize>().unwrap()).collect(); //   
        let width = v[0];
        let height = v[1];

        let golden_n = v[2];
        let silver_n = v[3];
        let tiles_n = v[4];
        let mut golden = Vec::new();
        for _ in 0..golden_n{
            let cur: Vec<usize> = lines.next().unwrap().split_ascii_whitespace().map(|x| x.parse::<usize>().unwrap()).collect();
            let x= cur[0];
            let y = cur[1];
            golden.push((x, y));

        }
        let mut silver = Vec::new();
        for _ in 0..silver_n{
            let cur: Vec<usize> = lines.next().unwrap().split_ascii_whitespace().map(|x| x.parse::<usize>().unwrap()).collect();
            let x= cur[0];
            let y = cur[1];
            let score = cur[2];
            silver.push((x, y, score));
            //println!("SP: x: {x} y: {y} score: {score}");
        }
        let mut tiles =HashMap::new();
        for _ in 0..tiles_n{
            let cur: Vec<&str> = lines.next().unwrap().split_ascii_whitespace().collect();
            let id= cur[0];
            let COST = cur[1].parse::<usize>().unwrap();
            let QUANTITY = cur[2].parse::<usize>().unwrap();
            tiles.insert(id.to_string(), (COST, QUANTITY));
        }
        golden.sort();
        Self {
            width,
            height,
            golden,
            silver,
            tiles,
            output: String::new() }

    }
}

fn sol_1(out: &str){
    let gp: HashSet<(i32, i32)> = vec![(60,22),(17,22),(70,17)].into_iter().collect();
    let mut file = String::new();
    for x in 0..80{
        for y in 1..39{
            if gp.contains(&(x,y)){
                continue;
            };
            file+=&format!("C {x} {y}\n");
        }
    }
    for x in 0..80{
        if x%2==0{
            file+=&format!("5 {x} 0\n");
            file+=&format!("A {x} 39\n");
        }else{
            file+=&format!("6 {x} 0\n");
            file+=&format!("9 {x} 39\n");
        }

    }
    fs::write(out, file);
}
#[repr(u8)]
#[derive(PartialEq)]
#[derive(Debug, Clone, Copy)]
enum Dir{
    Up = 8,
    Down = 4,
    Right = 1,
    Left = 2
}
impl Data{
    fn dikstra(&mut self, start: (usize, usize), end: (usize, usize),){
        let x_len = end.0-start.0+1;
        let y_len = (end.1 as i32 -start.1 as i32).abs() as usize +1;
        let mut grid: Vec<Vec<(i32, Vec<Dir>)>> = vec![vec![(i32::MAX, vec![]); y_len]; x_len];
        let v: HashMap<(usize, usize), usize> = if start.1<end.1{
            self.silver.iter().filter_map(|(x, y, score)|{
                Some(((x.checked_sub(start.0)?, y.checked_sub(start.1)?), *score))
            }).clone().collect()
        }else{
            self.silver.iter().filter_map(|(x, y, score)|{
                Some(((x.checked_sub(start.0)?, start.1.checked_sub(*y)?), *score))
            }).clone().collect()
        };
        fn test (g:&mut Vec<Vec<(i32, Vec<Dir>)>>, v: &HashMap<(usize, usize), usize>, x_len: usize, y_len: usize, x: usize, y: usize)->(i32, Vec<Dir>){
           // println!("{} {} {x_len} {y_len}", x, y);
            if x>=x_len || y>=y_len{
                return (i32::MIN, Vec::new());
            } else if x==x_len-1 && y==y_len-1 {
                return (0, vec![]);
            } else if g[x][y].0 != i32::MAX {
                return g[x][y].clone();
            }

            let mypoints = *v.get(&(x,y)).unwrap_or(&0usize) as i32;
            let (up_pts, mut up_path) = test( g, &v, x_len, y_len, x, y+1);
            let (right_pts, mut right_path) = test(g,  &v, x_len, y_len, x+1, y);
            if up_pts>right_pts {
                up_path.push(Dir::Up);
                g[x][y]=(up_pts+mypoints, up_path);
            } else {
                right_path.push(Dir::Right);
                g[x][y]= (right_pts+mypoints, right_path);
            }
            return g[x][y].clone()
        }

        let (points, path) = test(&mut grid, & v, x_len, y_len, 0 ,0 );
        let mut cur = start;
        for i in 0..path.len()-1{
            let cdir = path[i].clone();
            let ndir = path[i+1].clone();
            let nactual = if start.1<end.1{ if ndir == Dir::Up { Dir::Down } else if ndir == Dir::Down { Dir::Up } else { ndir } } else { ndir };
            match cdir{
                Dir::Up => {
                    let cactual = if start.1<end.1{ Dir::Up } else { Dir::Down };
                    let toprint = (cactual) as u8 | nactual as u8;
                    cur.1 = (cur.1 as i32 + if cactual == Dir::Down { -1 } else { 1 }) as usize;
                    self.output += &format!("{:X} {} {}\n", toprint, cur.0, cur.1);
                },
                _ => {
                    let cactual = Dir::Left;
                    cur.0 += 1;
                    let toprint = (cactual) as u8 | nactual as u8;
                    
                    self.output += &format!("{:X} {} {}\n", toprint, cur.0, cur.1);
                }
            }
            println!("{} {}", cur.0, cur.1);
        }
        println!("{}", points);
    }
    fn sol_2(&mut self, s: &str){
        for i in 0..self.golden.len()-1{
            let start = self.golden[i];
            let end = self.golden[i+1];
            println!("{:?} {:?}", start, end);
            self.dikstra(start, end);
        }
        fs::write(s, self.output.clone());
        println!("{}", self.output);
        
        let mut x = 145;
        let mut v: Vec<_> = self.silver.iter().filter_map(|(x, y, score)|{
            if *x>=145 && *x<682{
                Some(x)
            }else{
                None
            }
        } ).collect();
        v.sort();
        v.dedup();
    }
}