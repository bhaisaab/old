<%--
    Author      : Ajay Chhatwal
    Description : Result View Page
--%>

<%@page contentType="text/html" pageEncoding="UTF-8" isELIgnored="false" %>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
"http://www.w3.org/TR/html4/loose.dtd">

<html>

 <%-- Head Tags --%>
 <jsp:include page="/WEB-INF/parts/head.html"></jsp:include>

 <body>

    <%-- Header And Navigation Bars  --%>

  <jsp:include page="/WEB-INF/parts/header.jsp"></jsp:include>
  <jsp:include page="/WEB-INF/parts/sidenav.jsp"></jsp:include>

  <%-- Main JSP Content Begins  --%>

  <div class="content">
   <%@ page language="java" import="java.util.*,java.lang.*" session="true" buffer="8kb" %>
   <br>
   Roll no. : ${result.rno} <br>
   <br>
 
   ${result.TS1} : ${result.t1} <br>
   ${result.TS2} : ${result.t2} <br>
   ${result.TS3} : ${result.t3} <br>
   ${result.TS4} : ${result.t4} <br>
   ${result.TS5} : ${result.t5} <br>
   ${result.TS6} : ${result.t6} <br><br>
   ${result.PS1} : ${result.p1} <br>
   ${result.PS2} : ${result.p2} <br>
   ${result.PS3} : ${result.p3} <br>
   <br>
 
   SGPA : ${result.sgpa} <br>
 
  </div>
  <%-- Main JSP Content Ends  --%>

  <%-- Footer --%>
  <jsp:include page="/WEB-INF/parts/footer.html"></jsp:include>

 </body>

</html>