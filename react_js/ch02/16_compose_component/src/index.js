
import React, {Component} from "react";
import  ReactDOM, {createRoot}  from "react-dom/client";

const Book = ({title, author, pages}) => {
  return (
    <section>
      <h2>{title}</h2>
      <p>by: {author}</p>
      <p>Pages: {pages} pages</p>
    </section>
  )
}

const Library = () => {
  return (
    <div>
      <Book title="The Sun Also Rises" author="Ernest Hemingway" pages={260}></Book>
      <Book title="White Teeth" author="Zadie Smith" pages={480}></Book>
      <Book title="Cat's Gradle" author="Kurt Vonnegut" pages={304}></Book>
    </div>
  )
}

const root = createRoot(
  document.getElementById("root")
)

root.render(
  <Library ></Library>
)