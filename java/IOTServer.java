import java.net.*;
import java.util.*;

import java.io.*;

/*
Board is registering : BR, Blue Fan, Cooler, AC #
Board is asking for commands : BC, Blur #
Command Center is asking for list cc,ls
Command Center is issuing a command CC, CMD , Turn on the Fan connected to Blur
                                    CC,CMD,JOKER,TABLET PC,1
                                        Response
                                        0 if board name is incorrect then Both board and device name are incorrect
                                        1 board name is incorrect
                                        2. device name is incorrect
                                        3. all is done command accepted
*/
class Board {
    public String id;
    public List<String> electronicUnits;
}

class IOTServer {
    private List<Board> boards;
    private ServerSocket serverSocket;
    public HashMap<String, LinkedList<String>> commands;

    IOTServer() {
        boards = new LinkedList<>();
        commands = new HashMap<>();
    }

    public void start() {
        try {
            serverSocket = new ServerSocket(7892);
            InputStreamReader inputStreamReader;
            InputStream inputStream;
            OutputStream outputStream;
            OutputStreamWriter outputStreamWriter;
            String response, request;
            StringBuffer stringBuffer;
            char x;
            int i, j;
            Socket socket;
            String splits[];
            String origin;
            String command;
            String boardName;
            String deviceName;
            String boardID;
            String electronicUnit;
            LinkedList<String> electronicUnits;
            LinkedList<String> commandsList;
            Board board;
            boolean boardNameFound;
            boolean deviceNameFound;

            while (true) {
                System.out.println("Server is ready to Listen on port 7892");
                socket = serverSocket.accept();

                inputStream = socket.getInputStream();
                inputStreamReader = new InputStreamReader(inputStream);

                stringBuffer = new StringBuffer();
                while (true) {

                    x = (char) inputStreamReader.read();
                    if (x == '#')
                        break;
                    stringBuffer.append((x));
                }
                request = stringBuffer.toString();
                splits = request.split(",");
                origin = splits[0];
                if (origin.equals("BR")) // board is registering
                {
                    System.out.println("Command Receive:"+request);
                    i = 2;
                    boardID = splits[1];
                    electronicUnits = new LinkedList<>();
                    while (i < splits.length) {
                        electronicUnit = splits[i];
                        electronicUnits.add(electronicUnit);
                        i++;
                    }
                    board = new Board();
                    board.id = boardID;
                    board.electronicUnits = electronicUnits;
                    boards.add(board);
                    response = "Got It#";
                    System.out.println("Response Sent:"+response);

                    outputStream = socket.getOutputStream();
                    outputStreamWriter = new OutputStreamWriter(outputStream);
                    outputStreamWriter.write(response);
                    outputStreamWriter.flush();
                    socket.close();

                }
               else if (origin.equals("BC")) // board is asking for commands
                {
                    System.out.println(request);
                    boardName = splits[1];
                    response = "";

                    if (commands.containsKey(boardName)) {
                        commandsList = commands.get(boardName);

                        if (commandsList.size() > 0) {
                            for (String cmd : commandsList) {
                                if (response.length() > 0)
                                    response += ":";
                                response = response + cmd;
                            }
                            commandsList.clear();
                        }
                    }

                    response += "#";
                    System.out.println(response);
                    outputStream = socket.getOutputStream();
                    outputStreamWriter = new OutputStreamWriter(outputStream);
                    outputStreamWriter.write(response);
                    outputStreamWriter.flush();
                    socket.close();
                  //  continue;
                } else if (origin.equals("CC")) // Something arrived from Command Center
                {
                    if (splits[1].equals("CMD")) {
                        boardName = splits[2];
                        deviceName = splits[3];
                        boardNameFound = false;
                        deviceNameFound = false;

                        for (i = 0; i < boards.size(); i++) {
                            board = boards.get(i);
                            if (board.id.equals(boardName)) {
                                boardNameFound = true;
                                for (j = 0; j < board.electronicUnits.size(); j++) {
                                    if (deviceName.equals(board.electronicUnits.get(j))) {
                                        deviceNameFound = true;
                                        break;
                                    }
                                }
                                break;
                            }
                        }
                        if (boardNameFound == false) {
                            response = "0#";

                        }
                        else if(deviceName.toUpperCase().equals("ALL"))
                        {
                            commandsList = commands.get(boardName);
                            if (commandsList == null) {
                                commandsList = new LinkedList<>();
                                commands.put(boardName, commandsList);
                            }
                            for (i = 0; i < boards.size(); i++) {
                                board = boards.get(i);
                                if (board.id.equals(boardName)) {
                                    boardNameFound = true;
                                    for (j = 0; j < board.electronicUnits.size(); j++) {
                                        commandsList.add(board.electronicUnits.get(j)+","+splits[4]);
                                    }
                                    break;
                                }
                            } 
                            response = "3#";

                        }
                        else if (deviceNameFound == false) {
                            response = "2#";

                        }
                        else {
                            command = splits[3] + "," + splits[4];
                            commandsList = commands.get(boardName);
                            if (commandsList == null) {
                                commandsList = new LinkedList<>();
                                commands.put(boardName, commandsList);
                            }
                            commandsList.add(command);
                            response = "3#";

                        }
                        outputStream = socket.getOutputStream();
                        outputStreamWriter = new OutputStreamWriter(outputStream);
                        outputStreamWriter.write(response);
                        outputStreamWriter.flush();
                        socket.close();
                    }
                    command = splits[1];
                    if (command.equals("ls")) {
                        response = "";
                        i = 0;
                        for (Board b : boards) {

                            response = response + b.id;

                            for (String eu : b.electronicUnits) {
                                response = response + "," + eu;

                            }
                            if (i < boards.size() - 1)
                                response = response + "!";
                            i++;
                        }
                        response = response + "#";
                        outputStream = socket.getOutputStream();
                        outputStreamWriter = new OutputStreamWriter(outputStream);
                        outputStreamWriter.write(response);
                        outputStreamWriter.flush();
                        socket.close();

                    }
                }
                else
                {
                    outputStream = socket.getOutputStream();
                    outputStreamWriter = new OutputStreamWriter(outputStream);
                    outputStreamWriter.write("WRONG COMMAND#");
                    outputStreamWriter.flush();
                    socket.close();
                }

            }

        } catch (Exception e) {
            System.out.println(e);
        }
    }

    public static void main(String gg[]) {
        IOTServer iotServer = new IOTServer();
        iotServer.start();
    }
}





