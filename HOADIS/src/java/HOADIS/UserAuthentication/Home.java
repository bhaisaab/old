package HOADIS.UserAuthentication;

import java.io.IOException;
import javax.servlet.*;
import javax.servlet.http.*;
import HOADIS.*;
import HOADIS.beans.*;
import java.sql.*;
import java.util.Vector;

/**
 *
 * @author ajay
 */
public class Home extends HttpServlet
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
    PreparedStatement ls = con.prepareStatement("select * from link where type=? OR type='E' order by id");
    ls.setString(1, userData.getType());
    ResultSet rsl = ls.executeQuery();
    Vector<Link> links=new Vector<Link>(15);
    while(rsl.next())
    {
     links.add( new Link(rsl.getString("name"), rsl.getString("url")));
    }
    session.setAttribute("links", links);
   }
   catch
    (Exception ex)
   {
    ex.printStackTrace(response.getWriter());
    //Utils.Error(request, response, Utils.DBERRORPAGE);
    return;
   }
/*
   try
   {
    int id = 0;
    Connection con = Utils.getDBConnection();
    PreparedStatement cs = con.prepareStatement("select max(id) from event");

    ResultSet rs = cs.executeQuery();
    
    if (rs.next())
    {
        id = rs.getInt(1);
    }
    
    HOADIS.beans.Event latestEvent[] = new HOADIS.beans.Event[3];
    
    
    for( int i = 0; (i < 3) && (id > 0); i++)
    {
      PreparedStatement cs2 = con.prepareStatement("select * from event where id=?");
      cs2.setInt(1, id);
      
     ResultSet rs2 = cs2.executeQuery();
     if (rs2.next())
     {
             // String temp = rs2.getString(5);
         latestEvent[i] = new HOADIS.beans.Event(id, rs2.getString("title"), rs2.getString("category"), rs2.getString("author"), rs2.getString("detail"), rs2.getInt("date"), rs2.getInt("month"), rs2.getInt("year"));
         --id;
     }
    }
    session.setAttribute("latestEvent", latestEvent);
   }
   catch
    (Exception ex)
   {
    ex.printStackTrace(response.getWriter());
    //Utils.Error(request, response, Utils.DBERRORPAGE);
    return;
   }
 */
  }
  rd = request.getRequestDispatcher(view);
  rd.forward(request, response);
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
  Utils.unauthorised(request, response);
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
 RequestDispatcher rd;
 String view = "/WEB-INF/UserAuthentication/Home.jsp";
}
