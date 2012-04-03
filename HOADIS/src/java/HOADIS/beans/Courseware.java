package HOADIS.beans;

public class Courseware
{
 String name, id, uploader, filename;

 public Courseware(String uploader, String filename)
 {
  this.name = name;
  this.id   = id;
  this.uploader   = uploader;
  this.filename = filename;
 }

 public String getName()
 {
  return name;
 }

 public void setName(String name)
 {
  this.name = name;
 }


 public String getId()
 {
  return id;
 }

 public void setId(String id)
 {
  this.id = id;
 }

 public String getUploader()
 {
  return uploader;
 }

 public void setUploader(String uploader)
 {
  this.uploader = uploader;
 }
 
  public String getFilename()
 {
  return filename;
 }

 public void setFilename(String filename)
 {
  this.filename = filename;
 }
 
}
