package HOADIS.beans;

import java.sql.Date;

public class Event
{

 String title, category, author, detail;
 Date date;

 public Event(String title, String category, String author, String detail, Date date)
 {
  this.title = title;
  this.category = category;
  this.author = author;
  this.detail = detail;
  this.date = date;
 }

 public String getAuthor()
 {
  return author;
 }

 public void setAuthor(String author)
 {
  this.author = author;
 }

 public String getCategory()
 {
  return category;
 }

 public void setCategory(String category)
 {
  this.category = category;
 }

 public Date getDate()
 {
  return date;
 }

 public void setDate(Date date)
 {
  this.date = date;
 }

 public String getDetail()
 {
  return detail;
 }

 public void setDetail(String detail)
 {
  this.detail = detail;
 }

 public String getTitle()
 {
  return title;
 }

 public void setTitle(String title)
 {
  this.title = title;
 }

 public Event()
 {
 }
 
}
