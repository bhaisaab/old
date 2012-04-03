<%--
    Author      : Ajay Chhatwal
    Description : Alumini's Profile Editor
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
            out.println("<img src=\"/HOADIS-deploy/avatars/"+user+"\" alt=\"Upload Your Photo!\" height=\"128\" width=\"128\">");
       
       %>
   <form name="gupshup" method="POST" action="AddPhoto" >
        <input type="submit" value="Upload Photo!" name="sub"/>
   </form>
   
   <form name="SProfile" method="POST" action="UpdateProfile" >
    Name     : <input type="text" name="user" value="${alumini.user}" size="15"  maxlength="15"/><br>
    Roll No. : <input type="text" name="rno" value="${alumini.rno}" size="15"  maxlength="15"/><br>
    Course   :
    <select name="course">
     <option ${BTech} >B.Tech.</option>
     <option ${IDD} >IDD</option>
    </select><br>
    Branch   : <input type="text" name="branch" value="${alumini.branch}" size="15" maxlength="50" /><br>
    Year Of Course Completion :<input type="text" name="year" value="${alumini.year}" size="4"  maxlength="4"/>
    <br>
    HomePage :<input type="text" name="homepage" value="${alumini.homepage}" size="15" maxlength="50" /><br>
    Profession: <input type="text" name="profession" value="${alumini.profession}" size="20" maxlength="20"/><br>
    Designation: <input type="text" name="desig" value="${alumini.desig}" size="20" maxlength="20"/><br>
    Organisation: <input type="text" name="org" value="${alumini.org}" size="20" maxlength="30"/><br>
    Areas Of Interest:
    <input type="text" name="aoi" value="${alumini.aoi}" size="20"  maxlength="100"/><br>
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