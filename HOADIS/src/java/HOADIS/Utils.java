package HOADIS;
import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.http.*;
import java.sql.*;
import javax.servlet.RequestDispatcher;

public class Utils
{
 public static final String UNAUTHORISEDPAGE = "/WEB-INF/Error/Unauthorised.jsp";
 public static final String DBERRORPAGE = "/WEB-INF/Error/DBError.jsp";

 private static final String DBDRIVER = "com.mysql.jdbc.Driver";
 private static final String DBURL = "jdbc:mysql://localhost:3306/hoadis";
 private static final String DBUSER ="hoadis";
 private static final String DBPASS ="hoadis";

 private static RequestDispatcher rd;

 public static void unauthorised(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException
 {
  rd = request.getRequestDispatcher(UNAUTHORISEDPAGE);
  rd.forward(request, response);
 }

 public static void Error(HttpServletRequest request, HttpServletResponse response,String ErrorPage) throws IOException, ServletException
 {
  rd = request.getRequestDispatcher(ErrorPage);
  rd.forward(request, response);
 }

 public static Connection getDBConnection() throws ClassNotFoundException, SQLException
 {
  Connection con=null;
  Class.forName(DBDRIVER);
  con=DriverManager.getConnection(DBURL,DBUSER ,DBPASS);
  return con;
 }
}
