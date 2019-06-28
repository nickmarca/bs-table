[@bs.val] [@bs.scope "window"] external innerHeight: int = "innerHeight";
[@bs.val] [@bs.scope "window"]
external addEventListener: (string, unit => unit) => unit = "addEventListener";
[@bs.val] [@bs.scope "window"]
external removeEventListener: (string, unit => unit) => unit =
  "removeEventListener";

let useInnerHeight = () => {
  let (h, setH) = React.useState(() => innerHeight);

  React.useEffect0(() => {
    let listener = () => setH(_ => innerHeight);
    addEventListener("resize", listener);
    Some(() => removeEventListener("resize", listener));
  });

  h;
};