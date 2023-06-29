import socket
import os
import time
import subprocess
import yaml
import pathlib

print()


def main():
    # get host name, needed to get right config
    # host_name = socket.gethostname()
    host_name = "FRONT1"
    with open("config.yaml", 'r') as yf:
        config = yaml.safe_load(yf)

    path = config["build-path"]

    config = config[host_name]
    # create args for exe
    args = [path]

    # popup window
    # args = args + ["-popupWindow"]

    # get the machine name
    args = args + ["overrideMachineName", config[0]]

    # get the eye
    args = args + ["eye", config[1]]

    # full screen
    args = args + ["-screen-fullscreen", "1"]

    print(args)
    while True:
        time.sleep(1)
        file = pathlib.Path(f"/{host_name}.txt")

        # file is found, run the Unity exe
        if file.is_file():
            os.remove(f"/{host_name}.txt")

            # start process
            subprocess.Popen(args)


if __name__ == "__main__":
    main()
