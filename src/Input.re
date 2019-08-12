let getValue = e => ReactEvent.Form.target(e)##value;

[@react.component]
let make = (~onChange, ~onBlur=?, ~name, ~value) =>
  <input
    className="input"
    onChange={e => getValue(e) |> onChange(name)}
    type_="number"
    min=0
    required=true
    value
  />;