[@react.component]
let make = (~targetYear, ~targetAmount, ~savingsRate) =>
  <div className="section">
    <div className="box">
      <h2 className="title is-3">
        {"Retire in: " |> ReasonReact.string}
        {targetYear |> ReasonReact.string}
        {" years" |> ReasonReact.string}
      </h2>
      <h3 className="title is-4">
        {"With savings rate: " |> ReasonReact.string}
        savingsRate
      </h3>
      <h3 className="title is-4">
        {"Needed for retirement: " |> ReasonReact.string}
        <FormattedCurrency value=targetAmount />
      </h3>
    </div>
  </div>;