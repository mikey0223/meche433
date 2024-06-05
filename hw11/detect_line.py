from PIL import Image
import sys

file_name = sys.argv[1]
img_data = Image.open(file_name)
img_data = img_data.convert('RGB')
# img_data.show()

import matplotlib.pyplot as plt
width, height = img_data.size
print(str(width)+" "+str(height))


mids = [0]*(height//10 + 1)

for y in range(0,height):

  index = []
  reds = []
  greens = []
  blues = []
  total = []
  for i in range(width):
      r, g, b = img_data.getpixel((i, y))
      index.append(i)
      reds.append(r)
      greens.append(g)
      blues.append(b)
      total.append(r+g+b)

  avg = sum(total)/len(total)
  line_x_vals = []
  for i, val in enumerate(total):
    if val > 1.3* avg:
      line_x_vals.append(i)
      

 
  if len(line_x_vals) > 10:
     
    mid = (line_x_vals[0] + line_x_vals[-1]) //2

    mids[y//10] = (mid,y)

    img_data.putpixel((mid, y), (255,0,0))
  else: mids[y//10] = (-1, y)
img_data.show()
print(mids)
# plt.plot(index,reds,'r-', index,greens,'g-', index,blues,'b-',index,total,'k-')
# plt.show()
