<%--
    Author      : Ajay Chhatwal
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@ page language="java" import="java.util.*,java.lang.*,java.sql.*,HOADIS.*,HOADIS.beans.*" session="true" buffer="8kb" %>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN"
"http://www.w3.org/TR/html4/loose.dtd">
<%
  Subject subject=new Subject();
  request.setAttribute("subject",subject);
%>
<jsp:setProperty name="subject" property="*"></jsp:setProperty>
  <%
     try
     {
      Connection con = Utils.getDBConnection();
      String code=subject.getCode().replace(" ", "").replace("-","");
      PreparedStatement del = con.prepareStatement("delete from subject where code=?");
      del.setString(1,code);
      del.execute();
      PreparedStatement cs = con.prepareStatement("insert into subject (name, code, course, sem, teacher, lastrno) values (?,?,?,?,?,?) ");
      cs.setString(1, subject.getName());
      cs.setString(2, subject.getCode());
      cs.setString(3, subject.getCourse());
      cs.setString(4, subject.getSem());
      cs.setString(5, subject.getTeacher());
      cs.setInt(6, subject.getLastrno());
      cs.execute();
      String course=subject.getCourse().replace(" ", "").replace(".","");
      try
      {
       del=con.prepareStatement("Drop table attend"+ course+code+"_old");
       del.execute();
      }
      catch (SQLException ex)
      {
       //ex.printStackTrace(response.getWriter());
       //May give exception if table does not exist.So the exception can be safely ignored.
      }
      try
      {
       out.println(code+course);
       del=con.prepareStatement("RENAME TABLE " + "attend"+course+code + " TO " + "attend"+course+code+"_old");
       del.execute();
      }
      catch (SQLException ex)
      {
       //ex.printStackTrace(response.getWriter());
       //May give exception if table does not exist.So the exception can be safely ignored.
      }
      int i=0;
      String create="create table "+"attend"+subject.getCourse().replace(".", "")+code.replace("-", "")+" (dat date,";
      for(i=1;i<subject.getLastrno();i++)
       {
        create+="rno"+i+" int(1) , ";
       }
      create+="rno"+i+" int(1) )";
      cs=con.prepareStatement(create);
      cs.execute();
     }
     catch (Exception ex)
     {
      //ex.printStackTrace(response.getWriter());
      Utils.Error(request, response, Utils.DBERRORPAGE);
      return;
     }
     response.sendRedirect("Home");
  %>
