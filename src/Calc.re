type fields =
  | AnnualReturn
  | CurrentBalance
  | Income
  | SavingsRate
  | Spending;

type action =
  | InputChange(fields, string)
  | Submit
  | UpdateSavingsRate;

type state = {
  annualReturn: string,
  income: string,
  spending: string,
  compoundInterest: list(float),
  currBalance: string,
  targetAmount: string,
  savingsRate: string,
  targetYear: string,
};

let initialState = {
  annualReturn: "7",
  income: "30000",
  spending: "10000",
  currBalance: "0",
  compoundInterest: [],
  targetAmount: "",
  savingsRate: "67%",
  targetYear: "",
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
  | Submit =>
    let compoundInterest =
      Finance.compoundInterest(
        ~rate=7.0,
        ~principal=float_of_string(state.currBalance),
        ~yearlySavings=
          Finance.savings(
            ~income=float_of_string(state.income),
            ~spending=float_of_string(state.spending),
          )
          *. 12.0,
      );
    let targetAmount = float_of_string(state.spending) *. 12.0 *. 25.0;
    let targetYear =
      Finance.getFIREYear(~amounts=compoundInterest, ~targetAmount);

    {
      ...state,
      targetAmount: targetAmount |> Js.Float.toString,
      compoundInterest:
        Finance.compoundInterest(
          ~rate=float_of_string(state.annualReturn),
          ~principal=float_of_string(state.currBalance),
          ~yearlySavings=
            Finance.savings(
              ~income=float_of_string(state.income),
              ~spending=float_of_string(state.spending),
            )
            *. 12.0,
        ),
      targetYear:
        switch (targetYear) {
        | Some(year) => year |> string_of_int
        | None => "Not in range"
        },
    };
  };

[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer(reducer, initialState);

  let handleChange = (name, value) => InputChange(name, value) |> dispatch;
  let handleBlur = (name, e) => UpdateSavingsRate |> dispatch;
  let handleSubmit = e => {
    ReactEvent.Synthetic.preventDefault(e);
    Submit |> dispatch;
  };

  <section className="container">
    <form className=" section" onSubmit=handleSubmit>
      <h1 className="title"> {"FIRE Calculator" |> ReasonReact.string} </h1>
      <Label>
        {"Current Balance" |> ReasonReact.string}
        <Input
          onChange=handleChange
          onBlur=handleBlur
          name=CurrentBalance
          value={state.currBalance}
        />
      </Label>
      <Label>
        {"Income (monthly)" |> ReasonReact.string}
        <Input
          onChange=handleChange
          onBlur=handleBlur
          name=Income
          value={state.income}
        />
      </Label>
      <Label>
        {"Spending (monthly)" |> ReasonReact.string}
        <Input
          onChange=handleChange
          onBlur=handleBlur
          name=Spending
          value={state.spending}
        />
      </Label>
      <Label>
        {"Savings rate" |> ReasonReact.string}
        <Input
          onChange=handleChange
          name=SavingsRate
          value={state.savingsRate}
        />
      </Label>
      <Label>
        {"Expected annual return (%)" |> ReasonReact.string}
        <Input
          onChange=handleChange
          onBlur=handleBlur
          name=AnnualReturn
          value={state.annualReturn}
        />
      </Label>
      <button className="button is-primary">
        {"Calculate" |> ReasonReact.string}
      </button>
    </form>
    <div className="section">
      <h2>
        {"Needed for retirement: " |> ReasonReact.string}
        <FormattedCurrency value={state.targetAmount} />
        <br />
        {"Achievable in year: " |> ReasonReact.string}
        {state.targetYear |> ReasonReact.string}
      </h2>
      {Belt.List.mapWithIndex(state.compoundInterest, (index, amount) =>
         <h1>
           {index + 1 |> string_of_int |> ReasonReact.string}
           {" - " |> ReasonReact.string}
           <FormattedCurrency value=amount />
         </h1>
       )
       |> Array.of_list
       |> ReasonReact.array}
    </div>
  </section>;
};