<%--
    Author      : Ajay Chhatwal
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@ page language="java" import="java.util.*,java.lang.*,java.sql.*,HOADIS.*,HOADIS.beans.*" session="true" buffer="8kb" %>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
"http://www.w3.org/TR/html4/loose.dtd">
<jsp:useBean class="HOADIS.beans.Student" id="student" scope="session"></jsp:useBean>
<jsp:setProperty name="student" property="*"></jsp:setProperty>
  <%
     try
     {
      Connection con = Utils.getDBConnection();
      PreparedStatement del = con.prepareStatement("delete from student where user=?");
      del.setString(1, student.getUser());
      del.execute();
      PreparedStatement cs = con.prepareStatement("insert into student(user, rno, branch, year, course, aoi, homepage) values (?,?,?,?,?,?,?) ");
      cs.setString(1, student.getUser());
      cs.setString(2, student.getRno());
      cs.setString(3, student.getBranch());
      cs.setString(4, ""+student.getYear());
      cs.setString(5, student.getCourse());
      cs.setString(6, student.getAoi());
      cs.setString(7,student.getHomepage());
      cs.execute();
     }
     catch (Exception ex)
     {
      //ex.printStackTrace(response.getWriter());
      Utils.Error(request, response, Utils.DBERRORPAGE);
      return;
     }
     response.sendRedirect("Home");
  %>
