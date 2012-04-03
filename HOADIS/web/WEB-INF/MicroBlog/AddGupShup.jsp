<%--
    Author      : Rohit Yadav
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@ page language="java" import="java.util.*,java.lang.*,java.sql.*,HOADIS.*,HOADIS.beans.*" session="true" buffer="8kb" %>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
"http://www.w3.org/TR/html4/loose.dtd">
<jsp:useBean class="HOADIS.beans.GupShup" id="gupshup" scope="request"></jsp:useBean>
<jsp:setProperty name="gupshup" property="*"></jsp:setProperty>
  <%
     try
     {
     HOADIS.beans.User userData = (HOADIS.beans.User) session.getAttribute("userData");
     String user = userData.getUser();
     
     gupshup.setMessage(request.getParameter("msg"));
     if(request.getParameter("msg") == null)
     {
       return;
     }
      Connection con = Utils.getDBConnection();
      PreparedStatement cs = con.prepareStatement("insert into gupshup(author, msg) values (?,?) ");
      cs.setString(1, user);
      cs.setString(2, gupshup.getMessage());
      cs.execute();
     }
     catch (Exception ex)
     {
      //ex.printStackTrace(response.getWriter());
      Utils.Error(request, response, Utils.DBERRORPAGE);
      return;
     }
     response.sendRedirect("GupShup");
  %>
