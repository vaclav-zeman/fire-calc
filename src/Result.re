[@react.component]
let make = (~targetYear, ~targetAmount) =>
  <div className="section">
    <div className="box">
      <h2 className="title is-3">
        {"Retire in: " |> ReasonReact.string}
        {targetYear |> ReasonReact.string}
        {" years" |> ReasonReact.string}
      </h2>
      <strong className="title is-4">
        {"Needed for retirement: " |> ReasonReact.string}
        <FormattedCurrency value=targetAmount />
      </strong>
    </div>
  </div>;