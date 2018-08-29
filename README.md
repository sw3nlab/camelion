# camelion
433 mHz Gate signal generator for Arduino

esp8266 and esp32 comming soon ! =)

![image](https://github.com/sw3nlab/camelion/blob/master/howto.jpg)

1) Upload `main.ino` to your arduino controller.
2) Connect **Digital pin 8** to 433 transmitter  / **pin 2** to receiver.
3) Use serial monitor and next command:

After power on

From serial monitor or Linux console Use next command: 
>send 1234

where 1234 you gate code.
 
For use from the Linux console:
 - after connecting the controller to the usb port check it:
 > lsusb
 
*QinHeng Electronics HL-340 USB-Serial adapter*

Check new usb device:
 > ls /dev/ttyUSB*
 
 *for example:* /dev/ttyUSB0

For connection and autoconfiguration of the controller, you can use the GNU `screen` utility:

>screen /dev/ttyUSB0 115200

If you see a message: `Scan is DEFAULT mode.\nType 'send [code]' to send command.`
then you did everything correctly and you can scan or send signals.
detach from `screen session` by CRTL+A+D

after this you may send commands like this:

> echo "send 1234">/dev/ttyUSB0
