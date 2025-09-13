
import React, {Component} from "react";
import  ReactDOM, {createRoot}  from "react-dom/client";


let skiData = {
  total: 50,
  powder: 20,
  backcountry: 10,
  goal: 100
}

const getPercent = decimal =>{
  return decimal * 100 + '%'
}

const calGoalProgress = (total, goal) => {
  return getPercent(total/ goal)
}

const SkiDayCounter = ({total, powder, backcountry, goal}) => {
  return ( <section>
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
        <p>Goal Process: {calGoalProgress(total, goal)}</p>
      </div>
  </section>)
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