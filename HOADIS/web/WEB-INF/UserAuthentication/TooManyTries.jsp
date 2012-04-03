<%--
    Author      : Ajay Chhatwal
    Description : More Than 10 Tries Error Page
--%>

<%@page contentType="text/html"  pageEncoding="UTF-8"%>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
   "http://www.w3.org/TR/html4/loose.dtd">

<html>

 <%-- Head Tags --%>
 <jsp:include page="/WEB-INF/parts/head.html"></jsp:include>

 <body>

  <%-- Header And Navigation Bars  --%>

  <jsp:include page="/WEB-INF/parts/header.html"></jsp:include>
  <jsp:include page="/WEB-INF/parts/topnav.jsp"></jsp:include>
  <jsp:include page="/WEB-INF/parts/sidenav.jsp"></jsp:include>

  <%-- Main JSP Content Begins  --%>
  <div class="content">
  <h1> <br>
  You have already tried to login incorrectly 10 times. <br>
  Please restart your browser to login again.
  Or contact your Administrator.<br>
  </h1>

 </div>
  <%-- Main JSP Content Ends  --%>

  <%-- Footer --%>
  <jsp:include page="/WEB-INF/parts/footer.html"></jsp:include>

 </body>

</html>
