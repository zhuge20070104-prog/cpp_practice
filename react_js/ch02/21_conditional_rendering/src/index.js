import React, {Component} from "react";
import  ReactDOM, {createRoot}  from "react-dom/client";

// 一般从数据库或者接口中拿数据
let bookList = [
  {title: "Hunger", author: "Roxane Gay", pages: 320},
  {title: "The Sun Also Rises", author: "Ernest Hemingway", pages: 260},
  {title: "White Teeth", author: "Zadie Smith", pages: 480},
  {title: "Cat's Gradle", author: "Kurt Vonnegut", pages: 304},
]

const Book = ({title, author, pages, freeBookmark}) => {
  return (
    <section>
      <h2>{title}</h2>
      <p>by: {author}</p>
      <p>Pages: {pages} pages</p>
      <p>Free Bookmark today: {freeBookmark? 'yes!': 'no!'}</p>
    </section>
  )
}

// 函数返回除了 {return XX} 外，也可以直接写tag
const Hiring = () => 
  <div>
    <p>The Library is hiring. Go to www.library.com/jobs for more.</p>
  </div>

const NotHiring = () => 
  <div>
    <p>The Library is not hiring. Check back later for more.</p>
  </div>


// 只有class 能有state
class Library extends Component {
  state = {
    open: true,
    freeBookmark: true,
    hiring: false
  }
  // 这样写能够直接绑定到对象，不需要手动绑定
  toggleOpenClosed = () => {
    this.setState(prevState => ({
      open: !prevState.open
    }))
  }

  render() {
    const {books} = this.props
    return (
      <div>
        {this.state.hiring ? <Hiring/>: <NotHiring/>}
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

const root = createRoot(
  document.getElementById("root")
)

root.render(
  <Library books={bookList}></Library>
)