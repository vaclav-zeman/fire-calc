type fields =
  | Income
  | Spending
  | Years;

type action =
  | InputChange(fields, string);

type state = {
  income: string,
  spending: string,
  years: string,
};

let getValue = e => ReactEvent.Form.target(e)##value;

let updateFormState = (state: state, field: fields, value: string) =>
  switch (field) {
  | Income => {...state, income: value}
  | Spending => {...state, spending: value}
  | Years => {...state, years: value}
  };

[@react.component]
let make = () => {
  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | InputChange(field, value) => updateFormState(state, field, value)
        },
      {income: "0", spending: "0", years: "0"},
    );

  let handleChange = (name, value) => InputChange(name, value) |> dispatch;

  <form>
    {"FIRE Calculator" |> ReasonReact.string}
    <Label>
      {"Income" |> ReasonReact.string}
      <input
        onChange={e => getValue(e) |> handleChange(Income)}
        value={state.income}
      />
    </Label>
    <Label>
      {"Spending" |> ReasonReact.string}
      <input
        onChange={e => getValue(e) |> handleChange(Spending)}
        value={state.spending}
      />
    </Label>
    <Label>
      {"Years" |> ReasonReact.string}
      <input
        onChange={e => getValue(e) |> handleChange(Years)}
        value={state.years}
      />
    </Label>
    <button> {"Calculate" |> ReasonReact.string} </button>
  </form>;
};