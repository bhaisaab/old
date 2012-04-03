<%-- 
    Document   : sidenav
    Created on : 31 Jan, 2009, 1:29:56 PM
    Author     : ajay
--%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@ page language="java" import="java.util.*,java.lang.*,java.sql.*,HOADIS.*,HOADIS.beans.*" session="true" buffer="8kb" %>
<div class="left">
 <ul>

  <%
     Vector<Link> links = (Vector<Link>) session.getAttribute("links");
     if(links!=null)
     {
      for (int i = 0; i < links.size(); i++) {
      Link link = links.elementAt(i);
      out.println("<li> <a href =\"" + link.getUrl() + "\" >" + link.getName() + "</a> </li>");
      out.println("<br>");
      }
     }
  %>
 </ul>
 </div>
