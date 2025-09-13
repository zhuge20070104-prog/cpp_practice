import React from "react";
import  ReactDOM  from "react-dom/client";

var style = {
  backgroundColor: 'orange',
  color: 'white',
  fontFamily: 'Arial'
}

const title = React.createElement('ul',
  {id: 'title', className: 'header', style: style},
  React.createElement(
      'li',
      {},
      'item on our list'
  )
)

const root = ReactDOM.createRoot(
  document.getElementById("root")
)

root.render(
  title
)