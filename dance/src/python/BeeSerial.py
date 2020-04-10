import serial.tools.list_ports
import sys
import glob

#ports = list(serial.tools.list_ports.comports())
#for p in ports:
#    print(p.serial_number)

class SerialBeeBoogie():
	def __init__(self, baudrate):
		self.baudrate = baudrate
		self.port = self.find_controller('beeboogie')
		print('Port founded for communication with beeboogie module: ' + str(self.port))

	def close_port():
		self.serial.close()

	def find_controller(self, password):
		    # Finds the serial port names
		if sys.platform.startswith('win'):
			ports = ['COM%s' % (i+1) for i in range(256)]
		elif sys.platform.startswith('linux') or sys.platform.startswith('cygwin'):
			ports = glob.glob('/dev/ttyUSB*')
		elif sys.platform.startswith('darwin'):
			ports = glob.glob('/dev/tty.usbserial*')
		else:
			raise EnvironmentError('Error finding ports on your operating system')

		beecontroller_port = ''
		for port in ports:
			print(port)
			try:
				s = serial.Serial(port=port, baudrate = self.baudrate, timeout=1)
				print(s)
				s.write('password\n'.encode("utf-8"))
				answer = s.readline()
				print(answer)
				s.close()

				if answer[:-1]==password:
					beecontroller_port = port

			except (OSError, serial.SerialException):
				pass

		if beecontroller_port == '':
			raise OSError('Cannot find BeeBoogie port')

		else:
			return beecontroller_port 

if __name__=='__main__':
	password = 'beeboogie'
	serial = SerialBeeBoogie(9600)
