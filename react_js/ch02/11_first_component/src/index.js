import React from "react";
import  ReactDOM  from "react-dom/client";

class Message extends React.Component {
  render() {
    return (
      <div>
        <h1>Hello EveryOne</h1>
      </div>
    )
  }
}

const root = ReactDOM.createRoot(
  document.getElementById("root")
)

root.render(
  <Message/>
)