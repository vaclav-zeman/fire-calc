let format = [%bs.raw
  {| new Intl.NumberFormat(undefined, { minimumFractionDigits: 2 }).format |}
];

[@react.component]
let make = (~value) => <> {format(value)} </>;