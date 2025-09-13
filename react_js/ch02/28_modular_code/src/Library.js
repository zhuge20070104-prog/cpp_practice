import React, {Component} from "react"
import PropTypes from "prop-types"
import Book from "./Book"
import Hiring from "./Hiring"
import NotHiring from "./NotHiring"

// 只有类对象才能有生命周期
// 1. constructor是构造函数，组件构造时用来初始化
// 2. componentDidMount在组件被挂载上DOM时调用
// 3. 每次更新界面时会调用render函数
// 4. 更新完毕后会调用componentDidUpdate函数
// 5. componentWillUnmount可以用来清理资源，例如dom节点等。
// 只有class 能有state
class Library extends Component {
    // 给一个默认属性，没有传books的时候，就用默认属性
    static defaultProps = {
      books: [
        {title: "Hunger", author: "Roxane Gay"}
      ]
    }
    state = {
      open: true,
      freeBookmark: true,
      hiring: false,
      data: [],
      loading: false
    }
    // 这样写能够直接绑定到对象，不需要手动绑定
    toggleOpenClosed = () => {
      this.setState(prevState => ({
        open: !prevState.open
      }))
    }
  
    componentDidMount() {
      this.setState({loading: true})
      fetch('https://hplussport.com/api/products/order/price/sort/asc/qty/3')
      .then(data => data.json())
      .then(data=> this.setState({data, loading: false}))
    }
  
    componentDidUpdate() {
      console.log('The component just updated!')
    }
  
    render() {
      const {books} = this.props
      return (
        <div>
          {this.state.hiring ? <Hiring/>: <NotHiring/>}
  
          <h3>Library Product of the Week!</h3>  
          {
            this.state.loading? 
            "Loading..."
            : 
            this.state.data.map(product => {
                return (
                  <div key={product.id}>
                    <h4>{product.name}</h4>
                    <img src={product.image} alt={product.name} height={100}></img>
                  </div>
                )
              })
            }
  
          <h1>The Library is {this.state.open? 'open': 'closed'}</h1>
          <button onClick={this.toggleOpenClosed}>Change</button>
          {books.map(
            (book, i) =>
            <Book key={i}
              title={book.title} 
              author={book.author} 
              pages={book.pages}
              freeBookmark={this.state.freeBookmark}
              >  
            </Book>
          )}
        </div>
      )
    }
  }
  
  Library.propTypes = {
    books: PropTypes.array
  } 

  export default Library