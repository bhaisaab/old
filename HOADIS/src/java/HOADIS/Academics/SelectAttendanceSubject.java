package HOADIS.Academics;

import java.io.IOException;
import javax.servlet.*;
import javax.servlet.http.*;
import HOADIS.*;
import HOADIS.beans.*;
import java.sql.*;
import java.util.Vector;

public class SelectAttendanceSubject extends HttpServlet
{
 @Override
 protected void doGet(HttpServletRequest request, HttpServletResponse response)
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
   Vector<String> subjectList = new Vector<String>();
   try
   {
    Connection con = Utils.getDBConnection();
    PreparedStatement cs = con.prepareStatement("select code from subject");
    ResultSet rs = cs.executeQuery();
    while (rs.next())
    {
     //String code = rs.getString("code");
     subjectList.add(new String(rs.getString("code")));
    }
    request.setAttribute("subjectList", subjectList);
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
 String view = "/WEB-INF/Academics/SelectAttendanceSubject.jsp";
}
