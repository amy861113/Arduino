from pyfirmata import Arduino, util
from time import sleep
import pymysql

def arduino_map(x, in_min, in_max, out_min, out_max):
    return(x-in_min) * (out_max-out_min) / (in_max-in_min) + out_min

PORT = "COM4"
uno = Arduino(PORT)

sleep(5)

it = util.Iterator(uno)
it.start()

a4 = uno.get_pin('a:4:i')
a5 = uno.get_pin('a:5:i')

db = pymysql.connect("120.110.114.14", "hanshin", "Hanshin519", "Student", port = 3306)
cursor = db.cursor()
print("Arduino start~")

try:
 while True:
     gas = a4.read()
     tmp = a5.read()
     try:
         gasValue = round(gas * 1024)

         Vout = arduino_map(tmp, 0, 1, 0, 5)
         tmpValue =  round((((Vout * 1000) - 500) / 10) , 2)
         #tmpValue = ((round(tmp * 1024)) * (5.0/1024) -0.5) / 0.01
         sleep(5)
     except TypeError:
         pass

     print('{0} {1}'.format(gasValue, tmpValue))
     sql = "update Student.articles_envdata set tmpValue = {1}, gasValue = {0} where data_id = 1".format(gasValue, tmpValue)
     cursor.execute(sql)
     db.commit()
     print("Update Success~")
     sleep(5)
except Exception as e:
 db.rollback()
 print("Error!:{0}".format(e))
except KeyboardInterrupt:
 uno.exit()


