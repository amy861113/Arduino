#import pyfirmata
from time import sleep
import serial
import pymysql


PORT = "COM4"
#board = pyfirmata.Arduino(PORT)
board = serial.Serial(PORT, 9600)
sleep(5)

#it = pyfirmata.util.Iterator(board)
#it.start()

db = pymysql.connect("120.110.114.14", "hanshin", "Hanshin519", "env_database", port = 3306)
cursor = db.cursor()

print("Arduino start~")





try:
 while True:
  gasValue = int(board.readline())
  tmpValue = float(board.readline())
  print('{0} {1}'.format(gasValue, tmpValue))
  sql = "update env_database.env_data set tmpValue = {1}, gasValue = {0} where data_id = 1" .format(gasValue, tmpValue)
  cursor.execute(sql)
  db.commit()
  print("Update Success~")
  sleep(5)
except Exception as e:
 db.rollback()
 print("Error!:{0}".format(e))
except KeyboardInterrupt:
 board.exit()








