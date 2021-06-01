import java.io.*;
import java.net.*;
import java.util.*;

import javax.swing.text.Style;

class IOTControler {
    public static void main(String gg[]) {
        try {

            InputStream inputStream;
            InputStreamReader inputStreamReader;
            OutputStream outputStream;
            OutputStreamWriter outputStreamWriter;
            String command;
            String request;
            String device;
            String board;
            String response,str;
            String splits1[];
            String splits2[];
            Socket socket;
            char x;
            int i, j;
            StringBuffer stringBuffer;
            InputStreamReader keyboardInputStreamReader;
            keyboardInputStreamReader = new InputStreamReader(System.in);

            BufferedReader bufferedReader;
            bufferedReader = new BufferedReader(keyboardInputStreamReader);
            while (true) {
                System.out.println("iot controller>");
                command = bufferedReader.readLine();
                command=command.trim();
                while(command.indexOf("  ")!=-1)command=command.replaceAll("  ", " ");
                if (command.equalsIgnoreCase("QUIT"))
                    break;
                else if (command.equals("help")) {
                    System.out.println("ls:to get list of connected devices");
                    System.out.println("Turn on Electronic Device connected to Device ID.");
                    System.out.println("quit: to exit from the controller software");
                } else if (command.equals("ls")) {
                    request = "CC,ls#";
                    socket = new Socket("localhost", 7892);
                    outputStream = socket.getOutputStream();
                    outputStreamWriter = new OutputStreamWriter(outputStream);
                    outputStreamWriter.write(request);
                    outputStreamWriter.flush();
                    inputStream = socket.getInputStream();
                    inputStreamReader = new InputStreamReader(inputStream);
                    stringBuffer = new StringBuffer();
                    while (true) {
                        x = (char) inputStream.read();
                        if (x == '#')
                            break;
                        stringBuffer.append(x);
                    }
                   
                    response = stringBuffer.toString();
                   
                    socket.close();
                    if(response==null || response.length()==0)
                    {
                        System.out.println("No Board  connected to server ");
                        break;
                    }
                    splits1 = response.split("!");
                    for (i = 0; i < splits1.length; i++) {
                        splits2 = splits1[i].split(",");
                        System.out.println("---------------------------------------");
                        System.out.println("Board:" + splits2[0]);
                        System.out.println("---------------------------------------");
                        for (j = 1; j < splits2.length; j++) {
                            System.out.println(j + ") " + splits2[j]);
                        }
                        System.out.println();
                    }
                    System.out.println();

                    continue;
                    
                }
                str=command.toUpperCase();
                if(str.startsWith(("TURN ON"))||str.startsWith(("TURN OFF")))
                {
                    i=str.indexOf(" CONNECTED TO ");
                    if(i!=-1)
                    {
                    j=str.startsWith("TURN ON")?8:9;
                    device=command.substring(j,i);
                    board=command.substring(i+14);
                    request="CC,CMD,"+board+","+device+"";
                    if(j==8)request=request+",1#";
                    if(j==9)request=request+",0#";
                    socket=new Socket("localhost",7892);
                    outputStream=socket.getOutputStream();
                    outputStreamWriter=new OutputStreamWriter(outputStream);
                    outputStreamWriter.write(request);
                    outputStreamWriter.flush();
                    inputStream=socket.getInputStream();
                    inputStreamReader=new InputStreamReader(inputStream);
                    stringBuffer=new StringBuffer();
                    while(true)
                    {
                        x=(char)inputStreamReader.read();
                        if(x=='#')break;
                        stringBuffer.append(x);
                    }
                    response=stringBuffer.toString();
                    if(response.equals("0"))
                    {
                        System.out.println("Invalid board name:"+board+",Invalid device name:"+device+"");

                    }
                    else if(response.equals("1"))
                    {
                        System.out.println("Invalid board name:"+board+"");

                    }
                    else if(response.equals("2"))
                    {
                        System.out.println("Invalid device name:"+device+"");

                    }
                    if(response.equals("3"))
                    {
                        System.out.println("Request Accepted");
                    }
                    continue;
                    }

                    


                }




                    System.out.println("Invalid command, type help to get list of commands");
                

            }
            System.out.println(("Thank you for using command center"));

        } catch (Exception e) {
            System.out.println(e);
        }
    }

}
