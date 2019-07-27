let getValue = e => ReactEvent.Form.target(e)##value;

[@react.component]
let make = (~onChange, ~onBlur=?, ~name, ~value) =>
  <input
    className="input"
    onChange={e => getValue(e) |> onChange(name)}
    onBlur={
      switch (onBlur) {
      | Some(onBlur) => onBlur(name)
      | None => Js.log
      }
    }
    value
  />;