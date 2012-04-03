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
<script>
function showMe (it, box) {
var vis = (box.checked) ? "block" : "none";
var e=document.getElementsByName(it);
for(var i=0;i<e.length;i++)
 e[i].style.display = vis;
}
</script>
  <div class="content">
    Show:<br>
    Workshops <input type="checkbox" onclick="showMe('Workshop', this)" checked>&nbsp;&nbsp&nbsp;&nbsp;
    Seminars <input type="checkbox" onclick="showMe('Seminar', this)" checked>&nbsp;&nbsp&nbsp;&nbsp;
    Competitions <input type="checkbox"  onclick="showMe('Competition', this)" checked>&nbsp;&nbsp&nbsp;&nbsp;
    Cultural Events <input type="checkbox"  onclick="showMe('Cultural Event', this)" checked>&nbsp;&nbsp&nbsp;&nbsp;
    Other Events <input type="checkbox"  onclick="showMe('Other', this)" checked>
    <br>
    <br>
   <%
   String[] dates=(String[])request.getAttribute("dates");
     for (int i = 0; i < dates.length; i++)
     {
      java.util.Vector<HOADIS.beans.Event> e =(java.util.Vector<HOADIS.beans.Event>) request.getAttribute(dates[i]);

      for (int j = 0; j < e.size(); j++)
      {
       out.println("<div name="+e.elementAt(j).getCategory()+">");
       out.println("<br>");
       out.println("Date: "+e.elementAt(j).getDate());
       out.println("<br>");
       out.println("Title: "+e.elementAt(j).getTitle());
       out.println("<br>");
       out.println("Author: "+e.elementAt(j).getAuthor());
       out.println("<br>");
       out.println("Category: "+e.elementAt(j).getCategory());
       out.println("<br>");
       out.println("Details: "+e.elementAt(j).getDetail());
       out.println("<br>");
       out.println("<hr>");
       out.println("</div>");
      }
     }
    %>
    </div>
<%-- Main JSP
      Content Ends--%>

  <%-- Footer --%>
  <jsp:include page="/WEB-INF/parts/footer.html"></jsp:include>

 </body>

</html>
