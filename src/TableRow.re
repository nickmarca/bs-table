module Styles = {
  open Css;

  let container = (~height=50) =>
    style([
      minHeight(px(height)),
      maxHeight(px(height)),
      padding(px(10)),
      borderBottom(px(1), solid, hex("efefef")),
    ]);
};

[@react.component]
let make = (~children, ~height) => {
  <div className={Styles.container(~height)}>
    <span> {ReasonReact.string("Table Row: ")} </span>
    children
  </div>;
};