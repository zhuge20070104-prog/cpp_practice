import React, {Component} from "react";
import  ReactDOM, {createRoot}  from "react-dom/client";

class FavoriteColorForm extends Component {
  state = {value: ''}
  
  newColor = e =>
    this.setState({value: e.target.value})
  
  submit = e => {
    console.log(`New Color: ${this.state.value}`)
    e.preventDefault()
  }

  render() {
    return (
      <form onSubmit={this.submit}>
        <label>Favorite Color: 
          <input type="color" onChange={this.newColor}></input>
        </label>
        <button type="submit">Submit</button>
      </form>
    )
  }
}

const root = createRoot(
  document.getElementById("root")
)

root.render(
  <FavoriteColorForm />
)