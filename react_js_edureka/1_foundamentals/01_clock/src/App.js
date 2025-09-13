import logo from './logo.svg';
import './App.css';
import React from 'react';
import ReactDOM from 'react-dom/client';


class Clock extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      date: new Date()
    };
  }

  componentDidMount() {
    this.timerID = setInterval(()=> {
      this.tick();
    }, 1000); 
  }

  componentWillUnmount() {
    clearInterval(this.timerID);
  }

  tick() {
    this.setState({
      date: new Date()
    });
  }

  render() {
    return (
      <div>
        <h1>Hello, Fredric!</h1>
        <h2>
          It is: {this.state.date.toLocaleTimeString()}
        </h2>
      </div>
    );
  }
}

function App() {
  return (
    <div className="App">
      <Clock />
    </div>
  );
}

export default App;
