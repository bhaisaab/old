   <%
   String error=(String)session.getAttribute("Error");
   if (error==null)
       error="";
   if(error != "")
   {
    out.println("<font color=\"red\"> ");
    out.println(error+" <br> <br>");
    out.println("</font> ");
   }
   %>