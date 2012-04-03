package HOADIS.Event;

import java.io.IOException;
import javax.servlet.*;
import java.sql.*;
import javax.servlet.http.*;
import HOADIS.*;
import HOADIS.beans.*;
import java.util.Vector;

public class NoticeBoard extends HttpServlet
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
    PreparedStatement c = con.prepareStatement("select count(distinct date) from event where date >= curdate()");
    ResultSet r = c.executeQuery();
    int n = 0;
    if (r.next())
    {
     n = r.getInt(1);
    }

    String dates[] = new String[n];

    PreparedStatement cs = con.prepareStatement("select distinct date from event where date >= curdate() order by date");
    ResultSet rs = cs.executeQuery();
    int i = 0;
    while (rs.next())
    {
     dates[i] =(rs.getDate("date")).toString();
     i++;
    }
    request.setAttribute("dates", dates);
    for (i = 0; i < n; i++)
    {
     Vector<HOADIS.beans.Event> events = new Vector<HOADIS.beans.Event>();
     PreparedStatement cs2 = con.prepareStatement("select * from event where date=?");
     cs2.setString(1, dates[i]);
     ResultSet rs2 = cs2.executeQuery();
     while (rs2.next())
     {
      events.add(new HOADIS.beans.Event(rs2.getString("title"), rs2.getString("category"), rs2.getString("author"), rs2.getString("detail"), rs2.getDate("date")));
     }
     request.setAttribute(dates[i], events);
    }
    rd = request.getRequestDispatcher(view);
    rd.forward(request, response);
   }
   catch (Exception ex)
   {
    //ex.printStackTrace(response.getWriter());
    Utils.Error(request, response, Utils.DBERRORPAGE);
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
 RequestDispatcher rd;
 String view = "/WEB-INF/Event/NoticeBoard.jsp";
}
