<%--
    Author      : Rohit Yadav
    Description : GupShup MicroBlogging
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

    <form name="gupshup" method="POST" action="AddGupShup" >
        <table class="form-noindent" border="0" bgcolor="#ff9095" cellpadding="5" cellspacing="3" width="90%" align="center">
            <tbody>
                <tr>

                <td style="text-align: center;" nowrap="nowrap" valign="top">
                    <tr>
                    <td colspan="2" align="center">
                    <font size="5">
                    GupShup MicroBlogging on <img src="media/logo.gif" alt="HOAD!S" width="70" height="25"> SPEAK UP!
                    </font>
                    </td>
                    
                    </tr>
                 
                    <tr>
                        <td nowrap="nowrap">
                        <div align="left">
                        GupShup:
                        </div>
                        </td>
                        <td>
                            <textarea name="msg" rows="3" cols="100">
                            </textarea>
                        </td>
                    </tr>

                    <tr>
                    <td></td>
                    <td align="left">
                        <input type="submit" value="New GupShup!" name="sub"/>
                    </td>
                    </tr>
    
                </td>
                </tr>
            <tbody>
       </table>
   </form>

   <br />

   <%
   HOADIS.beans.User userData = (HOADIS.beans.User) session.getAttribute("userData");
     String user = userData.getUser();
     //out.println("<b>"+user+"</b>");
   String[] msgs=(String[])request.getAttribute("msgs");
     for (int i = msgs.length-1; i >=0 ; i--)
     {
      java.util.Vector<HOADIS.beans.GupShup> e =(java.util.Vector<HOADIS.beans.GupShup>) request.getAttribute(msgs[i]);
      
      for (int j = 0; j < e.size(); j++)
      {
       
       if( e.elementAt(j).getAuthor().equals(user) )
           out.println("<table bgcolor=\"#6CA24B\" width=\"90%\" align=\"center\">");
       else
           out.println("<table bgcolor=\"#99CF63\" width=\"90%\" align=\"center\">");
      
       out.println("<tbody><td>");
       out.println("<div><h3>");
       out.println("<img src=\"/HOADIS-deploy/avatars/" + e.elementAt(j).getAuthor() + "\" alt=" + e.elementAt(j).getAuthor()+ "\" height=\"64\">");
       out.println("<b>");
       out.println(e.elementAt(j).getAuthor()+": ");
       out.println("</b></h3>");
       out.println(e.elementAt(j).getMessage());
       out.println("</div>");
       
       out.println("</td></tbody></table>");
      
      }

      out.println("<br />");
     }
    %>

   </div> 
   <%-- Main JSP Content Ends  --%>

  <%-- Footer --%>
  <jsp:include page="/WEB-INF/parts/footer.html"></jsp:include>

 </body>

</html>