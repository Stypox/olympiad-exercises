use std::process::Command;

use mpi::{request::WaitGuard, traits::{Communicator, Destination, Root, Source}};
use rayon::iter::{IntoParallelIterator, ParallelIterator};

extern crate reply;
fn main() {
    
    reply::launch();
}
/*

fn mpi(){
    let universe = mpi::initialize().unwrap();
    let world = universe.world();
    let size = world.size();
    let rank = world.rank();
    println!("Hello, world! I am rank {} of {}.", rank, size);
    
    let next_rank = (rank + 1) % size;
    let previous_rank = (rank - 1 + size) % size;

    let msg = vec![rank, 2 * rank, 4 * rank];



    mpi::request::scope(|scope| {
        let _sreq = WaitGuard::from(
            world
                .process_at_rank(next_rank)
                .immediate_send(scope, &msg[..]),
        );

        let (msg, status) = world.any_process().receive_vec();

        println!(
            "Process {} got message {:?}.\nStatus is: {:?}",
            rank, msg, status
        );
        let x = status.source_rank();
        assert_eq!(x, previous_rank);
        assert_eq!(vec![x, 2 * x, 4 * x], msg);

        let root_rank = 0;
        let root_process = world.process_at_rank(root_rank);

        let mut a;
        if world.rank() == root_rank {
            a = vec![2, 4, 8, 16];
            println!("Root broadcasting value: {:?}.", &a[..]);
        } else {
            a = vec![0; 4];
        }
        root_process.broadcast_into(&mut a[..]);
        println!("Rank {} received value: {:?}.", world.rank(), &a[..]);
        
        let t = Command::new("whoami").output().unwrap();
        println!("{:?}", String::from_utf8(t.stdout).unwrap());
        assert_eq!(&a[..], &[2, 4, 8, 16]);
    });
}*/

/*
#[cfg(test)]
mod tests {
    use rustsat::instances::SatInstance;
    use rustsat::solvers::{Solve, SolverResult};
    use rustsat::types::TernaryVal;

    #[test]
    fn sat_test() {
        let mut instance: SatInstance = SatInstance::new();
        let l1 = instance.new_lit();
        let l2 = instance.new_lit();
        instance.add_binary(l1, l2);
        instance.add_binary(!l1, l2);
        instance.add_unit(l1);
        let mut solver = rustsat_minisat::core::Minisat::default();
        solver.add_cnf(instance.into_cnf().0).unwrap();
        let res = solver.solve().unwrap();
        assert_eq!(res, SolverResult::Sat);
        let sol = solver.full_solution().unwrap();
        assert_eq!(sol[l1.var()], TernaryVal::True);
        assert_eq!(sol[l2.var()], TernaryVal::True);
    }
}
*/