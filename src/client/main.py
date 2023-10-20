import asyncio
from email import message
import json
import logging
import stat
import sys

import websockets

logging.basicConfig(format="%(message)s", level=logging.DEBUG)

MOISTURE_PERCENT_TO_TURN_ON_PUMP = 0


async def controlPump(websocket, state: bool):
    control = {
        "type": "pump",
        "action": "off",
    }
    if state:
        control["action"] = "on"

    print(json.dumps(control, indent=4))
    await websocket.send(json.dumps(control))


def handleMoistureSensor(event: dict[str, str]) -> bool:
    print(event)
    return event["exceed"] == True


def handleMQ2SernsorMessage(event: dict[str, str]) -> bool:
    print(event)
    return event["exceed"] == True


async def handler(websocket):
    async for msg in websocket:
        try:
            event = json.loads(msg)
            if event["type"] == "moisture":
                exceedMoisture = handleMoistureSensor(event)
            elif event["type"] == "mq2":
                exceedGas = handleMQ2SernsorMessage(event)

            if exceedMoisture or exceedGas:
                await controlPump(websocket, True)
            else:
                await controlPump(websocket, False)
        except json.JSONDecodeError:
            print("Error decoding json, continue")
            continue


async def main():
    async with websockets.serve(handler, "", 8080):
        await asyncio.Future()


if __name__ == "__main__":
    asyncio.run(main())
