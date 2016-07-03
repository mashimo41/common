import cv2
import sys

img = cv2.imread(sys.argv[1])

cv2.imshow("img", img)

dst = img + img


cv2.imshow("img*img", dst)
cv2.waitKey(0)
