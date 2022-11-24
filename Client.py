import socket
import threading
import tkinter 
import tkinter.scrolledtext
from tkinter import simpledialog


HOST = "127.0.0.1"
PORT = 9090

class Client:
    def __init__(self, host, port):

        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.connect((host, port))


        msg = tkinter.Tk()
        msg.withdraw()

        self.nickname = simpledialog.askstring("Nickname", "Please choose a nickname", parent=msg)



        self.gui_done = False
        self.running = True

        gui_thread = threading.Thread(target=self.gui_loop)
        recieve_thread = threading.Thread(target=self.recieve_loop)


        gui_thread.start()
        recieve_thread.start()

    def gui_loop(self):
        self.win =  tkinter.Tk()
        self.win.configure(bg="purple")
        self.chat_lbl = tkinter.Label(self.win, text="Chat Room", bg="purple")


        self.text_area = tkinter.scrolledtext.ScrolledText(self.win)
        self.text_area.pack(padx=20, pady=5)
        self.text_area.config(state='disabled')

        self.msg_lbl = tkinter.Label(self.win, text="Message", bg="black", fg="#00FF00")
        self.msg_lbl.pack(padx=20, pady=5)

        self.input_section = tkinter.Text(self.win, height=5)
        self.input_section.pack(padx=20, pady=5)


        self.send_btn = tkinter.Button(self.win, text="send", bg="black", fg="#00FF00", command=self.write)
        self.send_btn.pack(padx=20, pady=5)


        self.gui_done = True

        self.win.protocol("WM_DELETE_WINDOW", self.stop)


        self.win.mainloop()
    
    def write(self):
        message = f"{self.nickname}: {self.input_section.get('1.0', 'end')}"
        self.sock.send(message.encode('utf-8'))

    def stop(self):
        self.run = False
        self.win.destroy()
        self.sock.close()
        exit(0)

    def recieve(self):
        while self.running:
            try:
                message = self.sock.recv(1024).decode('utf-8')
                if message == 'NICK':
                    self.sock.send(self.nickname.encode('utf-8'))
                else:
                    if self.gui_done:
                        self.text_area.config(state='normal')
                        self.text_area.insert('end', message)
                        self.text_area.yview('end')
                        self.text_area.config(state='disabled')
            except ConnectionAbortedError:
                break


client = Client(HOST, PORT)







