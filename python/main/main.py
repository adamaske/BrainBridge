#testing for networking


token = 'eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJhcHBJZCI6ImNvbS54cmFpYmNpLmJjaTJnZSIsImFwcFZlcnNpb24iOiIxLjAuMCIsImV4cCI6MTY3NzEyNzMyOSwibmJmIjoxNjc2ODY4MTI5LCJ1c2VySWQiOiJhZjU0NzFjYS1lZDcyLTQ4YTUtYjI1OC0xOTM0NGE2ZTM5ZTciLCJ1c2VybmFtZSI6InhyYWliY2kiLCJ2ZXJzaW9uIjoiMi4wIn0.mPm__R_PfdlUkM44k65n-DvrF5_YZFFatjl8IbTXC64'

import asyncio
import websockets
import json

#"params" : {
            #"clientId" : "1KkcmNkhTy22HiM2CMzXz03nnvGV1T7950LtMoEc",
            #"clientSecret" : "dPb5EplnkaRFt7AVs1PuNOrTBGsp3HTEXBnUlX4A86p1Ev1V6OI5KMuPbOvPbpXq4AYQ9m6pNNcOnCr2KK5ETLsGyX94rJxhAHauZhQb1ADEML7jyHWhXMxd3CHcwPRS"
            #}
async def run():
    uri = "wss://localhost:6868"
    async with websockets.connect(uri) as websocket:
        x = requestAccess()
        message = json.dumps(x)
        await websocket.send(toString(x))
        print(f">>> {message}")
        
        rsp = await websocket.recv()
        response = json.loads(rsp)
        print(response["result"])

        x =queryProfiles()
        message = json.dumps(x)
        await websocket.send(message)
        
        rsp = await websocket.recv()
        response = json.loads(rsp)
        print(response["result"])
            
            
        profile = getCurrentProfile()
        
def queryProfiles():
    x = baseCall()
    x["method"] = "queryProfile"
    x["params"] = {
        "cortexToken" : token
    }
    return x
def getCurrentProfile():
    x = baseCall()
    x["method"] = "getCurrentProfile"
    x["params"] = {
        "cortexToken" : token,
        "headset" : "INSIGHT-12341234"
    }
    return x
    
def controlDevice():
    x = baseCall()
    x["method"] = controlDevice
    x["params"] = {
        "command" : "connect",
        "headset" : "Simulated Device 1"
    }  
    return x 
def toJson(string):
    return json.loads(string)

def toString(js):
    return json.dumps(js)

def storeHeadsets(result):
    result

def queryHeadsets():
    x = baseCall()
    x["method"] = "queryHeadsets"
    return x


    
    return x
def baseCall():
    x = {
        "id" : 1,
        "jsonrpc" : "2.0"
    }
    return x

def clientSecretAndID():
    x = {
        "clientId" : "1KkcmNkhTy22HiM2CMzXz03nnvGV1T7950LtMoEc",
        "clientSecret" : "dPb5EplnkaRFt7AVs1PuNOrTBGsp3HTEXBnUlX4A86p1Ev1V6OI5KMuPbOvPbpXq4AYQ9m6pNNcOnCr2KK5ETLsGyX94rJxhAHauZhQb1ADEML7jyHWhXMxd3CHcwPRS"
    }
    return x

def generateNewToken():
    x = baseCall()
    x["method"] = "generateNewToken"
    x["params"] = {
        "cortexToken" : token,
        "clientId" : "1KkcmNkhTy22HiM2CMzXz03nnvGV1T7950LtMoEc",
        "clientSecret" : "dPb5EplnkaRFt7AVs1PuNOrTBGsp3HTEXBnUlX4A86p1Ev1V6OI5KMuPbOvPbpXq4AYQ9m6pNNcOnCr2KK5ETLsGyX94rJxhAHauZhQb1ADEML7jyHWhXMxd3CHcwPRS"
    }
    return x
def requestAccess():
    x = baseCall()
    x["method"] = "requestAccess"
    x["params"] = clientSecretAndID()
    return x
    

if __name__ == "__main__":
    asyncio.run(run())