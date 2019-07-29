type fields =
  | Income
  | CurrentBalance
  | Spending
  | SavingsRate;

type action =
  | InputChange(fields, string)
  | Submit
  | UpdateSavingsRate;

type state = {
  income: string,
  spending: string,
  compoundInterest: list(float),
  currBalance: string,
  targetAmount: string,
  savingsRate: string,
  targetYear: string,
};

let initialState = {
  income: "30000",
  spending: "10000",
  currBalance: "0",
  compoundInterest: [],
  targetAmount: "",
  savingsRate: "",
  targetYear: "",
};

let updateFormState = (state: state, field: fields, value: string) =>
  switch (field) {
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
        Js.Float.toString(
          Finance.savingsRate(
            ~income=float_of_string(state.income),
            ~spending=float_of_string(state.spending),
          ),
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
    let targetAmount = float_of_string(state.spending) *. 25.0;
    let targetYear =
      Finance.getFIREYear(~amounts=compoundInterest, ~targetAmount);

    {
      ...state,
      targetAmount: targetAmount |> Js.Float.toString,
      compoundInterest:
        Finance.compoundInterest(
          ~rate=7.0,
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
          name=CurrentBalance
          value={state.currBalance}
        />
      </Label>
      <Label>
        {"Income" |> ReasonReact.string}
        <Input
          onChange=handleChange
          onBlur=handleBlur
          name=Income
          value={state.income}
        />
      </Label>
      <Label>
        {"Spending" |> ReasonReact.string}
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
      <button className="button is-primary">
        {"Calculate" |> ReasonReact.string}
      </button>
    </form>
    <div className="section">
      <h2>
        {"Needed for retirement:" |> ReasonReact.string}
        {state.targetAmount |> ReasonReact.string}
        <br />
        {"Achievable in year:" |> ReasonReact.string}
        {state.targetYear |> ReasonReact.string}
      </h2>
      {List.map(
         amount =>
           <h1> {Js.Float.toString(amount) |> ReasonReact.string} </h1>,
         state.compoundInterest,
       )
       |> Array.of_list
       |> ReasonReact.array}
    </div>
  </section>;
};