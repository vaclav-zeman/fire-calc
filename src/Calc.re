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
  compoundInterest: list(float),
  currBalance: string,
  hasSubmitted: bool,
  income: string,
  savingsRate: string,
  spending: string,
  targetAmount: string,
  targetYear: string,
};

let initialState = {
  annualReturn: "7",
  compoundInterest: [],
  currBalance: "0",
  hasSubmitted: false,
  income: "30000",
  savingsRate: "67%",
  spending: "10000",
  targetAmount: "",
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
    let yearlySavings =
      Finance.savings(
        ~income=float_of_string(state.income),
        ~spending=float_of_string(state.spending),
      )
      *. 12.0;
    let compoundInterest =
      Finance.compoundInterest(
        ~rate=float_of_string(state.annualReturn),
        ~principal=float_of_string(state.currBalance),
        ~yearlySavings,
      );
    let targetAmount = float_of_string(state.spending) *. 12.0 *. 25.0;
    let targetYear =
      Finance.getFIREYear(~amounts=compoundInterest, ~targetAmount);

    {
      ...state,
      hasSubmitted: true,
      targetAmount: targetAmount |> Js.Float.toString,
      compoundInterest,
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

  <main className="container">
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
    {state.hasSubmitted === true
       ? <>
           <Result
             targetAmount={state.targetAmount}
             targetYear={state.targetYear}
           />
           <Table data={state.compoundInterest} />
         </>
       : ReasonReact.null}
  </main>;
};