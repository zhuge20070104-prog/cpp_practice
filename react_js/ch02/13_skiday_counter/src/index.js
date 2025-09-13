
import React, {Component} from "react";
import  ReactDOM, {createRoot}  from "react-dom/client";


let skiData = {
  total: 50,
  powder: 20,
  backcountry: 10,
  goal: 100
}

class SkiDayCounter extends Component {
  render() {
    const {total, powder, backcountry, goal} = this.props
    return (
      <section>
          <div>
            <p>Total Days: {total}</p>
          </div>
          <div>
            <p>Powder Days: {powder}</p>
          </div>
          <div>
            <p>Backcountry Days: {backcountry}</p>
          </div>
          <div>
            <p>Goal: {goal}</p>
          </div>
      </section>
    )
  }
}

const root = createRoot(
  document.getElementById("root")
)

root.render(
  <SkiDayCounter 
    total={skiData.total}
    powder={skiData.powder}
    backcountry={skiData.backcountry}
    goal={skiData.goal} />
)