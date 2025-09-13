import React, {Component} from "react";
import  ReactDOM, {createRoot}  from "react-dom/client";
import Library from "./Library"


let bookList = [
  {title: "Hunger", author: "Roxane Gay", pages: 320},
  {title: "The Sun Also Rises", author: "Ernest Hemingway", pages: 260},
  {title: "White Teeth", author: "Zadie Smith", pages: 480},
  {title: "Cat's Gradle", author: "Kurt Vonnegut", pages: 304},
]


const root = createRoot(
  document.getElementById("root")
)

root.render(
  <Library books={bookList}/>
)