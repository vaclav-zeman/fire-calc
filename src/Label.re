let style = ReactDOMRe.Style.make(~display="block", ~margin="2rem 0", ());

[@react.component]
let make = (~children) => <label style> children </label>;