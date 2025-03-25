use std::io;

fn go(n: usize, t: &Vec<usize>, p: &Vec<usize>, day: usize, sum: usize, max: &mut usize) {
    if sum > *max {
        *max = sum;
    }
    if day < n {
        if day + t[day] <= n {
            go(n, t, p, day + t[day], sum + p[day], max);
        }
        go(n, t, p, day + 1, sum, max);
    }
}

fn main() {
    let mut input = String::new();
    io::stdin().read_line(&mut input).unwrap();
    let num: usize = input.trim().parse().unwrap();
    let mut max: usize = 0;
    let mut t: Vec<usize> = Vec::new();
    let mut p: Vec<usize> = Vec::new();

    for _ in 0..num {
        let mut input = String::new();
        io::stdin().read_line(&mut input).unwrap();
        let vs: Vec<String> = input
            .trim()
            .split_whitespace()
            .map(str::to_string)
            .collect();
        let tv: usize = vs[0].parse().unwrap();
        let pv: usize = vs[1].parse().unwrap();
        t.push(tv);
        p.push(pv);
    }

    //println!("{:?} {:?}", t, p);

    go(num, &t, &p, 0, 0, &mut max);
    println!("{}", max);
}
