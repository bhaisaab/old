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

public class UpdateTimeTable extends HttpServlet
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
  String year = (String) session.getAttribute("TimeTableYear");
  
  if (userData == null || userData.getUser() == null || year==null)
  {
   Utils.unauthorised(request, response);
   return;
  }
  else
  {
   try
   {
    Connection con = Utils.getDBConnection();
    PreparedStatement drop=con.prepareStatement("delete from timetable"+year);
    drop.execute();
    for(int i=1;i<8;i++)
    {
     PreparedStatement cs=con.prepareStatement("insert into timetable"+year+" (time,mon,tue,wed,thur,fri,sat) values(?,?,?,?,?,?,?)");
     cs.setString(1, request.getParameter("time"+i));
     cs.setString(2, request.getParameter("mon"+i));
     cs.setString(3, request.getParameter("tue"+i));
     cs.setString(4, request.getParameter("wed"+i));
     cs.setString(5, request.getParameter("thurs"+i));
     cs.setString(6, request.getParameter("fri"+i));
     cs.setString(7, request.getParameter("sat"+i));
     cs.execute();
    }
   }
   catch (Exception ex)
   {
    //ex.printStackTrace(response.getWriter());
    Utils.Error(request, response, Utils.DBERRORPAGE);
    return;
   }
   response.sendRedirect("Home");
  }
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

}
