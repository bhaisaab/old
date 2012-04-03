<%--
    Author      : Ajay Chhatwal
    Description : Faculty's Profile Editor
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
       <% 
            HOADIS.beans.User userData = (HOADIS.beans.User) session.getAttribute("userData");
            String user = userData.getUser();
            out.println("<img src=\"/HOADIS-deploy/avatars/"+user+"\" alt=\"Upload Your Photo!\" height=\"128\">");
       
       %>
   <form name="gupshup" method="POST" action="AddPhoto" >
        <input type="submit" value="Upload Photo!" name="sub"/>
   </form>
   
   <form name="Profile" method="POST" action="UpdateProfile" >
    Username : ${faculty.user}  <br>
    Designation: <input type="text" name="desig" value="${faculty.desig}" size="20" maxlength="100"/><br>
    Qualifications: <input type="text" name="qual" value="${faculty.qual}" size="20" maxlength="100"/><br>
    Courses Taught:<input type="text" name="courses" value="${faculty.courses}" size="20" maxlength="100"/><br>
    Areas Of Interest:<input type="text" name="aoi" value="${faculty.aoi}" size="20"  maxlength="100"/><br>
    Email: <input type="text" name="email" value="${faculty.email}" size="20"  maxlength="100"/><br>
    Phone Numbers: <input type="text" name="ph" value="${faculty.ph}" size="10"  maxlength="100"/><br>
    HomePage : <input type="text" name="homepage" value="${faculty.homepage}" size="20" maxlength="100" /><br>
    <br>
    <input type="submit" value="Update" name="sub"/>
   </form>
   <br>
  </div>
  <%-- Main JSP Content Ends  --%>

  <%-- Footer --%>
  <jsp:include page="/WEB-INF/parts/footer.html"></jsp:include>

 </body>

</html>