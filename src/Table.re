let rowHeight = 50;
let listLen = 100000;
let tableHeight = 800;
let tableWidth = 500;

module Styles = {
  open Css;

  let container =
    style([
      height(px(tableHeight)),
      width(px(tableWidth)),
      display(flexBox),
      flexDirection(column),
      overflowY(auto),
      fontFamily("'Mali', cursive"),
      position(relative),
    ]);

  let scroll = h => style([minHeight(px(h))]);
  let scrollWrapper =
    style([
      overflowY(auto),
      height(px(tableHeight)),
      width(px(tableWidth)),
      position(relative),
    ]);

  let tableContent =
    style([
      minWidth(pct(100.)),
      position(absolute),
      top(px(0)),
      right(px(0)),
      overflow(hidden),
    ]);
};

let rec makeList: int => list((int, int)) =
  num => {
    let rec helper = (p, acc) => {
      let (i, n) = p;

      if (n < 1) {
        acc;
      } else {
        helper((i - 1, n - 1), List.append([(i, n)], acc));
      };
    };
    helper((num - 1, num), []);
  };

let list = makeList(listLen);

let listLen = List.length(list);

let slice = (startFrom, length, list) => {
  let (l, _) =
    List.partition(
      p => {
        let (i, _) = p;
        if (i >= startFrom && i < startFrom + length) {
          true;
        } else {
          false;
        };
      },
      list,
    );
  l;
};

let createRows = lst => {
  List.rev_map(
    p => {
      let (_, v) = p;
      <TableRow key={string_of_int(v)} height=rowHeight>
        {ReasonReact.string(string_of_int(v))}
      </TableRow>;
    },
    lst,
  );
};

[@react.component]
let make = () => {
  let numberOfRows = tableHeight / rowHeight;

  let (start, setStart) = React.useState(() => 0);

  let onScroll = event => {
    let scrollTop = event->ReactEvent.UI.target##scrollTop;
    let nextStart = scrollTop / rowHeight;

    if (start != nextStart) {
      setStart(_ => nextStart);
    };
  };

  let nList = slice(listLen - (numberOfRows + start), numberOfRows, list);

  <div className=Styles.container>
    <div className=Styles.tableContent>
      {ReasonReact.array(Array.of_list(createRows(nList)))}
    </div>
    <div className=Styles.scrollWrapper onScroll>
      <div className={Styles.scroll(listLen * rowHeight)} />
    </div>
  </div>;
};