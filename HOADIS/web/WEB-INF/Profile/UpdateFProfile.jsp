<%--
    Author      : Ajay Chhatwal
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@ page language="java" import="java.util.*,java.lang.*,java.sql.*,HOADIS.*,HOADIS.beans.*" session="true" buffer="8kb" %>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
"http://www.w3.org/TR/html4/loose.dtd">
<jsp:useBean class="HOADIS.beans.Faculty" id="faculty" scope="session"></jsp:useBean>
<jsp:setProperty name="faculty" property="*"></jsp:setProperty>
  <%
     try
     {
      Connection con = Utils.getDBConnection();
      PreparedStatement del = con.prepareStatement("delete from faculty where user=?");
      del.setString(1, faculty.getUser());
      del.execute();
      PreparedStatement cs = con.prepareStatement("insert into faculty(user, desig, qual, courses, aoi, ph, email, homepage) values (?,?,?,?,?,?,?,?) ");
      cs.setString(1, faculty.getUser());
      cs.setString(2, faculty.getDesig());
      cs.setString(3, faculty.getQual());
      cs.setString(4, faculty.getCourses());
      cs.setString(5, faculty.getAoi());
      cs.setString(6, faculty.getPh());
      cs.setString(7,faculty.getEmail());
      cs.setString(8,faculty.getHomepage());
      cs.execute();
     }
     catch (Exception ex)
     {
      ex.printStackTrace(response.getWriter());
      //Utils.Error(request, response, Utils.DBERRORPAGE);
      return;
     }
     response.sendRedirect("Home");
  %>
