package HOADIS.UserAuthentication;

import java.io.IOException;
import javax.servlet.*;
import javax.servlet.http.*;
import HOADIS.*;
import HOADIS.beans.User;

/**
 *
 * @author ajay
 */
public class RegisterForm extends HttpServlet
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

  //Get/Create userData bean
  session = request.getSession();
  User userData = (User) session.getAttribute("userData");
  if (userData == null)
  {
   userData = new User();
   session.setAttribute("userData", userData);
  }
  else
  {
   //Display error if too many login attempts
   int tries = userData.getTries();
   if (tries > 10)
   {
    view = "/WEB-INF/UserAuthentication/TooManyTries.jsp";
   }
   else
   {
    //Go to user's homepage if already logged in
    String user = userData.getUser();
    if (user != null)
    {
     response.sendRedirect("Home");
     return;
    }
   }
  }


  //Forward request
  rd = request.getRequestDispatcher(view);
  rd.forward(request, response);

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
  Utils.unauthorised(request, response);
 }

 /**
  * Returns a short description of the servlet.
  * @return a String containing servlet description
  */
 @Override
 public String getServletInfo()
 {
  return "HOADIS MVC Control Servlet";
 }
 private HttpSession session;
 private RequestDispatcher rd;
 private String view = "/WEB-INF/UserAuthentication/RegisterForm.jsp";
}
