import java.net.*;
import java.io.*;
public class Client
{
    public static void main(String gg[])
    {
        try{
       String request="Hello Siddhant#";
       Socket socket=new Socket("localhost",8521);
       OutputStream os=socket.getOutputStream();
       OutputStreamWriter osw=new OutputStreamWriter(os);
       osw.write(request);
       osw.flush();
            InputStream is=socket.getInputStream();
            InputStreamReader isr=new InputStreamReader(is);
            StringBuffer sb=new StringBuffer();
            char c;
            while(true)
            {
                c=(char)isr.read();
                if(c=='#')break;
                sb.append((c));
            }
            String response=sb.toString();
            System.out.println("Response request arrived");
            System.out.println(response);
            
        
    }catch(Exception e)
    {
        System.out.println(e);
    }
}
}