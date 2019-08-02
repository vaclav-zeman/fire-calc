type resultRecord = {
  year: int,
  netWorth: float,
  changeInNetWorth: float,
  roi: float,
};

type resultList = list(resultRecord);

let getResultList = (~rate, ~principal, ~yearlySavings) => {
  let numOfCompoundings = 1.0;
  let numOfPeriods = 25;
  let yearsArray: array(int) = Belt.Array.range(1, numOfPeriods);

  let calculate = (~prevValue) => {
    (prevValue +. yearlySavings)
    *. (1.0 +. rate /. 100.0 /. numOfCompoundings)
    |> Js.Math.round;
  };

  Array.fold_left(
    (acc, year) => {
      let index = List.length(acc) - 1;
      let prevValue = index >= 0 ? List.nth(acc, index).netWorth : principal;
      let netWorth = calculate(~prevValue);
      let roi = netWorth -. yearlySavings -. prevValue;
      let changeInNetWorth = netWorth -. prevValue;
      let result = {year, netWorth, changeInNetWorth, roi};

      List.append(acc, [result]);
    },
    [],
    yearsArray,
  );
};

let getFIREYear = (~amounts, ~targetAmount) => {
  let amountsLength = List.length(amounts) - 1;
  let rec calculate = (~index=0) =>
    if (amountsLength === index) {
      None;
    } else if (List.nth(amounts, index).netWorth >= targetAmount) {
      Some(index + 1);
    } else {
      calculate(~index=index + 1);
    };

  calculate(~index=0);
};

let getSavingsRate = (~income, ~spending) =>
  Js.Math.floor_float((income -. spending) /. income *. 100.0);

let getSpendingBySavings = (~income, ~savingsRate) =>
  Js.Math.floor_float(income -. income *. savingsRate /. 100.0);