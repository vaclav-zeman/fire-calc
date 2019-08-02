[@react.component]
let make = (~annualReturn: string, ~data: Finance.resultList) =>
  <section className="section">
    <div className="box">
      <div className="columns">
        <div className="column"> {"End of year" |> ReasonReact.string} </div>
        <div className="column"> {"Net worth" |> ReasonReact.string} </div>
        <div className="column">
          {"Change in net worth" |> ReasonReact.string}
        </div>
        <div className="column">
          {"ROI (" ++ annualReturn ++ "%)" |> ReasonReact.string}
        </div>
      </div>
      {List.map(
         ({year, netWorth, changeInNetWorth, roi}: Finance.resultRecord) =>
           <div className="columns">
             <div className="column">
               {year |> string_of_int |> ReasonReact.string}
             </div>
             <div className="column">
               <FormattedCurrency value=netWorth />
             </div>
             <div className="column">
               <FormattedCurrency value=changeInNetWorth />
             </div>
             <div className="column"> <FormattedCurrency value=roi /> </div>
           </div>,
         data,
       )
       |> Array.of_list
       |> ReasonReact.array}
    </div>
  </section>;