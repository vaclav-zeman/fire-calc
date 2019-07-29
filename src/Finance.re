// A = P(1 + r/n)^nt

// n = 365 – assuming daily compounding
// P = Principal
// r = interest rate
// t = years
// A = accrued amount: principal + interest
let compoundInterest = (~rate, ~principal, ~yearlySavings) => {
  let numOfCompoundings = 1.0;
  let numOfPeriods = 25;
  let yearsArray = Belt.List.fromArray(Belt.Array.range(1, numOfPeriods));

  let calculate = (~prevValue) => {
    (prevValue +. yearlySavings)
    *. (1.0 +. rate /. 100.0 /. numOfCompoundings)
    |> Js.Math.round;
  };

  List.fold_left(
    (acc, year) => {
      let index = List.length(acc) - 1;
      let prevValue = index >= 0 ? List.nth(acc, index) : principal;
      List.append(acc, [calculate(~prevValue)]);
    },
    [],
    yearsArray,
  );
};

let getFIREYear = (~amounts, ~targetAmount, ~index) => {
  2;
};

let savings = (~income, ~spending) => income -. spending;

let savingsRate = (~income, ~spending) =>
  Js.Math.round(savings(~income, ~spending) /. income *. 100.0);