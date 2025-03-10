use std::io;

fn go(target: i32, count: &mut i32) {
    if target == 0 {
        *count += 1;
    } else if target > 0 {
        go(target - 1, count);
        go(target - 2, count);
        go(target - 3, count);
    } else {
        // Do nothing
        //println!("Do nothing if target is negative: {}", target);
    }
}

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let num: i32 = input.trim().parse().unwrap();

    for _ in 0..num {
        let mut input = String::new();
        io::stdin().read_line(&mut input).unwrap();
        let num: i32 = input.trim().parse().unwrap();
        let mut count: i32 = 0;
        go(num, &mut count);
        println!("{}", count);
    }
}
