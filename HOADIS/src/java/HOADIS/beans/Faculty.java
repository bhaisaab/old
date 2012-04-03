package HOADIS.beans;

public class Faculty
{
 String user,desig,qual,courses,aoi,ph,email,homepage;

 public Faculty(String user, String desig, String qual, String courses, String aoi, String ph, String email, String homepage)
 {
  this.user = user;
  this.desig = desig;
  this.qual = qual;
  this.courses = courses;
  this.aoi = aoi;
  this.ph = ph;
  this.email = email;
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

 public String getCourses()
 {
  return courses;
 }

 public void setCourses(String courses)
 {
  this.courses = courses;
 }

 public String getDesig()
 {
  return desig;
 }

 public void setDesig(String desig)
 {
  this.desig = desig;
 }

 public String getEmail()
 {
  return email;
 }

 public void setEmail(String email)
 {
  this.email = email;
 }

 public String getHomepage()
 {
  return homepage;
 }

 public void setHomepage(String homepage)
 {
  this.homepage = homepage;
 }

 public String getPh()
 {
  return ph;
 }

 public void setPh(String ph)
 {
  this.ph = ph;
 }

 public String getQual()
 {
  return qual;
 }

 public void setQual(String qual)
 {
  this.qual = qual;
 }

 public String getUser()
 {
  return user;
 }

 public void setUser(String user)
 {
  this.user = user;
 }

 public Faculty()
 {
 }
 
}
