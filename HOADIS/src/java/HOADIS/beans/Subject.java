package HOADIS.beans;

public class Subject
{
 String name,code,course,sem,teacher;
 int lastrno;

 public Subject()
 {
 }

 public Subject(String name, String code, String course, String sem, String teacher, int lastrno)
 {
  this.name = name;
  this.code = code;
  this.course = course;
  this.sem = sem;
  this.teacher = teacher;
  this.lastrno = lastrno;
 }

 public String getCode()
 {
  return code;
 }

 public void setCode(String code)
 {
  this.code = code;
 }

 public String getCourse()
 {
  return course;
 }

 public void setCourse(String course)
 {
  this.course = course;
 }

 public int getLastrno()
 {
  return lastrno;
 }

 public void setLastrno(int lastrno)
 {
  this.lastrno = lastrno;
 }

 public String getName()
 {
  return name;
 }

 public void setName(String name)
 {
  this.name = name;
 }

 public String getSem()
 {
  return sem;
 }

 public void setSem(String sem)
 {
  this.sem = sem;
 }

 public String getTeacher()
 {
  return teacher;
 }

 public void setTeacher(String teacher)
 {
  this.teacher = teacher;
 }
 
}
