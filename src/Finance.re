// A = P(1 + r/n)^nt

// n = 365 – assuming daily compounding
// P = Principal
// r = interest rate
// t = years
// A = accrued amount: principal + interest
let compoundInterest = (~rate, ~principal, ~yearlySavings) => {
  let numOfCompoundings = 1.0;
  let numOfPeriods = 25;
  let yearsArray = Belt.Array.range(1, numOfPeriods);

  let calculate = (~prevValue) => {
    (prevValue +. yearlySavings)
    *. (1.0 +. rate /. 100.0 /. numOfCompoundings)
    |> Js.Math.round;
  };

  Array.fold_left(
    (acc, year) => {
      let index = Array.length(acc) - 1;
      let maybePrevVal = index >= 0 ? acc[Array.length(acc) - 1] : None;
      let prevValue: float =
        switch (maybePrevVal) {
        | Some(maybePrevVal) => maybePrevVal
        | None => principal
        };

      Array.append(acc, [|Some(calculate(~prevValue))|]);
    },
    [||],
    yearsArray,
  );
};

let savings = (~income, ~spending) => income -. spending;

let savingsRate = (~income, ~spending) =>
  Js.Math.round(savings(~income, ~spending) /. income *. 100.0);