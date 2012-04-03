<%-- 
    Document   : header
    Created on : 2 Apr, 2009, 11:17:28 PM
    Author     : ajay
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
"http://www.w3.org/TR/html4/loose.dtd">

<div id="top">

 <table align="center" border="0" cellpadding="0" cellspacing="0" width="95%">
  <tbody><tr valign="top">
    <td width="1%">
     <img src="media/logo.gif" alt="HOADIS" align="left" border="0" height="59" vspace="10" width="143">
    </td>
    <td bgcolor="#ffffff" valign="top" width="99%">
     <table cellpadding="1" width="100%">
      <tbody><tr valign="bottom">
        <td><div align="right">&nbsp;</div></td>
       </tr>
       <tr>
        <td nowrap="nowrap">
         <table style="margin-bottom: 5px;" align="center" bgcolor="#9dfd9d" cellpadding="0" cellspacing="0" width="100%">
          <tbody><tr>
            <td class="bubble tl" align="left" valign="top"><img src="media/corner_tl.gif" class="c" alt=""></td>
            <td class="bubble" rowspan="2" style="padding: 5px 0pt; font-family: arial; text-align: left; font-weight: bold;">
            <b>HOAD!S: Hypermedia Open Architecture Departmental Information System</b></td>
            <td class="bubble tr" align="right" valign="top"><img src="media/corner_tr.gif" class="c" alt=""></td>
           </tr>
           <tr>
            <td class="bubble bl" align="left" valign="bottom"><img src="media/corner_bl.gif" class="c" alt=""></td>
            <td class="bubble br" align="right" valign="bottom"><img src="media/corner_br.gif" class="c" alt=""></td>
           </tr>

         </tbody></table>
        </td>
       </tr>
     </tbody></table>
    </td>
   </tr>
 </tbody></table>
 <nobr>
  <p align="right">
   <%
     HOADIS.beans.User userData = (HOADIS.beans.User) session.getAttribute("userData");
     String user = userData.getUser();
     String type = userData.getType();
     if (user == null || type == null) {
      userData.setLoginError("You Are Not Logged In.");
      response.sendRedirect("index.jsp");
      return;
     }
     else {
      out.println("Welcome <b align=\"right\">" + user.toUpperCase() + "!</b>");
      out.println("| Access Privilege: ");
      if (type.matches("S")) {
       out.println("Student |");
      }
      if (type.matches("F")) {
       out.println("Faculty |");
      }
      if (type.matches("A")) {
       out.println("Alumnus |");
      }
      if (type.matches("G")) {
       out.println("Guest |");
      }
      if (type.matches("X")) {
       out.println("Admin |");
      }
     }
   %>
   <a href="Logout">Sign Out</a>
  </p>
 </nobr>
</div>