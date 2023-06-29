import subprocess

import yaml


def main():
    open("FRONT1.txt", "x")
    open("FRONT2.txt", "x")
    open("LEFT1.txt", "x")
    open("LEFT2.txt", "x")
    open("RIGHT1.txt", "x")
    open("RIGHT2.txt", "x")

    with open("config.yaml", 'r') as yf:
        config = yaml.safe_load(yf)

    path = config["build-path"]

    args = [path]

    subprocess.Popen(args)


if __name__ == '__main__':
    main()
