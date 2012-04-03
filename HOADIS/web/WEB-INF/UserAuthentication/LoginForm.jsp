<%--
    Author      : Ajay Chhatwal, Rohit Yadav
    Description : Login Page
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
  <table>

   <%@ page language="java" import="java.util.*,java.lang.*,java.sql.*;" session="true" buffer="8kb" %>
   <jsp:useBean id="userData" scope="session" class="HOADIS.beans.User" />
   <div  class="error" align="center">
    <jsp:getProperty  name="userData" property="loginError" />
    <br>
   </div>


   <br>
    <form name="login" method="POST" action="Login">
        <table class="form-noindent" border="0" bgcolor="#efa0c0" cellpadding="5" cellspacing="3" width="30%" align="center">
            <tbody>
                <tr>

                <td style="text-align: center;" nowrap="nowrap" valign="top">
                    <tr>
                    <td colspan="2" align="center">
                    <font size="-1">
                        Sign in to<strong> HOADIS </strong>with your
                    </font>
                    <table>
                    <tbody>
                    <tr>
                    <td valign="top">
                    <img src="media/logo.gif" alt="HOAD!S" width="70" height="25">

                    </td>
                    <td valign="middle">
                    <font size="+0"><b>Account</b></font>
                    </td>
                    </tr>
                    </tbody>
                    </table>
                    </td>
                    </tr>
                    
                    <tr>
                        <td colspan="2" align="center">
                        </td>
                    </tr>
                    
                    <tr>
                        <td nowrap="nowrap">
                        <div align="right">
                        Username:
                        </div>
                        </td>
                        <td>
                            <input type="text" name="user" value="" size="20" />
                        </td>
                    </tr>
                    <tr>
                        <td></td>
                        <td align="left">
                        </td>
                    </tr>

                    <tr>
                        <td align="right">
                        Password:
                        </td>
                        <td>
                            <input type="password" name="pass" value="" size="20" />
                        </td>
                    </tr>

                    <tr>
                    <td></td>
                        <td align="left">
                        </td>
                    </tr>

                    <tr>
                    <td></td>
                    <td align="left">
                        <input type="submit" value="Login" name="sub"/>
                    </td>
                    </tr>

                    <tr>
                    <td colspan="2" align="center" height="33" valign="bottom">
                        Not Registered?
                        <a href="RegisterForm">
                        Register Now!
                        </a>
                    </td>
                    </tr>
    
                </td>
                </tr>
            <tbody>
       </table>
   </form>
   <br>

   </table>
  <%-- Main JSP Content Ends  --%>

 <%-- Footer --%>
  <jsp:include page="/WEB-INF/parts/footer.html"></jsp:include>

 </body>

</html>