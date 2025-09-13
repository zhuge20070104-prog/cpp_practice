import React from "react";
import  ReactDOM  from "react-dom/client";

var style = {
  backgroundColor: 'orange',
  color: 'white',
  fontFamily: 'Arial'
}

const root = ReactDOM.createRoot(
  document.getElementById("root")
)

root.render(
  <div style={style}>
    <h1 id="heading-element">Hello, World</h1>
    <p>We're glad you're here</p>
  </div>
)