import React from "react";
import  ReactDOM  from "react-dom/client";

class Message extends React.Component {
  render() {
    return (
      <div>
        <h1 style={{color: this.props.color}}>
           {this.props.msg}
        </h1>
        <p>I'll check back in {this.props.minutes} minutes</p>
      </div>
    )
  }
}

const root = ReactDOM.createRoot(
  document.getElementById("root")
)

root.render(
  <Message color="blue" msg="How are you?" minutes={5}/>
)