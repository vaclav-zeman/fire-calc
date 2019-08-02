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
  let handleBlur = (name, _) => Form.UpdateSavingsRate(name) |> dispatchForm;
  let handleSubmit = e => {
    ReactEvent.Synthetic.preventDefault(e);
    dispatchForm(Form.Submit);
    dispatchData(Data.Calculate(formState));
  };

  <main className="container">
    <form className="section" onSubmit=handleSubmit>
      <h1 className="title"> {"FIRE Calculator" |> ReasonReact.string} </h1>
      <Label>
        {"Currently Saved / Invested" |> ReasonReact.string}
        <Input
          onChange=handleChange
          onBlur=handleBlur
          name=Form.CurrentBalance
          value={formState.currBalance}
        />
      </Label>
      <Label>
        {"Annual Income" |> ReasonReact.string}
        <Input
          onChange=handleChange
          onBlur=handleBlur
          name=Form.Income
          value={formState.income}
        />
      </Label>
      <Label>
        {"Annual Expenses" |> ReasonReact.string}
        <Input
          onChange=handleChange
          onBlur=handleBlur
          name=Form.Spending
          value={formState.spending}
        />
      </Label>
      <Label>
        {"Savings rate (%)" |> ReasonReact.string}
        <Input
          onChange=handleChange
          name=Form.SavingsRate
          onBlur=handleBlur
          value={formState.savingsRate}
        />
      </Label>
      <Label>
        {"Expected annual return (%)" |> ReasonReact.string}
        <Input
          onChange=handleChange
          onBlur=handleBlur
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