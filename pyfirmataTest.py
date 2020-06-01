from pyfirmata import Arduino, util
from time import sleep


PORT = "COM4"
uno = Arduino(PORT)

sleep(5)

it = util.Iterator(uno)
it.start()

a3 = uno.get_pin('a:3:i')
a5 = uno.get_pin('a:5:i')




try:
 while True:
  gas = a3.read()
  tmp = a5.read()
  try:
    gasValue = (gas*5000.0-500.0)/10.0
    tmpValue = (tmp*5000.0-500.0)/10.0
    print(gasValue)
    print(tmpValue)
    sleep(5)
  except TypeError:
    pass

except KeyboardInterrupt:
 uno.exit()


