package HOADIS.Profile;

import java.io.IOException;
import javax.servlet.*;
import javax.servlet.http.*;
import HOADIS.*;
import HOADIS.beans.*;
import java.sql.*;

public class EditProfile extends HttpServlet
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
   String type = userData.getType();
   if (type.equals("S"))
   {
    //Get/Create student bean
    Student student = (Student) session.getAttribute("student");
    if (student == null)
    {
     try
     {
      Connection con = Utils.getDBConnection();
      String user = userData.getUser();
      PreparedStatement cs = con.prepareStatement("select * from student where user=?");
      cs.setString(1, user);
      ResultSet rs = cs.executeQuery();
      if (rs.next())
      {
       String rno = new String(rs.getString("rno"));
       String branch = new String(rs.getString("branch"));
       String course = new String(rs.getString("course"));
       String aoi = new String(rs.getString("aoi"));
       String homepage = new String(rs.getString("homepage"));
       int year = rs.getInt("year");
       student = new Student(user, rno, branch, year, course, aoi, homepage);
       if (student.getCourse().equals("IDD"))
       {
        request.setAttribute("IDD", "selected");
       }
       else
       {
        request.setAttribute("BTech", "selected");
       }
       request.setAttribute("y" + student.getYear(), "selected");
      }
      else
      {
       student = new Student();
       student.setUser(user);
      }
     }
     catch (Exception ex)
     {
      ex.printStackTrace(response.getWriter());
      //Utils.Error(request, response, Utils.DBERRORPAGE);
      return;
     }
     session.setAttribute("student", student);
    }

    view = "/WEB-INF/Profile/EditSProfile.jsp";
   }
   else if (type.equals("A"))
   {
    //Get/Create alumini bean
    Alumini alumini = (Alumini) session.getAttribute("alumini");
    if (alumini == null)
    {
     try
     {
      Connection con = Utils.getDBConnection();
      String user = userData.getUser();
      PreparedStatement cs = con.prepareStatement("select * from alumini where user=?");
      cs.setString(1, user);
      ResultSet rs = cs.executeQuery();
      if (rs.next())
      {
       String rno = new String(rs.getString("rno"));
       String branch = new String(rs.getString("branch"));
       String course = new String(rs.getString("course"));
       String aoi = new String(rs.getString("aoi"));
       String homepage = new String(rs.getString("homepage"));
       String profession = new String(rs.getString("profession"));
       String desig = new String(rs.getString("desig"));
       String org = new String(rs.getString("org"));
       int year = rs.getInt("year");
       alumini = new Alumini(user, rno, branch, year, course, aoi, homepage, profession, desig, org);
      }
      else
      {
       alumini = new Alumini();
       alumini.setUser(user);
      }
     }
     catch (Exception ex)
     {
      //ex.printStackTrace();
      Utils.Error(request, response, Utils.DBERRORPAGE);
      return;
     }
     session.setAttribute("alumini", alumini);
    }
    if (alumini.getCourse().equals("IDD"))
    {
     request.setAttribute("IDD", "selected");
    }
    else
    {
     request.setAttribute("BTech", "selected");
    }
    view = "/WEB-INF/Profile/EditAProfile.jsp";
   }
   else if (type.equals("F"))
   {
    //Get/Create faculty bean
    Faculty faculty = (Faculty) session.getAttribute("faculty");
    if (faculty == null)
    {
     try
     {
      Connection con = Utils.getDBConnection();
      String user = userData.getUser();
      PreparedStatement cs = con.prepareStatement("select * from faculty where user=?");
      cs.setString(1, user);
      ResultSet rs = cs.executeQuery();
      if (rs.next())
      {
       String desig = new String(rs.getString("desig"));
       String qual = new String(rs.getString("qual"));
       String courses = new String(rs.getString("courses"));
       String ph = new String(rs.getString("ph"));
       String email = new String(rs.getString("email"));
       String homepage = new String(rs.getString("homepage"));
       String aoi = new String(rs.getString("aoi"));
       faculty = new Faculty(user, desig, qual, courses, aoi, ph, email, homepage);
      }
      else
      {
       faculty = new Faculty();
       faculty.setUser(user);
      }
     }
     catch (Exception ex)
     {
      Utils.Error(request, response, Utils.DBERRORPAGE);
      return;
     }
     session.setAttribute("faculty", faculty);
    }
    view = "/WEB-INF/Profile/EditFProfile.jsp";
   }


   rd = request.getRequestDispatcher(view);
   rd.forward(request, response);
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
 String view = "/WEB-INF/Profile/Home.jsp";
}
