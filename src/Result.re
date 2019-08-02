[@react.component]
let make =
    (~targetYear: option(int), ~targetAmount: float, ~savingsRate: string) => {
  let year =
    switch (targetYear) {
    | Some(year) => year |> string_of_int
    | None => "Not in range"
    };

  <div className="section">
    <div className="box">
      <h2 className="title is-3">
        {"Retire in: " |> ReasonReact.string}
        {year |> ReasonReact.string}
        {" years" |> ReasonReact.string}
      </h2>
      <h3 className="title is-4">
        {"With savings rate: " |> ReasonReact.string}
        {savingsRate |> ReasonReact.string}
      </h3>
      <h3 className="title is-4">
        {"Needed for retirement: " |> ReasonReact.string}
        <FormattedCurrency value=targetAmount />
      </h3>
    </div>
  </div>;
};