let format = [%bs.raw
  {| new Intl.NumberFormat('cs-CZ', { style: 'currency', currency: 'CZK' }).format |}
];

[@react.component]
let make = (~value) => <> {format(value)} </>;