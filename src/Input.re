let getValue = e => ReactEvent.Form.target(e)##value;

[@react.component]
let make = (name, onChange, value) =>
  <input name onChange={getValue |> onChange(name)} value />;