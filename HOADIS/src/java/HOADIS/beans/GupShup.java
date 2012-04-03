package HOADIS.beans;

public class GupShup 
{
    String msg = "GupShup is unable to process data.";
    String author = "GupShup's Created by Rohit Yadav";
    
 public GupShup(String author, String msg)
 {
     this.author = author;
     this.msg = msg;
 }

 public String getAuthor()
 {
  return author;
 }

 public void setAuthor(String author)
 {
  this.author = author;
 }
 
 public String getMessage()
 {
  return msg;
 }

 public void setMessage(String msg)
 {
  this.msg = msg;
 }
 
 public GupShup()
 {
 }
 
}

