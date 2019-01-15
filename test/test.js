console.log("Hello World");

const Left = x => ({
    map: fn => Left(x),
    chain: fn => Left(x),
})

const Right = x => ({
    map: fn => Right(fn(x)),
    chain: fn => fn(x),
})

Right(3).map(x => x * x) // -> Right(9)
Left(3).map(x => x * x) // -> Left(3)

const result = Right(3)
    .map(x => x % 2 == 0
        ? Right(x)
        : Left('Odd'))

// const result = Right(3)
//     .chain(x => x % 2 == 0
//         ? Right(x)
//         : Left('Odd'))

console.log("Result",result); // -> Left('Odd')