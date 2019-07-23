let getValue = e => ReactEvent.Form.target(e)##value;

[@react.component]
let make = (~onChange, ~name, ~value) =>
  <input
    className="input"
    onChange={e => getValue(e) |> onChange(name)}
    value
  />;