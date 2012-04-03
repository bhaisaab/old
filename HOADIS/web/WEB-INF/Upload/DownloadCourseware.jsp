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
    <table class="form-noindent" border="0" bgcolor="#7999C3" cellpadding="5" cellspacing="3" width="90%" align="center">
    <tbody>
    <td>
    <font size="5" align="center">
    Download Courseware on <img src="media/logo.gif" alt="HOAD!S" width="70" height="25">
    </font>
    </td>
    </tbody>
    </table>
    <br />
    <br />
                   
    <%
   HOADIS.beans.User userData = (HOADIS.beans.User) session.getAttribute("userData");
     String user = userData.getUser();
     //out.println("<b>"+user+"</b>");
   String[] msgs=(String[])request.getAttribute("msgs");
     for (int i = msgs.length-1; i >=0 ; i--)
     {
      java.util.Vector<HOADIS.beans.Courseware> e =(java.util.Vector<HOADIS.beans.Courseware>) request.getAttribute(msgs[i]);
      
      for (int j = 0; j < e.size(); j++)
      {
          
       if( (i%2) == 0 )
           out.println("<table bgcolor=\"#ff9090\" width=\"90%\" align=\"center\">");
       else
           out.println("<table bgcolor=\"#ff7575\" width=\"90%\" align=\"center\">");
      
       out.println("<td>");
       out.println("<div><h3>");
       out.println("<a href=\"/HOADIS-deploy/courseware/" + e.elementAt(j).getFilename() + "\">" + e.elementAt(j).getFilename().toUpperCase() + "</a>" );
       out.println("uploaded by <b>");
       out.println(e.elementAt(j).getUploader().toUpperCase());
       out.println("<img src=\"/HOADIS-deploy/avatars/" + e.elementAt(j).getUploader().toLowerCase() + "\" alt=" + e.elementAt(j).getUploader()+ "\" height=\"48\">");
       out.println("</b></h3>");
       out.println("</div>");
       
       out.println("</td></table>");
      
      }

      out.println("<br />");
     }
   out.println("</div>");
    %>


    </div> 
   <%-- Main JSP Content Ends  --%>

  <%-- Footer --%>
  <jsp:include page="/WEB-INF/parts/footer.html"></jsp:include>

 </body>

</html>