package HOADIS.Result;

import java.io.IOException;
import javax.servlet.*;
import javax.servlet.http.*;
import HOADIS.*;
import HOADIS.beans.*;
import java.sql.*;

public class Result extends HttpServlet
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
   String rno = request.getParameter("rno");
   try
   {
    Connection con = Utils.getDBConnection();
    PreparedStatement cs = con.prepareStatement("select * from result where rno=?");
    cs.setString(1, rno);
    ResultSet rs = cs.executeQuery();
    if (rs.next())
    {
     HOADIS.beans.Result result = new HOADIS.beans.Result();
     result.setRno(rno);
     result.setT1(rs.getString("T1").charAt(0));
     result.setT2(rs.getString("T2").charAt(0));
     result.setT3(rs.getString("T3").charAt(0));
     result.setT4(rs.getString("T4").charAt(0));
     result.setT5(rs.getString("T5").charAt(0));
     result.setT6(rs.getString("T6").charAt(0));
     result.setP1(rs.getString("P1").charAt(0));
     result.setP2(rs.getString("P2").charAt(0));
     result.setP3(rs.getString("P3").charAt(0));
     result.setP4(rs.getString("P4").charAt(0));
     result.setTS1(rs.getString("TS1"));
     result.setTS2(rs.getString("TS2"));
     result.setTS3(rs.getString("TS3"));
     result.setTS4(rs.getString("TS4"));
     result.setTS5(rs.getString("TS5"));
     result.setTS6(rs.getString("TS6"));
     result.setPS1(rs.getString("PS1"));
     result.setPS2(rs.getString("PS1"));
     result.setPS3(rs.getString("PS3"));
     result.setPS4(rs.getString("PS4"));
     result.setCgpa(rs.getDouble("CGPA"));
     result.setYgpa(rs.getDouble("YGPA"));
     result.setSgpa(rs.getDouble("SGPA"));
     PreparedStatement cs2 = con.prepareStatement("select * from student where rno=?");
     cs2.setString(1, rno);
     ResultSet rs2 = cs.executeQuery();
     if (rs2.next())
     {
      //result.setCourse(rs2.getString("course"));
      //result.setSem(rs2.getInt("sem"));
      request.setAttribute("result", result);
     }
     else
     {
      Utils.Error(request, response, Utils.DBERRORPAGE);
      return;
     }
    }
     else
     {
      Utils.Error(request, response, Utils.DBERRORPAGE);
      return;
     }
    }
   catch
    (Exception ex)
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
 public String getServletInfo()
 {
  return "HOADIS MVC Control Servlet";
 }
 HttpSession session;
 RequestDispatcher rd;
 String view = "/WEB-INF/Result/Result.jsp";
}
