package HOADIS.beans;

public class User
{

 private String user,  pass,  type;
 private String loginError = "",  registerError = "";
 private int tries = 0;

 public String getLoginError()
 {
  return loginError;
 }

 public void setLoginError(String loginError)
 {
  this.loginError = loginError;
 }

 public String getRegisterError()
 {
  return registerError;
 }

 public void setRegisterError(String registerError)
 {
  this.registerError = registerError;
 }

 public int getTries()
 {
  return tries;
 }

 public void setTries(int tries)
 {
  this.tries = tries;
 }

 public String getPass()
 {
  return pass;
 }

 public void setPass(String pass)
 {
  this.pass = pass;
 }

 public String getType()
 {
  return type;
 }

 public void setType(String type)
 {
  this.type = type;
 }

 public String getUser()
 {
  return user;
 }

 public void setUser(String user)
 {
  this.user = user;
 }
}
