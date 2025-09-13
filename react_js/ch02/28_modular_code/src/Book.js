import React from "react"
import PropTypes from "prop-types"

// 函数对象也可以给默认属性，例如pages没有就给0
const Book = ({title, author, pages=0, freeBookmark}) => {
    return (
      <section>
        <h2>{title}</h2>
        <p>by: {author}</p>
        <p>Pages: {pages} pages</p>
        <p>Free Bookmark today: {freeBookmark? 'yes!': 'no!'}</p>
      </section>
    )
  }

Book.propTypes = {
    title: PropTypes.string,
    author: PropTypes.string,
    pages: PropTypes.number,
    freeBookmark: PropTypes.bool
}
export default Book  