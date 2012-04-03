<%--
    Author      : Ajay Chhatwal
    Description : Student's Profile Editor
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
   
   <br />
   <form name="SProfile" method="POST" action="UpdateProfile" >
    Name : ${student.user}<br>
    Roll No. : <input type="text" name="rno" value="${student.rno}" size="15"  maxlength="15"/><br>
    Course   :
    <select name="course">
     <option ${BTech} >B.Tech.</option>
     <option ${IDD} >IDD</option>
    </select><br>
    Branch   : <input type="text" name="branch" value="${student.branch}" size="15" maxlength="50" /><br>
    Year     :
    <select name="year">
     <option value="0" ${y0} >Prep</option>
     <option value="1" ${y1} >First</option>
     <option value="2" ${y2} >Second</option>
     <option value="3" ${y3} >Third</option>
     <option value="4" ${y4} >Fourth</option>
     <option value="5" ${y5} >Fifth</option>
    </select><br>
    <br>
    HomePage :<input type="text" name="homepage" value="${student.homepage}" size="15" maxlength="50" /><br>
    Areas Of Interest
    <input type="text" name="aoi" value="${student.aoi}" size="20"  maxlength="100"/><br>
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