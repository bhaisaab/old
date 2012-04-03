package HOADIS.Academics;

import java.io.IOException;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;
import HOADIS.*;
import HOADIS.beans.*;

public class AddAttendance extends HttpServlet
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
  if (userData == null || !userData.getType().equals("F"))
  {
   Utils.unauthorised(request, response);
   return;
  }
  try
  {
   Subject subject = (Subject) session.getAttribute("subject");
   String code = subject.getCode().replace(" ", "").replace("-", "");
   String course = subject.getCourse().replace(" ", "").replace(".", "");
   Connection con = Utils.getDBConnection();
   String table = "attend" + course + code;
   PreparedStatement cs = con.prepareStatement("delete from " + table + " where dat=curdate()");
   cs.execute();
   String insert = "insert into " + table + "(";
   for (int i = 1; i <= subject.getLastrno(); i++)
   {
    insert += " rno" + i + " , ";
   }
   insert += "dat) values (";
   for (int i = 1; i <= subject.getLastrno(); i++)
   {
    insert += request.getParameter("rno" + i)+ " , ";
   }
   insert += " curdate() )";
   response.getWriter().println(insert);
   cs = con.prepareStatement(insert);
   cs.execute();
  }
  catch (Exception ex)
  {
   //ex.printStackTrace(response.getWriter());
   Utils.Error(request, response, Utils.DBERRORPAGE);
   return;
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
 private String destination = "Home";
}
