import React from "react";
import  ReactDOM  from "react-dom/client";

var style = {
  backgroundColor: 'orange',
  color: 'white',
  fontFamily: 'Arial'
}

const title = React.createElement('h1',
  {id: 'title', className: 'header', style: style},
  'Hello World'
)

const root = ReactDOM.createRoot(
  document.getElementById("root")
)

root.render(
  title
)