package HOADIS.Academics;

import java.io.IOException;
import javax.servlet.*;
import javax.servlet.http.*;
import HOADIS.*;
import HOADIS.beans.*;
import java.sql.*;

public class EditSubject extends HttpServlet
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
  if (userData == null || userData.getUser() == null || !userData.getType().equals("F"))
  {
   Utils.unauthorised(request, response);
   return;
  }
  else
  {
   Subject subject = null;
   String code = request.getParameter("subject");
   if (!code.equals("new"))
   {
    try
    {
     Connection con = Utils.getDBConnection();
     PreparedStatement cs = con.prepareStatement("select * from subject where code = ?");
     cs.setString(1, code);
     ResultSet rs = cs.executeQuery();
     if (rs.next())
     {
      subject = new Subject(rs.getString("name"), code, rs.getString("course"), rs.getString("sem"), rs.getString("teacher"), rs.getInt("lastrno"));
      if (subject.getCourse().equals("IDD"))
      {
       request.setAttribute("IDD", "selected");
      }
      else
      {
       request.setAttribute("BTech", "selected");
      }
      request.setAttribute("subject", subject);
     }
     else
     {
      Utils.Error(request, response, Utils.DBERRORPAGE);
      return;
     }
    }
    catch (Exception ex)
    {
     //ex.printStackTrace(response.getWriter());
     Utils.Error(request, response, Utils.DBERRORPAGE);
     return;
    }
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
 String view = "/WEB-INF/Academics/EditSubject.jsp";
}
