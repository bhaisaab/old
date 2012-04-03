<%-- 
    Document   : EditTimeTable
    Created on : 4 Apr, 2009, 2:46:27 AM
    Author     : ajay
--%>

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
  <form action="UpdateTimeTable" method="post" >
   <table border="1" frame="box">
    <thead>
     <tr>
      <th>Time</th>
      <th>Mon</th>
      <th>Tue</th>
      <th>Wed</th>
      <th>Thurs</th>
      <th>Fri</th>
      <th>Sat</th>
     </tr>
    </thead>
    <tbody>
     <tr>
      <td><input type="text" name="time1" value="${time1}" size="10" /></td>
      <td><input type="text" name="mon1" value="${mon1}" size="10" /></td>
      <td><input type="text" name="tue1" value="${tue1}" size="10" /></td>
      <td><input type="text" name="wed1" value="${wed}" size="10" /></td>
      <td><input type="text" name="thurs1" value="${thurs1}" size="10" /></td>
      <td><input type="text" name="fri1" value="${fri1}" size="10" /></td>
      <td><input type="text" name="sat1" value="${sat1}" size="10" /></td>
     </tr>
     <tr>
      <td><input type="text" name="time2" value="${time2}" size="10" /></td>
      <td><input type="text" name="mon2" value="${mon2}" size="10" /></td>
      <td><input type="text" name="tue2" value="${tue2}" size="10" /></td>
      <td><input type="text" name="wed2" value="${wed2}" size="10" /></td>
      <td><input type="text" name="thurs2" value="${thurs2}" size="10" /></td>
      <td><input type="text" name="fri2" value=""${fri2}" size="10" /></td>
      <td><input type="text" name="sat2" value="${sat2}" size="10" /></td>
     </tr>
     <tr>
      <td><input type="text" name="time3" value="${time3}" size="10" /></td>
      <td><input type="text" name="mon3" value="${mon3}" size="10" /></td>
      <td><input type="text" name="tue3" value="${tue3}" size="10" /></td>
      <td><input type="text" name="wed3" value="${wed3}" size="10" /></td>
      <td><input type="text" name="thurs3" value="${thurs3}" size="10" /></td>
      <td><input type="text" name="fri3" value=""${fri3}" size="10" /></td>
      <td><input type="text" name="sat3" value="${sat3}" size="10" /></td>
     </tr>
     <tr>
      <td><input type="text" name="time4" value="${time4}" size="10" /></td>
      <td><input type="text" name="mon4" value="${mon4}" size="10" /></td>
      <td><input type="text" name="tue4" value="${tue4}" size="10" /></td>
      <td><input type="text" name="wed4" value="${wed4}" size="10" /></td>
      <td><input type="text" name="thurs4" value="${thurs4}" size="10" /></td>
      <td><input type="text" name="fri4" value=""${fri4}" size="10" /></td>
      <td><input type="text" name="sat4" value="${sat4}" size="10" /></td>
     </tr>
     <tr>
      <td><input type="text" name="time5" value="${time5}" size="10" /></td>
      <td><input type="text" name="mon5" value="${mon5}" size="10" /></td>
      <td><input type="text" name="tue5" value="${tue5}" size="10" /></td>
      <td><input type="text" name="wed5" value="${wed5}" size="10" /></td>
      <td><input type="text" name="thurs5" value="${thurs5}" size="10" /></td>
      <td><input type="text" name="fri5" value=""${fri5}" size="10" /></td>
      <td><input type="text" name="sat5" value="${sat5}" size="10" /></td>
     </tr>
     <tr>
      <td><input type="text" name="time6" value="${time6}" size="10" /></td>
      <td><input type="text" name="mon6" value="${mon6}" size="10" /></td>
      <td><input type="text" name="tue6" value="${tue6}" size="10" /></td>
      <td><input type="text" name="wed6" value="${wed6}" size="10" /></td>
      <td><input type="text" name="thurs6" value="${thurs6}" size="10" /></td>
      <td><input type="text" name="fri6" value=""${fri6}" size="10" /></td>
      <td><input type="text" name="sat6" value="${sat6}" size="10" /></td>
     </tr>
     <tr>
      <td><input type="text" name="time7" value="${time7}" size="10" /></td>
      <td><input type="text" name="mon7" value="${mon7}" size="10" /></td>
      <td><input type="text" name="tue7" value="${tue7}" size="10" /></td>
      <td><input type="text" name="wed7" value="${wed7}" size="10" /></td>
      <td><input type="text" name="thurs7" value="${thurs7}" size="10" /></td>
      <td><input type="text" name="fri7" value=""${fri7}" size="10" /></td>
      <td><input type="text" name="sat7" value="${sat7}" size="10" /></td>
     </tr>

    </tbody>
   </table>
   <br>
   <input align="middle" type="submit" value="Update" />
  </form>

 </body>
</html>
