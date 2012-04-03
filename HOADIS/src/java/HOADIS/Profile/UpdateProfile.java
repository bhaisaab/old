package HOADIS.Profile;

import java.io.IOException;
import javax.servlet.*;
import javax.servlet.http.*;
import HOADIS.*;
import HOADIS.beans.*;

public class UpdateProfile extends HttpServlet
{

 @Override
 protected void doGet(HttpServletRequest request, HttpServletResponse response)
 throws ServletException, IOException
 {
  Utils.unauthorised(request, response);
 }

 @Override
 protected void doPost(HttpServletRequest request, HttpServletResponse response)
 throws ServletException, IOException
 {
  session = request.getSession();
  User userData = (User) session.getAttribute("userData");
  if (userData == null || userData.getUser() == null)
  {
   Utils.unauthorised(request, response);
   return;
  }
  else
  {
   String type = userData.getType();

   if (type.equals("S"))
   {
    Student student = (Student) session.getAttribute("student");
    if (student == null)
    {
     Utils.unauthorised(request, response);
     return;
    }
    view = "/WEB-INF/Profile/UpdateSProfile.jsp";
   }
   else if (type.equals("A"))
   {
    Alumini alumini = (Alumini) session.getAttribute("alumini");
    if (alumini == null)
    {
     Utils.unauthorised(request, response);
     return;
    }
    view = "/WEB-INF/Profile/UpdateAProfile.jsp";
   }
   else if (type.equals("F"))
   {
    Faculty faculty = (Faculty) session.getAttribute("faculty");
    if (faculty == null)
    {
     Utils.unauthorised(request, response);
     return;
    }
    view = "/WEB-INF/Profile/UpdateFProfile.jsp";
   }

   rd = request.getRequestDispatcher(view);
   rd.forward(request, response);
  }
 }

 @Override
 public String getServletInfo()
 {
  return "HOADIS MVC Control Servlet";
 }
 HttpSession session;
 RequestDispatcher rd;
 String view = "/WEB-INF/Profile/Home.jsp";
}
