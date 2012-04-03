package HOADIS.TimeTable;

import java.io.IOException;
import javax.servlet.*;
import javax.servlet.http.*;
import HOADIS.*;
import HOADIS.beans.*;
import java.sql.*;

/**
 *
 * @author ajay
 */
public class TimeTable extends HttpServlet
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
  session = request.getSession();
  User userData = (User) session.getAttribute("userData");
  if (userData == null || userData.getUser() == null)
  {
   Utils.unauthorised(request, response);
   return;
  }
  try
  {
   year=request.getParameter("year");
   session.setAttribute("TimeTableYear", year);
   Connection con = Utils.getDBConnection();
   PreparedStatement cs = con.prepareStatement("select * from timetable" + year);
   ResultSet rs = cs.executeQuery();
   for (int i = 1; i < 8; i++)
   {
    if (rs.next())
    {
     request.setAttribute("time" + i, rs.getString("time"));
     request.setAttribute("mon" + i, rs.getString("mon"));
     request.setAttribute("tue" + i, rs.getString("tue"));
     request.setAttribute("wed" + i, rs.getString("wed"));
     request.setAttribute("thurs" + i, rs.getString("thur"));
     request.setAttribute("fri" + i, rs.getString("fri"));
     request.setAttribute("sat" + i, rs.getString("sat"));
    }
   }
  }
  catch (Exception ex)
  {
   //ex.printStackTrace(response.getWriter());
   Utils.Error(request, response, Utils.DBERRORPAGE);
   return;
  }
  if(userData.getType().equals("F"))
    view="/WEB-INF/TimeTable/EditTimeTable.jsp";
  else
   view="/WEB-INF/TimeTable/ViewTimeTable.jsp";
  rd = request.getRequestDispatcher(view);
  rd.forward(request, response);
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
 HttpSession session;
 String year;
 RequestDispatcher rd;
 String view = "/WEB-INF/TimeTable/ViewTimeTable.jsp";
}
