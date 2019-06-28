let handleClick = _event => Js.log("clicked!");

[@react.component]
let make = (~message) =>
  <div onClick=handleClick> {ReasonReact.string(message)} </div>;