<%--
    Author      : Ajay Chhatwal
    Document   : Subject Selector
--%>

<%@page contentType="text/html" pageEncoding="UTF-8" import="java.util.Vector" %>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
"http://www.w3.org/TR/html4/loose.dtd">

<html>

 <%-- Head Tags --%>
 <jsp:include page="/WEB-INF/parts/head.html"></jsp:include>

  <%-- Header And Navigation Bars  --%>
  <jsp:include page="/WEB-INF/parts/header.jsp"></jsp:include>
  <jsp:include page="/WEB-INF/parts/sidenav.jsp"></jsp:include>
 <head>
  <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
  <title>JSP Page</title>
 </head>
 <body>
  Select Subject Code:
  <br><br>
  <form name="getSubject" action="EditSubject" method="post">
     <select name="subject" onchange="document.getSubject.submit();" >
     <%
      Vector<String> subjectList = (Vector<String>) request.getAttribute("subjectList");
      out.println("<option value=\"new\" > Add New Subject </option>");
      for(int i=0;i<subjectList.size();i++)
       out.println("<option>"+subjectList.get(i)+"</option>");
     %>
    </select><br><br>
    <input type="submit" value="Submit" />
  </form>

 </body>
</html>
