<%@page contentType="text/html" pageEncoding="UTF-8"%>
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
  Select Year To View The Time Table.
  <br><br>
  <form name="getyear" action="TimeTable" method="post">
     <select name="year" onchange="document.getyear.submit();" >
     <option value="1" ${y1} >First</option>
     <option value="2" ${y2} >Second</option>
     <option value="3" ${y3} >Third</option>
     <option value="4" ${y4} >Fourth</option>
     <option value="5" ${y5} >Fifth</option>
    </select><br><br>
    <input type="submit" value="Submit" />
  </form>

 </body>
</html>
