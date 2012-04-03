package HOADIS.UserAuthentication;

import java.io.IOException;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;
import HOADIS.*;
import HOADIS.beans.*;

/**
 *
 * @author ajay
 */
public class Login extends HttpServlet
{

 /**
  * Handles the HTTP <code>GET</code> method.
  * @param request servlet request
  * @param response servlet response
  * @throws ServletException if a servlet-specific error occurs
  * @throws IOException if an I/O error occurs
  */
 @Override
 protected void doGet(HttpServletRequest request, HttpServletResponse response)
 throws ServletException, IOException
 {
  Utils.unauthorised(request, response);
 }

 /**
  * Handles the HTTP <code>POST</code> method.
  * @param request servlet request
  * @param response servlet response
  * @throws ServletException if a servlet-specific error occurs
  * @throws IOException if an I/O error occurs
  */
 @Override
 protected void doPost(HttpServletRequest request, HttpServletResponse response)
 throws ServletException, IOException
 {

  //Get userData bean
  session = request.getSession();
  User userData = (User) session.getAttribute("userData");
  if (userData == null)
  {
   Utils.unauthorised(request, response);
   return;
  }

  //Get Form Parameters
  String user = request.getParameter("user");
  String pass = request.getParameter("pass");

  //Perform DB query
  if (user == null || pass == null)
  {
   userData.setLoginError("A Required Feild Is Empty.Please Try Again");
   destination="LoginForm";
  }

  else
  {

   try
   {
    Connection con = Utils.getDBConnection();
    boolean flag = false;
    PreparedStatement cs = con.prepareStatement("select pass,type from login where user=?");
    cs.setString(1, user);
    ResultSet rs = cs.executeQuery();
    while (rs.next())
    {
     String pass2 = new String(rs.getString("pass"));
     String type = new String(rs.getString("type"));
     if (pass.equals(pass2))
     {
      flag = true;
      userData.setUser(user);
      userData.setPass(pass);
      userData.setType(type);
      userData.setLoginError("");
     }
    }
    if (flag == false)
    {
     int tries = userData.getTries();
     tries++;
     userData.setTries(tries);
     userData.setLoginError("Invalid Username/Password");
     destination="LoginForm";
    }
   }
   catch (Exception ex)
   {
    Utils.Error(request, response, Utils.DBERRORPAGE);
    return;
   }

  }
  response.sendRedirect(destination);
 }

 /**
  * Returns a short description of the servlet.
  * @return a String containing servlet description
  */
 @Override
 public String getServletInfo()
 {
  return "HOADIS Form Processing Servlet";
 }

 private HttpSession session;
 private String destination="Home";
}
