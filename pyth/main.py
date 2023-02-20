# This is a sample Python script.
#!/usr/bin/env python
# Press Shift+F10 to execute it or replace it with your code.
# Press Double Shift to search everywhere for classes, files, tool windows, actions, and settings.

import asyncio
import websockets
import json
import socket
import socketserver

async def hello():
    async with websockets.connect("wss://localhost:6868") as websocket:
        await websocket.send("Hei")
        await websocket.recv()

async def echo(websocket):
    async for message in websocket:
        await websocket.send(message)

async def main():
    async with websockets.serve(echo, "localhost", 6868):
        await asyncio.Future()

class Option:
    text = "A generic option"
    index = 0
class Options:
    x = "Adama"

def MainMenu():
    print("Welcome to BrainBridge")

def ConnectToCortex():
    print("Connecting to cortex")
# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    ConnectToCortex()
    while 1:
        #print what we need
        MainMenu()

        x = input()


def baseCall():
    x = {"id": 1, "jsonrpc": "2.0"}
    return x


# See PyCharm help at https://www.jetbrains.com/help/pycharm/
