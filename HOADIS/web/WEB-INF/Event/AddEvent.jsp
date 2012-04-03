<%--
    Author      : Rohit Yadav
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@ page language="java" import="java.util.*,java.lang.*,java.sql.*,HOADIS.*,HOADIS.beans.*" session="true" buffer="8kb" %>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
"http://www.w3.org/TR/html4/loose.dtd">
<jsp:useBean class="HOADIS.beans.Event" id="event" scope="request"></jsp:useBean>
<jsp:setProperty name="event" property="*"></jsp:setProperty>
  <%
     try
     {

      Connection con = Utils.getDBConnection();
      //java.util.Date d=new java.util.Date(Integer.parseInt(request.getParameter("year"))-1900,Integer.parseInt(request.getParameter("month"))-1,Integer.parseInt(request.getParameter("day")),Integer.parseInt(request.getParameter("hour")),Integer.parseInt(request.getParameter("min")),0);
      event.setDate(new java.sql.Date(Integer.parseInt(request.getParameter("year"))-1900,Integer.parseInt(request.getParameter("month"))-1,Integer.parseInt(request.getParameter("day"))));
      PreparedStatement cs = con.prepareStatement("insert into event(title,category, author, detail, date) values (?,?,?,?,?) ");
      cs.setString(1, event.getTitle());
      cs.setString(2, event.getCategory());
      cs.setString(3, event.getAuthor());
      cs.setString(4, event.getDetail());
      cs.setDate(5, event.getDate());
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
