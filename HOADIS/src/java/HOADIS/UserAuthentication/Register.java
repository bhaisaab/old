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
public class Register extends HttpServlet
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
  }

  //Get Form Parameters
  String user = request.getParameter("user");
  String pass = request.getParameter("pass");
  String type = request.getParameter("type");

  //Perform DB query
  if (user == null || pass == null)
  {
   userData.setLoginError("A Required Feild Is Empty.Please Try Again");
   destination = "RegisterForm";
  }
  else
  {
   try
   {
    Connection con = Utils.getDBConnection();
    PreparedStatement chk = con.prepareStatement("select user from login where user=? ");
    chk.setString(1, user);
    ResultSet rs = chk.executeQuery();
    if (rs.next())
    {
     userData.setRegisterError("Username Already Registered.Choose Another Username");
     destination = "RegisterForm";
    }
    else
    {
     PreparedStatement cs = con.prepareStatement("insert into login(user,pass,type) values (?,?,?) ");
     cs.setString(1, user);
     cs.setString(2, pass);
     cs.setString(3, type);
     cs.execute();
     userData.setLoginError("Please Login To Continue...");
     destination = "index.jsp";
    }
   }
   catch (Exception ex)
   {
    Utils.Error(request, response, Utils.DBERRORPAGE);
   }
  }
  response.sendRedirect(destination);
  return;
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
 private String destination = "index.jsp";
}
