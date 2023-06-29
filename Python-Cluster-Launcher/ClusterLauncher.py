import os
import sys
import time
import subprocess
import yaml
import pathlib


class ClusterLauncher:
    def __init__(self, config_yaml):
        self.Config = config_yaml

    def launch(self):
        # read config
        with open(self.Config, 'r') as yf:
            config = yaml.safe_load(yf)

            # launch head node
            print("starting head")
            head = ClusterLauncher.launch_uni_cave_window(path=config["build-path"],
                                                          machine_name=config["head-node"],
                                                          server_address=config["serverAddress"],
                                                          popup_window=config["popupWindow"],
                                                          server_port=config["serverPort"])

            # wait a bit before launching child nodes
            if config["head-wait"] is not None:
                time.sleep(config["head-wait"])

            time.sleep(10)
            # launch child nodes
            children = []
            for child_node in config["child-nodes"]:
                print(f"starting {child_node}")
                children.append(ClusterLauncher.launch_uni_cave_window(path=config["build-path"],
                                                                       machine_name=child_node[0],
                                                                       eye=child_node[1],
                                                                       server_address=config["serverAddress"],
                                                                       popup_window=config["popupWindow"],
                                                                       server_port=config["serverPort"]))
                # wait a bit between launching each child
                if config["child-wait"] is not None:
                    time.sleep(config["child-wait"])

            # poll head node process
            done = False
            while not done:
                if head.poll() is not None:
                    done = True
                time.sleep(config["sleep-time"])

            # when done, close child processes and exit
            for child in children:
                child.kill()

    @staticmethod
    def launch_uni_cave_window(path, popup_window, machine_name=None, eye=None, server_address=None, server_port=None):
        args = [path]

        if popup_window == 1:
            args = args + "-popupWindow"

        if machine_name is not None:
            args = args + ["overrideMachineName", machine_name]

        if eye is not None:
            args = args + ["eye", eye]

        if server_address is not None:
            args = args + ["serverAddress", server_address]

        if server_port is not None:
            args = args + ["serverPort", server_port]

        args = args + ["-screen-fullscreen", "0"]

        print(args)

        return subprocess.Popen(args)


if __name__ == "__main__":
    ClusterLauncher(os.path.join(pathlib.Path(__file__).parent.absolute(), "config.yaml")).launch()
