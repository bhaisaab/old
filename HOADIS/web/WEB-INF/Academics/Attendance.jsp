<%--
    Author      : Ajay Chhatwal
    Description : Attendance Sheet
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
   <%@ page language="java" import="java.util.*,java.lang.*,HOADIS.beans.*" session="true" buffer="8kb" %>
   <form name="Attendance" method="POST" action="AddAttendance" >
    <table class="form-noindent" border="0" bgcolor="#aaffaa" cellpadding="5" cellspacing="3" width="90%" align="center">
     <tbody>
     <tr>
      <td style="text-align: center;" nowrap="nowrap" valign="top">
       <tr>
        <td colspan="2" align="center">
         <font size="5">
          <%
          Date date=new java.sql.Date(System.currentTimeMillis());
          out.println("Mark Attendance For "+date.getDate()+"-"+date.getMonth()+"-"+(date.getYear()+1900)+" <br>");
          %>
         </font>
        </td>
       </tr>

       <tr>
        <td colspan="2" align="center">
        </td>
       </tr>
      <%
      Subject subject = (Subject) session.getAttribute("subject");
      for (int i = 1; i <= subject.getLastrno(); i++)
      {
       out.println("<tr> <td > <div align=\"left\">");
       out.println("Roll No." + i + ": ");
       out.println("</div> </td> <td>");
       out.println("<input type=\"checkbox\" name=\"rno" + i + "\" value=\"1\" />");
       out.println("</td> </tr>");
      }
      %>
       <tr>
        <td></td>
        <td align="left">
        </td>
       </tr>

       <tr>
        <td></td>
        <td align="left">
         <input type="submit" value="Submit" name="sub"/>
        </td>
       </tr>
      </td>
     </tr>
     <tbody>
    </table>
   </form>
   <br>
  </div>
  <%-- Main JSP Content Ends  --%>

  <%-- Footer --%>
  <jsp:include page="/WEB-INF/parts/footer.html"></jsp:include>

 </body>

</html>