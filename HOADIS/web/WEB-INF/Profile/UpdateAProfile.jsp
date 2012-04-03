<%--
    Author      : Ajay Chhatwal
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@ page language="java" import="java.util.*,java.lang.*,java.sql.*,HOADIS.*,HOADIS.beans.*" session="true" buffer="8kb" %>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
"http://www.w3.org/TR/html4/loose.dtd">
<jsp:useBean class="HOADIS.beans.Alumini" id="alumini" scope="session"></jsp:useBean>
<jsp:setProperty name="alumini" property="*"></jsp:setProperty>
  <%
     try
     {
      Connection con = Utils.getDBConnection();
      PreparedStatement del = con.prepareStatement("delete from alumini where user=?");
      del.setString(1, alumini.getUser());
      del.execute();
      PreparedStatement cs = con.prepareStatement("insert into alumini(user, rno, branch, year, course, aoi, homepage, profession, desig, org) values (?,?,?,?,?,?,?,?,?,?) ");
      cs.setString(1, alumini.getUser());
      cs.setString(2, alumini.getRno());
      cs.setString(3, alumini.getBranch());
      cs.setString(4, ""+alumini.getYear());
      cs.setString(5, alumini.getCourse());
      cs.setString(6, alumini.getAoi());
      cs.setString(7,alumini.getHomepage());
      cs.setString(8,alumini.getProfession());
      cs.setString(9,alumini.getDesig());
      cs.setString(10,alumini.getOrg());
      cs.execute();
     }
     catch (Exception ex)
     {
      Utils.Error(request, response, Utils.DBERRORPAGE);
      return;
     }
     response.sendRedirect("Home");
  %>
