use std::io;

fn go(target: i32) -> i32 {
    if target == 0 {
        return 1;
    } else if target > 0 {
        return go(target - 1) + go(target - 2) + go(target - 3);
    } else {
        return 0;
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
        println!("{}", go(num));
    }
}
