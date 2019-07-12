'use strict';

var Client = require('azure-iothub').Client;
var Message = require('azure-iot-common').Message;


var connectionStringDictionary = { 
                                  'DataMonitor' : 'HostName=greenhouseHub.azure-devices.net;DeviceId=DataMonitor;SharedAccessKey=DoDAJmOrP1XjvSMCUVW4H+WkMfkBD9q/NvaKLegmHeE=',
                                  'TEMP' : 'HostName=greenhouseHub.azure-devices.net;DeviceId=TEMP;SharedAccessKey=wocmf9g18fVQ+aMeZm6WilXj1QVCUaYIMKuZhjRHcA0=',
                                  'LUX' : 'HostName=greenhouseHub.azure-devices.net;DeviceId=LUX;SharedAccessKey=OviywhJqlAlaPchO6sbJxHMeH7rLmdKiZk1W3/OzO2o='
                                };

var targetDevice = process.argv[2];
var connectionString = 'HostName=greenhouseHub.azure-devices.net;SharedAccessKeyName=service;SharedAccessKey=88AHjW01a7Z0w/vPt/6Ouc5Y66AR0gbJDyGVzS42KZ4=';


var serviceClient = Client.fromConnectionString(connectionString);

function printResultFor(op) {
    return function printResult(err, res) {
      if (err) console.log(op + ' error: ' + err.toString());
      if (res) console.log(op + ' status: ' + res.constructor.name);
      // process.exit()
    };
    
}

function receiveFeedback(err, receiver){
    receiver.on('message', function (msg) {
      console.log('Feedback message:')
      console.log(msg.getData().toString('utf-8'))
      process.exit();
    });
}

serviceClient.open(function (err) {
    if (err) {
      console.error('Could not connect: ' + err.message);
    } else {
      console.log('Service client connected');
      serviceClient.getFeedbackReceiver(receiveFeedback);
      var fromDevice = process.argv[3];
      var Data = process.argv[4];
      var messageData =  targetDevice.concat('-',fromDevice,'-',Data);
    //   console.log(messageData)
      var message = new Message(messageData);
      message.ack = 'full';
      message.messageId = "My Message ID";
      console.log('Sending message: ' + message.getData());
      serviceClient.send(targetDevice, message, printResultFor('send'));
    //   serviceClient.send(targetDevice, message);
    //   TimeUnit.SECONDS.sleep(30);
    }
    // process.exit()
}
);