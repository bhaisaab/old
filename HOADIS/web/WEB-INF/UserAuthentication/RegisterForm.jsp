<%--
    Author      : Ajay Chhatwal
    Description : Registeration Page
--%>

<%@page contentType="text/html"  pageEncoding="UTF-8"%>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
"http://www.w3.org/TR/html4/loose.dtd">

<html>

 <%-- Head Tags --%>
 <jsp:include page="/WEB-INF/parts/head.html"></jsp:include>

 <body>
<%-- Header  --%>
  <jsp:include page="/WEB-INF/parts/header.html"></jsp:include>

  <%-- Main JSP Content Begins  --%>

  <div class="content">

   <h2>Please register yourself to be able to access HOADIS.</h2>
   <jsp:useBean id="userData" scope="session" class="HOADIS.beans.User" />
   <div  class="error">
    <jsp:getProperty  name="userData" property="registerError" />
   </div>
   <br>
   <form name="reg" action="Register" method="POST">
    Username: <input type="text" name="user" value="" size="18" />
    <br>
    Password: <input type="password" name="pass" value="" size="18" /><br><br>
    User Type:
    <select name="type">
     <option value="S">Student</option>
     <option value="F">Faculty</option>
     <option value="A">Alumnus</option>
     <option value="X">Administrator</option>
    </select>
    <br>
    <br>
    <input type="hidden" name="check_val" value="false" />
    <input type="submit" value="Register" name="sub"  />
   </form>
  </div>
  <%-- Main JSP Content Ends  --%>

  <%-- Footer --%>
  <jsp:include page="/WEB-INF/parts/footer.html"></jsp:include>

 </body>

</html>
