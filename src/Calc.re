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
  resultList: Finance.resultList,
  currBalance: string,
  hasSubmitted: bool,
  income: string,
  savingsRate: string,
  spending: string,
  targetAmount: float,
  targetYear: option(int),
};

let initialState = {
  annualReturn: "7",
  resultList: [],
  currBalance: "0",
  hasSubmitted: false,
  income: "360000",
  savingsRate: "66%",
  spending: "120000",
  targetAmount: 0.0,
  targetYear: None,
};

// 25x of yearly expenses is considered save for retiring for ordinary person
let magicConstant = 25.0;

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
      );
    let resultList: Finance.resultList =
      Finance.getResultList(
        ~rate=float_of_string(state.annualReturn),
        ~principal=float_of_string(state.currBalance),
        ~yearlySavings,
      );
    let targetAmount = float_of_string(state.spending) *. magicConstant;
    let targetYear = Finance.getFIREYear(~amounts=resultList, ~targetAmount);

    {...state, hasSubmitted: true, targetAmount, resultList, targetYear};
  };

[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer(reducer, initialState);

  let handleChange = (name, value) => InputChange(name, value) |> dispatch;
  let handleBlur = (_, _) => UpdateSavingsRate |> dispatch;
  let handleSubmit = e => {
    ReactEvent.Synthetic.preventDefault(e);
    Submit |> dispatch;
  };

  <main className="container">
    <form className="section" onSubmit=handleSubmit>
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
        {"Annual Income" |> ReasonReact.string}
        <Input
          onChange=handleChange
          onBlur=handleBlur
          name=Income
          value={state.income}
        />
      </Label>
      <Label>
        {"Annual Expenses" |> ReasonReact.string}
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
             savingsRate={state.savingsRate}
           />
           <Table annualReturn={state.annualReturn} data={state.resultList} />
         </>
       : ReasonReact.null}
  </main>;
};