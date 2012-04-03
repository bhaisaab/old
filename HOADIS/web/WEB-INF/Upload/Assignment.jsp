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
 
  <%-- Header And Navigation Bars  --%>
  <jsp:include page="/WEB-INF/parts/header.jsp"></jsp:include>
  <jsp:include page="/WEB-INF/parts/sidenav.jsp"></jsp:include>

 <body>

  <%-- Header And Navigation Bars  --%>


  <%-- Main JSP Content Begins  --%>

    <div class="content"> 

    <form name="assignment" enctype="multipart/form-data" method="POST" action="SaveAssignment" >
        <table class="form-noindent" border="0" bgcolor="#ffccaa" cellpadding="5" cellspacing="3" width="90%" align="center">
            <tbody>
                <tr>

                <td style="text-align: center;" nowrap="nowrap" valign="top">
                    <tr>
                    <td colspan="2" align="center">
                    <font size="5">
                    Submit Assigment on <img src="media/logo.gif" alt="HOAD!S" width="70" height="25">
                    </font>
                    </td>
                    
                    </tr>
                    
                    <tr>
                        <td colspan="2" align="center">
                        </td>
                    </tr>
                    
                    <tr>
                        <td nowrap="nowrap">
                        <div align="left">
                        Title:
                        </div>
                        </td>
                        <td>
                            <input type="text" name="name" value="" size="50" />
                        </td>
                    </tr>

                    <tr>
                        <td nowrap="nowrap">
                        <div align="left">
                        Subject ID:
                        </div>
                        </td>
                        <td>
                            <input type="text" name="id" value="" size="50" />
                        </td>
                    </tr>

                    <tr>
                        <td align="left">
                        File:
                        </td>
                        <td>
                            <input type="file" name="file" value="" size="50" />
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
                        <input type="submit" value="Submit Assignment" name="sub"/>
                    </td>
                    </tr>
    
                </td>
                </tr>
            <tbody>
       </table>
   </form>

    </div> 
   <%-- Main JSP Content Ends  --%>

  <%-- Footer --%>
  <jsp:include page="/WEB-INF/parts/footer.html"></jsp:include>

 </body>

</html>