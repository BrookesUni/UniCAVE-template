import threading
import tkinter as tk

import distutils
import os
from os.path import exists
import socket
import subprocess
import time
from distutils.dir_util import copy_tree

import yaml


class SimpleUI:
    def __init__(self, root):
        self.config_file = "config.yaml"
        self.root = root
        self.root.title("UniCave start")

        self.label1 = tk.Label(self.root, text="ig_shared_folder:")
        self.entry1 = tk.Entry(self.root, width=50)

        self.label2 = tk.Label(self.root, text="build_folder_origin:")
        self.entry2 = tk.Entry(self.root, width=50)

        self.label3 = tk.Label(self.root, text="build_folder_destination:")
        self.entry3 = tk.Entry(self.root, width=50)

        self.toggle4_var = tk.IntVar()
        self.toggle4 = tk.Checkbutton(self.root, text="overwrite_build", variable=self.toggle4_var)

        self.toggle4.grid(row=3, column=0, padx=(10, 0), sticky='w')
        # label4 = tk.Label(self.root, text="overwrite_build:")
        # entry4 = tk.Entry(self.root, width=50)

        # Position labels and input boxes using grid layout
        self.label1.grid(row=0, column=0, padx=(10, 0), pady=(10, 0))
        self.entry1.grid(row=0, column=1, padx=(0, 10), pady=(10, 0))

        self.label2.grid(row=1, column=0, padx=(10, 0))
        self.entry2.grid(row=1, column=1, padx=(0, 10))

        self.label3.grid(row=2, column=0, padx=(10, 0))
        self.entry3.grid(row=2, column=1, padx=(0, 10))

        # label4.grid(row=3, column=0, padx=(10, 0))
        # entry4.grid(row=3, column=1, padx=(0, 10))

        # Create and position buttons
        self.button1 = tk.Button(self.root, text="Start cave", command=self.start_cave)
        self.button2 = tk.Button(self.root, text="save config", command=self.save_config)

        self.button1.grid(row=4, column=0, padx=(10, 0), pady=(10, 10))
        self.button2.grid(row=4, column=1, padx=(0, 10), pady=(10, 10))
        # Load the configuration and populate the input boxes
        self.load_config()

        self.is_cave_starting = False

    def load_config(self):

        if not exists(self.config_file):
            self.create_empty_config()
            return

        with open(self.config_file, 'r') as yf:
            config = yaml.safe_load(yf)

        self.entry1.delete(0, tk.END)
        self.entry1.insert(0, config['ig_shared_folder'])

        self.entry2.delete(0, tk.END)
        self.entry2.insert(0, config['build_folder_origin'])

        self.entry3.delete(0, tk.END)
        self.entry3.insert(0, config['build_folder_destination'])

        self.toggle4_var.set(config['overwrite_build'])

    def show_popup(self, pop_up_message):
        popup = tk.Toplevel(self.root)
        popup.title("Pop-up Window")

        label = tk.Label(popup, text=pop_up_message)
        label.pack(pady=(10, 0))

        close_button = tk.Button(popup, text="Close", command=popup.destroy)
        close_button.pack(pady=(0, 10))

    def start_cave(self):
        cave_thread = threading.Thread(target=self.start_cave_thread)
        cave_thread.start()

    def start_cave_thread(self):
        if self.is_cave_starting:
            self.show_popup("UniCAVE already starting")
            self.is_cave_starting = False
            return

        print("starting cave")

        if not exists(self.config_file):
            self.create_empty_config()
            self.show_popup("config.yaml file does not exist! An empty file has been created.")
            self.is_cave_starting = False
            return

        # load config
        with open(self.config_file, 'r') as yf:
            config = yaml.safe_load(yf)

        self.show_popup("CAVE starting...")

        # overwrite a build folder
        if config["overwrite_build"]:
            result = self.copy_build_folder(config["build_folder_origin"], config["build_folder_destination"])
            if not result:
                self.show_popup("ERROR: make sure the UniCAVE is not running!")
                self.is_cave_starting = False
                return

        # start a host application
        self.start_host(config["build_folder_destination"])
        delay = 25
        print(f"Waiting {delay}s until starting the IGs")
        time.sleep(20)

        # send a signal to start ig's
        try:
            self.start_igs(config["ig_shared_folder"], config["build_folder_destination"])
        except TimeoutError:
            self.show_popup("Cannot establish connection with IG!")
            self.is_cave_starting = False

    def save_config(self):
        print("saving config")
        config = {
            'ig_shared_folder': self.entry1.get(),
            'build_folder_origin': self.entry2.get(),
            'build_folder_destination': self.entry3.get(),
            'overwrite_build': self.toggle4_var.get()
        }

        with open(self.config_file, 'w') as yf:
            yaml.dump(config, yf)
        self.show_popup("Configuration saved to config.yaml")

    def create_empty_config(self):
        with open(self.config_file, 'w') as yf:
            pass

    def start_ig(self, executable_location, ip_address, machine_name, eye, full_screen):
        """
        Send a payload to IG to start an executable
        :param executable_location: where the application is located in shared drive
        :param ip_address: ip address of IG
        :param machine_name: eg FRONT2 needs to run as FRONT1
        :param eye: left or right eye
        :param full_screen: should it run in full screen
        """
        print(f"Starting {ip_address}...")
        s = socket.create_connection((ip_address, 6000))
        args = f"{executable_location} overrideMachineName {machine_name} eye {eye} full_screen {full_screen}"
        com_bytes = args.encode("utf_16_be")
        len_bit = len(com_bytes).to_bytes(4, byteorder="big")
        payload = len_bit + com_bytes
        s.send(payload)
        s.close()

    # Starts an executable for Host
    def start_host(self, build_folder_destination):
        print("Starting host...")

        # create the path for executable
        exe_path = build_folder_destination + "/" + self.get_executable_path(build_folder_destination)
        args = [exe_path]

        # open a host process
        subprocess.Popen(args)
        print("Host running...")

    # copies a build folder from origin to destination folder
    def copy_build_folder(self, build_folder_origin, build_folder_destination) -> bool:
        # copy the build folder
        print("Copying new build folder to shared drive...")
        try:
            copy_tree(build_folder_origin, build_folder_destination)
        except distutils.errors.DistutilsFileError:
            return False
        print("Finished copying Build folder...")
        return True

    def get_executable_path(self, build_folder):
        # get the executable file from the build folder
        try:
            exe_name = [file for file in os.listdir(build_folder) if ".exe" in file][0]
            return exe_name
        except IndexError:
            input("Executable not found in Build folder!")
            exit(-1)

    def check_build_folders(self, overwrite_build, build_folder_origin, build_folder_destination):
        # check if build folder origin exists if we want to overwrite it
        if overwrite_build and not exists(build_folder_origin):
            input("Build Folder Origin does not exists!")
            exit(-1)

        # check if build folder destination exists
        if not exists(build_folder_destination):
            input("Build Folder Destination does not exists!")
            exit(-1)

    # sends a signal to each ig to start application
    def start_igs(self, ig_shared_folder, build_folder_destination):
        ig_executable_path = ig_shared_folder + self.get_executable_path(build_folder_destination)
        # LEFT1
        self.start_ig(executable_location=ig_executable_path,
                      ip_address="192.168.1.2",
                      machine_name="LEFT1",
                      eye="left",
                      full_screen=1)
        # LEFT2
        self.start_ig(executable_location=ig_executable_path,
                      ip_address="192.168.1.3",
                      machine_name="LEFT1",
                      eye="right",
                      full_screen=1)
        # FRONT1
        self.start_ig(executable_location=ig_executable_path,
                      ip_address="192.168.1.4",
                      machine_name="FRONT1",
                      eye="left",
                      full_screen=1)
        # FRONT2
        self.start_ig(executable_location=ig_executable_path,
                      ip_address="192.168.1.5",
                      machine_name="FRONT1",
                      eye="right",
                      full_screen=1)
        # RIGHT1
        self.start_ig(executable_location=ig_executable_path,
                      ip_address="192.168.1.6",
                      machine_name="RIGHT1",
                      eye="left",
                      full_screen=1)
        # RIGHT2
        self.start_ig(executable_location=ig_executable_path,
                      ip_address="192.168.1.7",
                      machine_name="RIGHT1",
                      eye="right",
                      full_screen=1)


if __name__ == "__main__":
    root = tk.Tk()
    app = SimpleUI(root)
    root.mainloop()
