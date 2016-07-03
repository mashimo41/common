from cv2.cv import *

img = LoadImage("Lena.JPG")
NamedWindow("opencv")
ShowImage("opencv",img)
WaitKey(0)
