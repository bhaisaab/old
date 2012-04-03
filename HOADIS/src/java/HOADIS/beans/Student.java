package HOADIS.beans;

public class Student
{
 private String user;
 private String rno;
 private String branch;
 private int year;
 private String course;
 private String aoi;
 private String homepage;

 public Student()
 {
 }

 
 public Student(String user, String rno, String branch, int year, String course, String aoi, String homepage)
 {
  this.user = user;
  this.rno = rno;
  this.branch = branch;
  this.year = year;
  this.course = course;
  this.aoi = aoi;
  this.homepage = homepage;
 }

 
 public String getAoi()
 {
  return aoi;
 }

 public void setAoi(String aoi)
 {
  this.aoi = aoi;
 }

 public String getBranch()
 {
  return branch;
 }

 public void setBranch(String branch)
 {
  this.branch = branch;
 }

 public String getCourse()
 {
  return course;
 }

 public void setCourse(String course)
 {
  this.course = course;
 }

 public String getHomepage()
 {
  return homepage;
 }

 public void setHomepage(String homepage)
 {
  this.homepage = homepage;
 }

 public String getRno()
 {
  return rno;
 }

 public void setRno(String rno)
 {
  this.rno = rno;
 }

 public String getUser()
 {
  return user;
 }

 public void setUser(String user)
 {
  this.user = user;
 }

 public int getYear()
 {
  return year;
 }

 public void setYear(int year)
 {
  this.year = year;
 }
 
}
