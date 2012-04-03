<%--
    Author      : Ajay Chhatwal
    Description : Subject Editor
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
   <form name="SProfile" method="POST" action="UpdateSubject" >
    <table class="form-noindent" border="0" bgcolor="#aaffaa" cellpadding="5" cellspacing="3" width="90%" align="center">
     <tbody>
     <tr>
      <td style="text-align: center;" nowrap="nowrap" valign="top">
       <tr>
        <td colspan="2" align="center">
         <font size="5">
          Edit Subject Information
         </font>
        </td>
       </tr>

       <tr>
        <td colspan="2" align="center">
        </td>
       </tr>
       <tr>
        <td >
         <div align="left">
          Name:
         </div>
        </td>
        <td>
         <input type="text" name="name" value="${subject.name}" size="15"  maxlength="255"/>
        </td>
       </tr>
       <tr>
        <td >
         <div align="left">
          Code :
         </div>
        </td>
        <td>
         <input type="text" name="code" value="${subject.code}" size="10"  maxlength="10"/>
        </td>
       </tr>
       <tr>
        <td >
         <div align="left">
          Course:
         </div>
        </td>
        <td>
         <select name="course">
          <option ${BTech} >B.Tech.</option>
          <option ${IDD} >IDD</option>
         </select><br>
        </td>
       </tr>
       <tr>
        <td >
         <div align="left">
          Department:
         </div>
        </td>
        <td>
         Computer Science And Engineering
        </td>
       </tr>
       <tr>
        <td >
         <div align="left">
          Semester:
         </div>
        </td>
        <td>
         <input type="text" name="sem" value="${subject.sem}" size="2" maxlength="2" /><br>
        </td>
       </tr>
       <tr>
        <td align="left">
         Teacher:
        </td>
        <td>
         <input type="text" name="teacher" value="${subject.teacher}" size="15" maxlength="255" /><br>
        </td>
       </tr>
       <tr>
        <td align="left">
         Roll No. Range:
        </td>
        <td>
         1 to <input type="text" name="lastrno" value="${subject.lastrno}" size="2"  maxlength="3"/>
        </td>
       </tr>
       <tr>

       <tr>
        <td></td>
        <td align="left">
        </td>
       </tr>

       <tr>
        <td></td>
        <td align="left">
         <input type="submit" value="Update" name="sub"/>
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