let format = [%bs.raw {| new Intl.NumberFormat(undefined).format |}];

[@react.component]
let make = (~value) => <> {format(value)} </>;