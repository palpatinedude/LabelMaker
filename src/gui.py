import tkinter as tk
from tkinter import messagebox
import serial
import time

class Selector:
    def __init__(self, master):
        self.master = master
        master.title("symbol selector")

        # available symbols
        self.letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        # self.digits = "0123456789"
        # self.symbols = "!@#$%^&*()_+=-[]\\{}|:\"';,./?><"
        
        #  label for instructions
        self.label = tk.Label(master, text="select a symbol from the columns:")
        self.label.pack(pady=10)

        #  frame to hold the listboxes
        self.frame = tk.Frame(master)
        self.frame.pack(pady=20)

        # listbox for letters
        self.letter_listbox = self.create_listbox(self.letters, "Letters")
        # self.digit_listbox = self.create_listbox(self.digits, "Digits")
        # self.symbol_listbox = self.create_listbox(self.symbols, "Special symbols")

        #  button to confirm selection
        self.select_button = tk.Button(master, text="select Symbol", command=self.select_symbol)
        self.select_button.pack(pady=10)

        #  button to exit the application
        self.exit_button = tk.Button(master, text="exit", command=self.exit)
        self.exit_button.pack(pady=5)

        try:
            self.serial_port = serial.Serial(port='/dev/ttyUSB0', baudrate=9600, timeout=1)  #
            time.sleep(2)  
        except serial.SerialException as e:
            messagebox.showerror("error", f"failed to open serial port: {e}")
            self.serial_port = None

    def create_listbox(self, symbols, title):
        # frame for each listbox
        listbox_frame = tk.Frame(self.frame)
        listbox_frame.pack(side=tk.LEFT, padx=10)

        # label for the listbox
        label = tk.Label(listbox_frame, text=title)
        label.pack()

        listbox = tk.Listbox(listbox_frame, selectmode=tk.SINGLE, width=10, height=15)
        listbox.pack()

        # add the symbols
        for symbol in symbols:
            listbox.insert(tk.END, symbol)

        return listbox

    def select_symbol(self):
        # get the selected symbol from the letter listbox
        selected_symbols = []
        
        # check the letter listbox for a selected symbol
        try:
            selected_index = self.letter_listbox.curselection()[0]
            selected_symbol = self.letter_listbox.get(selected_index)
            selected_symbols.append(selected_symbol)
        except IndexError:
            pass  # ignore 

        if selected_symbols:
            messagebox.showinfo("selected symbol", f"you selected: {', '.join(selected_symbols)}")
            # send the selected symbol to the controller
            self.serial_port.write((selected_symbols[0] + '\n').encode())
        else:
            messagebox.showwarning("Warning", "select a symbol from the list.")

    def exit(self):
        # send 'off' to turn off the system
        if self.serial_port:
            self.serial_port.write(b'off\n')
            time.sleep(1)  
            self.serial_port.close()
        self.master.quit()

if __name__ == "__main__":
    root = tk.Tk()
    app = Selector(root)
    root.mainloop()
