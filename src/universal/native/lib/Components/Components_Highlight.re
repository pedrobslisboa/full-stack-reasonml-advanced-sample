[@react.component]
let make = () => {
  <pre>
    <code className="css language-reason">
      <span className="token module"> {"Dream" |> React.string} </span>
      {".get(" |> React.string}
      <br />
      <span className="token string"> {"  \"home\"," |> React.string} </span>
      <br />
      <span className="token disable"> {"   _ " |> React.string} </span>
      {"=> {" |> React.string}
      <br />
      <span className="token keyword"> {"    let" |> React.string} </span>
      {" html =" |> React.string}
      <span className="token module"> {" ReactDOM" |> React.string} </span>
      {".renderToString(" |> React.string}
      <span className="token tag"> {"<" |> React.string} </span>
      <span className="token module"> {"App" |> React.string} </span>
      <span className="token tag"> {"/>" |> React.string} </span>
      {");" |> React.string}
      <br />
      <br />
      <span className="token module"> {"    Str" |> React.string} </span>
      {".global_replace(" |> React.string}
      <br />
      <span className="token module"> {"      Str" |> React.string} </span>
      {".regexp(" |> React.string}
      <span className="token string">
        {"\"<div id=\\\"root\\\"></div>\"" |> React.string}
      </span>
      {")," |> React.string}
      <br />
      <span className="token string">
        {"      \"<div id=\\\"root\\\">\"" |> React.string}
      </span>
      <span className="token operator"> {" ++ " |> React.string} </span>
      {"html" |> React.string}
      <span className="token operator"> {" ++ " |> React.string} </span>
      <span className="token string"> {"\"</div>\"" |> React.string} </span>
      {"," |> React.string}
      <br />
      <span> {"      indexFileString," |> React.string} </span>
      <br />
      <span> {"    )" |> React.string} </span>
      <br />
      <span className="token keyword"> {"    |> " |> React.string} </span>
      {"appendUniversalStyles)" |> React.string}
      <br />
      <span className="token keyword"> {"    |> " |> React.string} </span>
      {"Dream.html;" |> React.string}
      <br />
      {"  }" |> React.string}
      <br />
      {")" |> React.string}
    </code>
  </pre>;
};
