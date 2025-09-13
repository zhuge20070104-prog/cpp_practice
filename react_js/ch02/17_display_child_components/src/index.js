import React, {Component} from "react";
import  ReactDOM, {createRoot}  from "react-dom/client";

// 一般从数据库或者接口中拿数据
let bookList = [
  {title: "Hunger", author: "Roxane Gay", pages: 320},
  {title: "The Sun Also Rises", author: "Ernest Hemingway", pages: 260},
  {title: "White Teeth", author: "Zadie Smith", pages: 480},
  {title: "Cat's Gradle", author: "Kurt Vonnegut", pages: 304},
]

const Book = ({title, author, pages}) => {
  return (
    <section>
      <h2>{title}</h2>
      <p>by: {author}</p>
      <p>Pages: {pages} pages</p>
    </section>
  )
}

const Library = ({books}) => {
  return (
    <div>

      {books.map(
        (book, i) =>
        <Book key={i}
          title={book.title} 
          author={book.author} 
          pages={book.pages}>  
        </Book>
      )}
    </div>
  )
}

const root = createRoot(
  document.getElementById("root")
)

root.render(
  <Library books={bookList}></Library>
)