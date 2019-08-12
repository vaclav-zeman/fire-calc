open FormStore;
open DataStore;

[@react.component]
let make = () => {
  let (dataState, dispatchData) =
    React.useReducer(Data.reducer, Data.initialState);
  let (formState, dispatchForm) =
    React.useReducer(Form.reducer, Form.initialState);

  let handleChange = (name, value) =>
    Form.InputChange(name, value) |> dispatchForm;
  let handleSubmit = e => {
    ReactEvent.Synthetic.preventDefault(e);
    dispatchForm(Form.Submit);
    dispatchData(Data.Calculate(formState));
  };

  <main className="container">
    <form className="section" onSubmit=handleSubmit>
      <article className="content">
        <h1 className="title has-text-centered">
          {"FIRE Calculator - When can you retire early?" |> ReasonReact.string}
        </h1>
        <p>
          {"For the first 10 years, the regular savings make the biggest impact on net worth."
           |> ReasonReact.string}
        </p>
        {"Currency is irrelevant." |> ReasonReact.string}
      </article>
      <Label>
        {"Currently Saved / Invested" |> ReasonReact.string}
        <Input
          onChange=handleChange
          name=Form.CurrentBalance
          value={formState.currBalance}
        />
      </Label>
      <Label>
        {"Annual Income" |> ReasonReact.string}
        <Input
          onChange=handleChange
          name=Form.Income
          value={formState.income}
        />
      </Label>
      <Label>
        {"Annual Expenses" |> ReasonReact.string}
        <Input
          onChange=handleChange
          name=Form.Spending
          value={formState.spending}
        />
      </Label>
      // <Label>
      //   {"Savings rate (%)" |> ReasonReact.string}
      //   <Input
      //     onChange=handleChange
      //     name=Form.SavingsRate
      //     onBlur=handleBlur
      //     value={formState.savingsRate}
      //   />
      // </Label>
      <Label>
        {"Expected annual return (%)" |> ReasonReact.string}
        <Input
          onChange=handleChange
          name=Form.AnnualReturn
          value={formState.annualReturn}
        />
      </Label>
      <button className="button is-primary">
        {"Calculate" |> ReasonReact.string}
      </button>
    </form>
    {formState.hasSubmitted === true
       ? <>
           <Result
             targetAmount={dataState.targetAmount}
             targetYear={dataState.targetYear}
             savingsRate={formState.savingsRate}
           />
           <Table
             annualReturn={formState.annualReturn}
             data={dataState.resultList}
           />
         </>
       : ReasonReact.null}
  </main>;
};