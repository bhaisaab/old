package HOADIS.Profile;

import HOADIS.Upload.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.*;
import java.io.*;
import java.util.*;

import HOADIS.*;
import HOADIS.beans.*;

public class SavePhoto extends HttpServlet
{

 @Override
 protected void doGet(HttpServletRequest request, HttpServletResponse response)
 throws ServletException, IOException
 {
  Utils.unauthorised(request, response);
 }

 @Override
 protected void doPost(HttpServletRequest request, HttpServletResponse response)
 throws ServletException, IOException
 {

  //Get userData bean
  session = request.getSession();
  User userData = (User) session.getAttribute("userData");
  if (userData == null)
  {
   Utils.unauthorised(request, response);
  }
  
  PrintWriter out  = response.getWriter();
  out.println("Path: ");
  
  ServletInputStream sis = request.getInputStream();
  StringWriter sw = new StringWriter();
  
  int i = sis.read();
  for(; i!=-1 && i!='\r'; i=sis.read())
  {
    sw.write(i);
  }
  sis.read();
  
  String delimiter = sw.toString();
  
  int count = 0;
  while(true)
  {
    StringWriter h = new StringWriter();
    int[] temp = new int[4];
    
    temp[0] = (byte)sis.read();
    temp[1] = (byte)sis.read();
    temp[2] = (byte)sis.read();
    
    h.write(temp[0]);
    h.write(temp[1]);
    h.write(temp[2]);
    //read header
    
    for(temp[3]=sis.read(); temp[3]!=-1; temp[3]=sis.read()){
        if(temp[0] == '\r' &&
           temp[1] == '\n' &&
           temp[2] == '\r' &&
           temp[3] == '\n' ){
            break;
        }
    
        h.write(temp[3]);
        temp[0] = temp[1];
        temp[1] = temp[2];
        temp[2] = temp[3];
    }
    String header = h.toString();
    
    int startName = header.indexOf("name=\"");
    int endName = header.indexOf("\"", startName+6);
    if(startName == -1 || endName == -1){
        break;
    }
    
    String name = header.substring(startName+6, endName);
    if(name.equals("file")){
        startName = header.indexOf("filename=\"");
        endName = header.indexOf("\"", startName+10);
        String filename = header.substring(startName+10, endName);
        
        
          ServletContext sc = request.getSession().getServletContext();
  File file = new File(sc.getRealPath("/avatars"));
  
  file.mkdirs();
  FileOutputStream fos = new FileOutputStream(
          sc.getRealPath("/avatars")+"/"+userData.getUser());
  
  
    //write disk io

  int length = 0;
  delimiter = "\r\n" + delimiter;
          
  byte[] body = new byte[delimiter.length()];
  
  for( int j=0; j < body.length; j++)
  {
    body[j] = (byte)sis.read();
  }
  
  if(!delimiter.equals(new String(body))){
      int e = body.length - 1;
      i = sis.read();
      for(; i!=-1;i=sis.read()){
          fos.write(body[0]);
                for(int l=0; l<body.length-1;l++){
          body[l] = body[l+1];
      }
      body[e] = (byte)i;
      
      if(delimiter.equals(new String(body))){
          break;
      }
      length++;
      }

  }
  
  fos.flush();
  fos.close();
 
    }
    if(sis.read() == '-' && sis.read() == '-'){
        break;
    }
  
  }

  response.sendRedirect(destination);
  return;
 }

 @Override
 public String getServletInfo()
 {
  return "HOADIS Form Processing Servlet";
 }
 private HttpSession session;
 private String destination = "EditProfile";
}
