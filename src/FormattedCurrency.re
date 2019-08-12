let format = [%bs.raw
  {| new Intl.NumberFormat('en-US', { style: 'currency', currency: 'USD' }).format |}
];

[@react.component]
let make = (~value) => <> {format(value)} </>;