<%--
    Author      : Ajay Chhatwal
    Description : User's Home Page
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
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

    </div> 
   <%-- Main JSP Content Ends  --%>

  <%-- Footer --%>
  <jsp:include page="/WEB-INF/parts/footer.html"></jsp:include>

 </body>

</html>