import java.net.*;
import java.io.*;
public class Server

{
    public static void main(String gg[])
    {
        try{

        ServerSocket serverSocket;
        serverSocket=new ServerSocket(8521);
        while(true)
        {
        System.out.println("Server is ready to listen on port number 8521");
            Socket socket=serverSocket.accept();
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
            String request=sb.toString();
            System.out.println("Following request arrived");
            System.out.println(request);
            String response="Got it #";
            OutputStream os=socket.getOutputStream();
            OutputStreamWriter osw=new OutputStreamWriter(os);
            osw.write(response);
            osw.flush();
        System.out.println("Socket closed");
        socket.close();
        }
    }catch(Exception e)
    {
        System.out.println(e);
    }
    }
}