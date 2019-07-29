[@react.component]
let make = (~data) =>
  <section className="section">
    <div className="box">
      <div className="columns">
        <div className="column"> {"Years" |> ReasonReact.string} </div>
        <div className="column"> {"Amount" |> ReasonReact.string} </div>
      </div>
      {Belt.List.mapWithIndex(data, (index, amount) =>
         <div className="columns">
           <div className="column">
             {index + 1 |> string_of_int |> ReasonReact.string}
           </div>
           <div className="column"> <FormattedCurrency value=amount /> </div>
         </div>
       )
       |> Array.of_list
       |> ReasonReact.array}
    </div>
  </section>;