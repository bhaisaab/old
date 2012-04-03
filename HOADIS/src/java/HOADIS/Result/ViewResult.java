package HOADIS.Result;

import java.io.IOException;
import javax.servlet.*;
import javax.servlet.http.*;
import HOADIS.*;
import HOADIS.beans.*;

public class ViewResult extends HttpServlet
{

 @Override
 protected void doGet(HttpServletRequest request, HttpServletResponse response)
 throws ServletException, IOException
 {
  session = request.getSession();
  User userData = (User) session.getAttribute("userData");
  if (userData == null || userData.getUser() == null)
  {
   Utils.unauthorised(request, response);
  }
  else
  {
   rd = request.getRequestDispatcher(view);
   rd.forward(request, response);
  }
 }

 @Override
 protected void doPost(HttpServletRequest request, HttpServletResponse response)
 throws ServletException, IOException
 {
  Utils.unauthorised(request, response);
 }

 @Override
 public String getServletInfo()
 {
  return "HOADIS MVC Control Servlet";
 }
 HttpSession session;
 RequestDispatcher rd;
 String view = "/WEB-INF/Result/ViewResult.jsp";
}
