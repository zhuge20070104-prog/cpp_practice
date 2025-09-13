import React from "react";
import  ReactDOM  from "react-dom/client";


const title = React.createElement('h1',
  {id: 'title', className: 'header'},
  'Hello World'
)

const root = ReactDOM.createRoot(
  document.getElementById("root")
)

root.render(
  title
)