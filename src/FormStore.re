module Form = {
  type fields =
    | AnnualReturn
    | CurrentBalance
    | Income
    | SavingsRate
    | Spending;

  type formAction =
    | InputChange(fields, string)
    | Submit
    | UpdateSavingsRate;

  type state = {
    annualReturn: string,
    currBalance: string,
    income: string,
    spending: string,
    savingsRate: string,
    hasSubmitted: bool,
  };

  let initialState = {
    annualReturn: "7",
    currBalance: "0",
    hasSubmitted: false,
    income: "360000",
    savingsRate: "66%",
    spending: "120000",
  };

  let updateFormState = (state: state, field: fields, value: string) =>
    switch (field) {
    | AnnualReturn => {...state, annualReturn: value}
    | CurrentBalance => {...state, currBalance: value}
    | Income => {...state, income: value}
    | Spending => {...state, spending: value}
    | SavingsRate => state
    };

  let reducer = (state, action) =>
    switch (action) {
    | InputChange(field, value) => updateFormState(state, field, value)
    | UpdateSavingsRate => {
        ...state,
        savingsRate:
          (
            Finance.savingsRate(
              ~income=float_of_string(state.income),
              ~spending=float_of_string(state.spending),
            )
            |> Js.Float.toString
          )
          ++ "%",
      }
    | Submit => {...state, hasSubmitted: true}
    };
};