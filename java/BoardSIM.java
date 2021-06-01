import java.net.*;
import java.io.*;
import java.util.*;

/*
we will accept command line argument as
*/
public class BoardSIM {
    public static void main(String gg[]) {
        if (gg.length < 2) {
            System.out.println("You need to pass board id and list of electronic unit");
            return;
        }

        try {
            String request = "BR";
            int i;
            char x;
            for (i = 0; i < gg.length; i++) {
                request = request + "," + gg[i];
            }
            request = request + "#";
            Socket socket = new Socket("localhost", 7892);
            InputStream inputStream;
            InputStreamReader inputStreamReader;
            OutputStream outputStream;
            OutputStreamWriter outputStreamWriter;
            StringBuffer stringBuffer;
            String response;
            outputStream = socket.getOutputStream();
            outputStreamWriter = new OutputStreamWriter(outputStream);
            outputStreamWriter.write(request);
            outputStreamWriter.flush();
            inputStream = socket.getInputStream();
            inputStreamReader = new InputStreamReader(inputStream);
            stringBuffer = new StringBuffer();
            while (true) {
                x = (char) inputStreamReader.read();
                if (x == '#') {
                    break;
                }
                stringBuffer.append(x);
            }
            response = stringBuffer.toString();
            socket.close();
            while (true) {
                try {
                    Thread.sleep(5000);
                    socket = new Socket("localhost", 7892);
                    request = "BC," + gg[0] + "#";
                    outputStream = socket.getOutputStream();
                    outputStreamWriter = new OutputStreamWriter(outputStream);
                    outputStreamWriter.write(request);
                    outputStreamWriter.flush();
                    inputStream = socket.getInputStream();
                    inputStreamReader = new InputStreamReader(inputStream);
                    stringBuffer = new StringBuffer();
                    while (true) {
                        x = (char) inputStreamReader.read();
                        if (x == '#') {
                            break;
                        }
                        stringBuffer.append(x);
                    }
                    response = stringBuffer.toString();
                    
                    if (response.length() == 0) {
                        System.out.println("No Commands for now");
                    }
                    else
                    {
                        System.out.println(response);
                    }
                    // System.out.println(response);

                    socket.close();

                } catch (Exception ie) {
                    System.out.println(ie);
                }
            }

        } catch (Exception e) {
            System.out.println(e);
        }
    }
}
