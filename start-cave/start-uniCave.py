import distutils
import os
from os.path import exists
import socket
import subprocess
import time
from distutils.dir_util import copy_tree

import yaml


def start_ig(executable_location, ip_address, machine_name, eye, full_screen):
    """
    Send a payload to IG to start an executable
    :param executable_location: where the application is located in shared drive
    :param ip_address: ip address of IG
    :param machine_name:
    :param eye:
    :param full_screen:
    :return:
    """
    print(f"Starting {machine_name}...")
    s = socket.create_connection((ip_address, 6000))
    args = f"{executable_location} overrideMachineName {machine_name} eye {eye} full_screen {full_screen}"
    com_bytes = args.encode("utf_16_be")
    len_bit = len(com_bytes).to_bytes(4, byteorder="big")
    payload = len_bit + com_bytes
    s.send(payload)
    s.close()


# Starts an executable for Host
def start_host():
    print("Starting host...")

    # create the path for executable
    exe_path = config["build_folder_destination"] + "/" + get_ig_executable_path(config["build_folder_destination"])
    args = [exe_path]

    # open a host process
    subprocess.Popen(args)
    time.sleep(3)
    print("Host running...")


# copies a build folder from origin to destination folder
def copy_build_folder():
    # copy the build folder
    print("Copying new build folder to shared drive...")
    try:
        copy_tree(config["build_folder_origin"], config["build_folder_destination"])
    except distutils.errors.DistutilsFileError:
        input("ERROR: make sure the UniCAVE is not running!")
        exit(-1)
    print("Finished copying Build folder...")


def get_ig_executable_path(build_folder):
    # get the executable file from the build folder
    try:
        exe_name = [file for file in os.listdir(build_folder) if ".exe" in file][0]
        return exe_name
    except IndexError:
        input("Executable not found in Build folder!")
        exit(-1)


def check_build_folders():
    # check if build folder origin exists if we want to overwrite it
    if config["overwrite_build"] and not exists(config["build_folder_origin"]):
        input("Build Folder Origin does not exists!")
        exit(-1)

    # check if build folder destination exists
    if not exists(config["build_folder_destination"]):
        input("Build Folder Destination does not exists!")
        exit(-1)


# sends a signal to each ig to start application
def start_igs():
    ig_executable_path = config["ig_shared_folder"] + get_ig_executable_path(config["build_folder_destination"])
    # LEFT1
    start_ig(executable_location=ig_executable_path,
             ip_address="192.168.1.2",
             machine_name="LEFT1",
             eye="left",
             full_screen=1)
    # LEFT2
    start_ig(executable_location=ig_executable_path,
             ip_address="192.168.1.3",
             machine_name="LEFT1",
             eye="right",
             full_screen=1)
    # FRONT1
    start_ig(executable_location=ig_executable_path,
             ip_address="192.168.1.4",
             machine_name="FRONT1",
             eye="left",
             full_screen=1)
    # FRONT2
    start_ig(executable_location=ig_executable_path,
             ip_address="192.168.1.5",
             machine_name="FRONT1",
             eye="right",
             full_screen=1)
    # RIGHT1
    start_ig(executable_location=ig_executable_path,
             ip_address="192.168.1.6",
             machine_name="RIGHT1",
             eye="left",
             full_screen=1)
    # RIGHT2
    start_ig(executable_location=ig_executable_path,
             ip_address="192.168.1.7",
             machine_name="RIGHT1",
             eye="right",
             full_screen=1)


if __name__ == "__main__":
    # check if config file exists
    config_file = "config.yaml"
    if not exists(config_file):
        input("config.yaml file does not exists!")
        exit(-1)

    # load config
    with open(config_file, 'r') as yf:
        config = yaml.safe_load(yf)

    # check if build folder exists
    check_build_folders()

    # overwrite a build folder
    if config["overwrite_build"]:
        copy_build_folder()

    # start a host application
    start_host()
    delay = 20
    print(f"Waiting {delay}s until starting the IGs")
    time.sleep(delay)

    # send a signal to start ig's
    try:
        start_igs()
    except TimeoutError:
        input("Cannot establish connection with IG!")
