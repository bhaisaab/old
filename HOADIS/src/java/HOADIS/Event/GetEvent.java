package HOADIS.Event;

import java.io.IOException;
import java.util.*;
import javax.servlet.*;
import javax.servlet.http.*;
import HOADIS.*;
import HOADIS.beans.*;
import java.sql.*;

public class GetEvent extends HttpServlet
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
   return;
  }
  else
  {
   try
   {
    Connection con = Utils.getDBConnection();
    String[] cat =
    {
     "Workshop", "Seminar", "Competition", "Cultural Event", "Other"
    };
   }
   catch (Exception ex)
   {
    ex.printStackTrace(response.getWriter());
    //Utils.Error(request, response, Utils.DBERRORPAGE);
    return;
   }
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
 //RequestDispatcher rd;
 //String view = "/WEB-INF/Event/ShowEvent.jsp";
}
