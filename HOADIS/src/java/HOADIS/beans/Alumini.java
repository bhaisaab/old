
package HOADIS.beans;

public class Alumini
{
 private String user="";
 private String rno="";
 private String branch="";
 private int year;
 private String course="";
 private String aoi="";
 private String homepage="";
 private String profession="";
 private String desig="";
 private String org="";

 public Alumini()
 {
 }

 public Alumini(String user, String rno, String branch, int year, String course, String aoi, String homepage, String profession, String desig, String org)
 {
  this.user = user;
  this.rno = rno;
  this.branch = branch;
  this.year = year;
  this.course = course;
  this.aoi = aoi;
  this.homepage = homepage;
  this.profession = profession;
  this.desig = desig;
  this.org = org;
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

 public String getDesig()
 {
  return desig;
 }

 public void setDesig(String desig)
 {
  this.desig = desig;
 }

 public String getHomepage()
 {
  return homepage;
 }

 public void setHomepage(String homepage)
 {
  this.homepage = homepage;
 }

 public String getOrg()
 {
  return org;
 }

 public void setOrg(String org)
 {
  this.org = org;
 }

 public String getProfession()
 {
  return profession;
 }

 public void setProfession(String profession)
 {
  this.profession = profession;
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
