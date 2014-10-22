using System;
using System.Collections;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using System.Net.Sockets;
using System.Net;
using System.Collections.Generic;

namespace GUI {
  class SocketGUI {

    /********************************SOCKET COMMUNICATION********************************/
    private Thread listenThread;
    volatile private Thread clientThread;

    volatile private NetworkStream clientStream;
    
    volatile private TcpClient tcpClient;
    volatile private TcpListener tcpListener;
    volatile private TcpClient client;
    
    volatile private Boolean isAbortThreadRequest = false;
    /********************************SOCKET COMMUNICATION********************************/
    volatile public bool connected = false;
    public String socketStringReceiver;
    volatile public bool dataReceived = false;

    public SocketGUI() {
      this.tcpListener = new TcpListener(IPAddress.Any, 6000);
      this.listenThread = new Thread(new ThreadStart(ListenForClients));
      this.listenThread.Start();    
    }
    
    private void HandleClientComm(object client) {
      tcpClient = (TcpClient)client;
      this.clientStream = tcpClient.GetStream();
      byte[] message = new byte[4096];
      int bytesRead;
      while (true) {
        if (isAbortThreadRequest) {
          tcpClient.Close();
          this.clientStream.Close();
          break;
        }
        bytesRead = 0;
        try {
          //blocks until a client sends a message
          bytesRead = clientStream.Read(message, 0, 4096);
        } catch {
          //a socket error has occured
          break;
        }
        if (bytesRead == 0) {
          //the client has disconnected from the server
          break;
        }
        //message has successfully been received
        ASCIIEncoding encoder = new ASCIIEncoding();
        //System.Console.WriteLine(encoder.GetString(message, 0, bytesRead));
        try {
          dataReceived = true;
          socketStringReceiver = encoder.GetString(message, 0, bytesRead);
          System.Console.WriteLine(socketStringReceiver);
        } catch (Exception e) {System.Console.WriteLine("Socket:" + e.Message);}
      }
      tcpClient.Close();
    }

    private void ListenForClients() {
      this.tcpListener.Start();
      //System.Console.WriteLine("tcplistener started");
      while (true) {
        client = this.tcpListener.AcceptTcpClient();         //blocks until a client has connected to the server
        System.Console.WriteLine("tcplistener connected");
        connected = true;
     
        clientThread = new Thread(new ParameterizedThreadStart(HandleClientComm));         //with connected client create a thread to handle communication 
        clientThread.Start(client);
        if (isAbortThreadRequest) {
          this.tcpListener.Stop();
          clientThread.Abort();
          client.Close();
          break;
        }
      }
    }

    public void sendStringSocket(string str) {
      if (this.clientStream == null) return;
      try {
        if (listenThread.IsAlive) {
          byte[] msgBuffer = Encoding.ASCII.GetBytes(str);
          this.clientStream.Write(msgBuffer, 0, msgBuffer.Length);
        }
      } catch (Exception e) {System.Console.WriteLine("sendStringSocket:" + e.Message);}
    }

    public void stopSocket() {
      if (tcpListener != null && clientStream != null) {
        this.clientStream.Close();
        this.tcpClient.Close();
        this.clientThread.Abort();
        this.client.Close();
        this.tcpListener.Stop();
        this.listenThread.Abort();
        this.tcpListener = null;
      }
    }
  }
}
