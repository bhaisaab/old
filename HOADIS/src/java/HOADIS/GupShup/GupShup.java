package HOADIS.GupShup;

import HOADIS.GupShup.*;
import java.io.IOException;
import javax.servlet.*;
import javax.servlet.http.*;
import HOADIS.*;
import HOADIS.beans.*;
import java.sql.*;
import java.util.Vector;

/**
 *
 * @author Rohit Yadav
 */
public class GupShup extends HttpServlet
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
    PreparedStatement c = con.prepareStatement("select max(id) from gupshup");
    ResultSet r = c.executeQuery();
    int n = 0;
    if (r.next())
    {
     n = r.getInt(1);
    }

    String msgs[] = new String[n];

    PreparedStatement cs = con.prepareStatement("select * from gupshup order by id");
    ResultSet rs = cs.executeQuery();
    int i = 0;
    while (rs.next())
    {
        msgs[i] = (rs.getString("id")).toString();
        i++;
    }
    request.setAttribute("msgs", msgs);
    for (i = 0; i < n; i++)
    {
     Vector<HOADIS.beans.GupShup> gupshups = new Vector<HOADIS.beans.GupShup>();
     PreparedStatement cs2 = con.prepareStatement("select * from gupshup where id=?");
     cs2.setString(1, msgs[i]);
     ResultSet rs2 = cs2.executeQuery();
     while (rs2.next())
     {
      gupshups.add(new HOADIS.beans.GupShup(rs2.getString("author"), rs2.getString("msg")));
     }
     request.setAttribute(msgs[i], gupshups);
    }
    rd = request.getRequestDispatcher(view);
    rd.forward(request, response);
   }
   catch (Exception ex)
   {
    ex.printStackTrace(response.getWriter());
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
 String view = "/WEB-INF/MicroBlog/GupShup.jsp";
}
